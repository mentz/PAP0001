#ifndef COMUNICACAO_H_
#define COMUNICACAO_H_

#include <iostream>
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

void requestParadaAviao(std::string ip, int porta, std::vector<Parada> &paradas, int mensagens_recebidas);

#endif
