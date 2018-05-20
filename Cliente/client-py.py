import socket
import sys
import time
from random import randrange, uniform

HOST, PORT = "localhost", 9990

while True:
    lat = uniform(0, 9) * 10.0
    long = uniform(0, 9) * 10.0
    carga = randrange(0, 9) * 100
    data = str(lat) + " " + str(long) + " " + str(carga)
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        sock.connect((HOST, PORT))
        sock.sendall(bytes("x SENT: " + data + " x", "utf-8"))

        received = str(sock.recv(1024), "utf-8")
    finally:
        sock.close()
    print("Sent:     {}".format(data))
    print("Received: {}".format(received))
    time.sleep(1)
