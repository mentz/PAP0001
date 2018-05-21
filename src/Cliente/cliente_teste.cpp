#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h> // close
#include <string.h>
#include "comunicacao.hpp"

using namespace std;

int main( int argc, char ** argv )
{
    vector<Parada> a;
    int mensagem_atual = 1;
    requestParadaAviao("127.0.0.1", 9990, a, mensagem_atual);
    for (size_t i = 0; i < a.size(); i++) {
        cout << a[i].id_aviao << " - " << a[i].id_parada << " - " << a[i].latitude << " - " << a[i].longitude << " - " << a[i].carga_descarga << endl;
    }

    return 0;
}
