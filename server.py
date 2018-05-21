#!/usr/sbin/python3
#! coding=utf-8

import socketserver
import sys

# armazena id do avião, num_parada, latitute, longitude, carga
paradas = []
HOST = ""
PORT = ""

class MyTCPHandler(socketserver.BaseRequestHandler):

	def handle(self):
		self.data = self.request.recv(1024).strip()
		data = str(self.data)
		data = data.split(";")

		print("Redebido de %s: %s" %(self.client_address[0], data))

		if(data[1] == "0"):  #Guarda dados
			paradas.append([data[2], data[3], data[4], data[5], data[6]])
			self.request.sendall(bytes("DADOS RECEBIDOS", "utf-8"))

		if(data[1] == "1"): #Envia dados
			# Considerando que o request seja no formato 'x;1;n;x', onde n é o
			# índice do próximo registro que o cliente_framebuffer espera
			i = 0
			envio = ""
			for stop in paradas:
				if(i >= int(data[2])):
					envio += str(str(i) + " " + stop[0] + " " + stop[1] + " " + stop[2] + " " + stop[3] + " " + stop[4] + " ")
				i = i + 1
			print("Enviando %s" %envio);
			self.request.sendall(bytes(envio, "utf-8"))

if __name__ == "__main__":
	PORT = 9998
	#print("Digite o endereco do servidor: ")
	HOST = '0.0.0.0'

	print("Iniciando servidor")
	try:
		# Create the server, binding to localhost on port 9990
		server = socketserver.TCPServer((HOST, PORT), MyTCPHandler)

		# Activate the server; this will keep running until you
		# interrupt the program with Ctrl-C
		server.serve_forever()
	except KeyboardInterrupt:
		print("Stopping server")
	finally:
		server.server_close()
