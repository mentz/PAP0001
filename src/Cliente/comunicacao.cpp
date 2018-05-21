#include "comunicacao.hpp"

using namespace std;

void requestParadaAviao(std::string ip, int porta, vector<Parada> &paradas, int mensagens_recebidas){

    int sock = -1;

    sock = socket( AF_INET , SOCK_STREAM , 0 );
    if (sock == -1){
      cerr << "Error: could not create socket." << endl;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr( ip.c_str() );
    server_addr.sin_port = htons( porta );

    if ( connect(sock, (struct sockaddr *) &server_addr , sizeof(server_addr)) < 0 ){
      cerr << "Error: connection failure." << endl;
      return;
    }

    string data = "x;1;" + std::to_string(mensagens_recebidas) + ";x";
    // string data = "x;1;0;0.002;0.003;40;xx;1;1;0.003;0.003;50;x";
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

    string msg = buffer;
    Parada parada_atual;
    cout << msg << endl;
    int divisoria = 0;
    while(divisoria < msg.size() - 2){
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
    }

    close( sock );

}
