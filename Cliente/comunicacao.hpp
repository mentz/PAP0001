#ifndef COMUNICACAO_H_
#define COMUNICACAO_H_

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h> // close
#include <string.h>

typedef struct {
    int id_aviao;
    int id_parada;
    float carga_descarga;
    int coord_x;
    int coord_y;
} parada;

parada requestParadaAviao(std::string ip, int porta, int mensagens_recebidas);

#endif
