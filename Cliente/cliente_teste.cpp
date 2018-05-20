#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h> // close
#include <string.h>
#include "comunicacao.hpp"

using namespace std;

int main( int argc, char ** argv )
{
    int mensagem_atual = 0;
    parada info_atual;
    info_atual = requestParadaAviao("127.0.0.1", 9999, mensagem_atual);
    return 0;
}
