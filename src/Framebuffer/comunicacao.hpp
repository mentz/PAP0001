#ifndef COMUNICACAO_H_
#define COMUNICACAO_H_

#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h> // close
#include <string.h>
#include <vector>
#include <map>

using namespace std;

typedef struct {
	int cont;
	int num_parada;
	float lat;
	float lon;
	float carga_descarga;
	double x, y;
} Parada;

class Avioes {
public:
	map<int, vector<Parada> > mapa;
	int contador = 0;

	vector<Parada> operator[](const int &a)
	{
		return mapa[a];
	}

	bool inline getHasKey(int a)
	{
		return mapa.find(a) != mapa.end();
	}
};

void requestParadas(string host, int porta, Avioes &avioes)
{
	int sock = -1;

	sock = socket( AF_INET , SOCK_STREAM , 0 );
	if (sock == -1){
		cerr << "Error: could not create socket." << endl;
	}

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr( host.c_str() );
	server_addr.sin_port = htons( porta );

	if ( connect(sock, (struct sockaddr *) &server_addr , sizeof(server_addr)) < 0 ){
		cerr << "Error: connection failure." << endl;
		return;
	}

	string data = "x;1;" + std::to_string(avioes.contador) + ";x";
	if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
	{
		cerr << "Error: send failed."  << endl;
		return;
	}

	//Receive a reply from the server
	char buffer[8192];
	memset( buffer, 0, 8192 );
	if( recv(sock, buffer, sizeof(buffer), 0) < 0)
	{
		cerr << "Error: receive failed." << endl;
	}

	/* Formato da resposta do servidor:
		"" (se não houver nenhum dado novo)
	   ou
		"<id_aviao> <contador_global> <contador_da_parada> <lat> <lon> <carga/descarga>\n"
		(repete se houver mais entradas numa mesma solicitação)
	*/
	printf("Recebido: \n%s\n", buffer);
	stringstream msg_buf;
	msg_buf << buffer;
	int ic, ia, ip;
	float lat, lon, cd;
	double x, y;
	if (msg_buf.str() != "") cout << "Recebidos:\n";
	while(msg_buf >> ia >> ic >> ip >> lat >> lon >> cd)
	{
		cout << ic << "," << ia << "," << ip << "," << lat << "," << lon << "," << cd << "\n";

		if (ic >= avioes.contador)
		{
			if (!avioes.getHasKey(ia))
				avioes.mapa[ia] = vector<Parada>();
			
			x = ((lon / (double)360.0) + 0.5);
			y = ((lat / (double)-180.0) + 0.5);

			avioes.contador++; // Pode vir desordenado, mas todos serão aceitos
			avioes.mapa[ia].push_back({ic, ip, lat, lon, cd, x, y});
		}
	}

	/*
	cout << "Paradas: \n";
	for (unsigned int i = 0; i < paradas.size(); i++)
	{
		ia = paradas[i].id_aviao;
		ip = paradas[i].id_parada;
		lat = paradas[i].latitude;
		lon = paradas[i].longitude;
		cd = paradas[i].carga_descarga;
		cout << ia << ", " << ip << "," << lat << "," << lon << "," << cd << "\n";
	}
	*/

	close( sock );
}

#endif
