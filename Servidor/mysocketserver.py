import socketserver
import sys

# armazena id do avião, num_parada, latitute, longitude, carga
paradas = []

class MyTCPHandler(socketserver.BaseRequestHandler):

    def handle(self):
        self.data = self.request.recv(1024).strip()

        print("{} ACABOU DE ENVIAR:\n".format(self.client_address[0]))
        data = str(self.data)
        data = data.split(";")
        print(data)

        if(data[1] == "0"):  #Guarda dados
            paradas.append([data[2], data[3], data[4], data[5], data[6]])
            self.request.sendall(bytes("DADOS RECEBIDOS", "utf-8"))

        if(data[1] == "1"): #Envia dados
            #Considerando que o reques seja no formato 'x;1;n;x', onde n é o índice do próximo registro que o cliente_framebuffer espera
            i = 0
            for stop in paradas:
                if(i > data[2]):
                    envio += str("x;" + stop[0] + ";" + stop[1] + ";" + stop[2] + ";" + stop[3] + ";" + stop[4] + ";x")
                i = i + 1 
                
            self.request.sendall(bytes(envio, "utf-8"))

if __name__ == "__main__":
    PORT = 9990
    print("Digite o endereco do servidor: ")
    HOST = input()

    # Create the server, binding to localhost on port 9990
    server = socketserver.TCPServer((HOST, PORT), MyTCPHandler)

    # Activate the server; this will keep running until you
    # interrupt the program with Ctrl-C
    server.serve_forever()
