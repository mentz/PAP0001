#include "comunicacao.hpp"

using namespace std;

parada requestParadaAviao(std::string ip, int porta, int mensagens_recebidas){
    parada info_recebida;

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
      return info_recebida;
    }

    string data = "x;1;" + std::to_string(mensagens_recebidas) + ";x";
    if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
    {
      cerr << "Error: send failed."  << endl;
      return info_recebida;
    }

    //Receive a reply from the server
    char buffer[256];
    memset( buffer, 0, 256 );
    if( recv(sock, buffer, sizeof(buffer), 0) < 0)
    {
      cerr << "Error: receive failed." << endl;
    }

    cout << "Sent:     " << data << endl;
    cout << "Received: " << buffer << endl;

    close( sock );

}
