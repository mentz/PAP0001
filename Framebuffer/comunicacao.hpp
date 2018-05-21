#ifndef COMUNICACAO_H_
#define COMUNICACAO_H_

#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h> // close
#include <string.h>
#include <vector>

typedef struct {
	int id_aviao;
	int id_parada;
	float latitude;
	float longitude;
	float carga_descarga;
} Parada;

using namespace std;

void requestParadas(string host, int porta, vector<Parada> &paradas, int &contador)
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

	string data = "x;1;" + std::to_string(contador) + ";x";
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

	printf("Recebido: \n%s\n", buffer);
	stringstream msg_buf;
	msg_buf << buffer;
	int ii, ia, ip;
	float lat, lon, cd;
	cout << "Recebidos:\n";
	while(msg_buf >> ii >> ia >> ip >> lat >> lon >> cd)
	{
		cout << "teste\n";
		/*
		divisoria = msg.find(";", divisoria + 1);
		parada_atual.id_aviao = stoi(msg.substr(divisoria + 1, msg.find(";", divisoria)));
		divisoria = msg.find(";", divisoria + 1);
		parada_atual.id_parada = stoi(msg.substr(divisoria + 1, msg.find(";", divisoria)));
		divisoria = msg.find(";", divisoria + 1);
		parada_atual.latitude = stof(msg.substr(divisoria + 1, msg.find(";", divisoria)));
		divisoria = msg.find(";", divisoria + 1);
		parada_atual.longitude = stof(msg.substr(divisoria + 1, msg.find(";", divisoria)));
		divisoria = msg.find(";", divisoria + 1);
		parada_atual.carga_descarga = stoi(msg.substr(divisoria + 1, msg.find(";", divisoria)));
		paradas.push_back(parada_atual);
		divisoria = msg.find(";", divisoria + 1);
		*/

		cout << ia << "," << ip << "," << lat << "," << lon << "," << cd << "\n";

		if (ii >= contador)
		{
			contador++;
			paradas.push_back({ia, ip, lat, lon, cd});
		}
	}

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

	close( sock );
}

#endif
