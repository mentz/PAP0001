#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h> // close
#include <string.h>

using namespace std;

int main( int argc, char ** argv )
{
    int sock = -1;
    struct sockaddr_in server;

    sock = socket( AF_INET , SOCK_STREAM , 0 );
    if (sock == -1){
        cerr << "Error: could not create socket." << endl;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
    server_addr.sin_port = htons( 9999 );

    if ( connect(sock, (struct sockaddr *) &server_addr , sizeof(server_addr)) < 0 ){
        cerr << "Error: connection failure." << endl;
        return 1;
    }

    string data = "hello c++ network world.";
    if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
    {
        cerr << "Error: send failed."  << endl;
        return 2;
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

    return 0;
}
