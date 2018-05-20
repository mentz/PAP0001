import socket
import sys
import time
from random import randrange, uniform
# "<id_aviao>;<num_parada>;<carga_descarga (pode ser só um inteiro tipo -80 ou 40)>;<lat>;<long>"
# Latitude(90, -90) Longitude (180, -180) btw
HOST, PORT = "localhost", 9999

print("Digite o ID do Aviao")
ID_AVIAO = input()

num_parada = 0;

while True:
    print("Digite a Carga (+: carregada, -: descarregada)")
    carga = int(input())
    print("Digite a Latitude (-90, +90)")
    lat = float(input())
    print("Digite a Longitude (-180, +180)")
    long = float(input())
    num_parada = num_parada + 1
    # lat = uniform(0, 9) * 10.0
    # long = uniform(0, 9) * 10.0
    # carga = randrange(0, 9) * 100

    data = ID_AVIAO + ";" + str(num_parada) + ";" + str(carga) + ";" + str(lat) + ";" + str(long)

    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        sock.connect((HOST, PORT))
        sock.sendall(bytes("x;0;" + data + ";x", "utf-8"))

        received = str(sock.recv(1024), "utf-8")
    finally:
        sock.close()
    print("ENVIADO:     {}".format(data))
    print("RECEBIDO: {}".format(received))
    time.sleep(1)
