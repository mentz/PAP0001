import socketserver

# armazena id do avião, num_parada, carga, latitute, longitude
paradas = []

class MyTCPHandler(socketserver.BaseRequestHandler):

    def handle(self):
        self.data = self.request.recv(1024).strip()

        print("{} ACABOU DE ENVIAR:\n".format(self.client_address[0]))
        data = str(self.data)
        data = data.split(";")
        print(data)

        if(data[1] == "0"):
            paradas.append([data[2], data[3], data[4], data[5], data[6]])


        self.request.sendall(bytes("DADOS RECEBIDOS", "utf-8"))

if __name__ == "__main__":
    HOST, PORT = "localhost", 9999

    # Create the server, binding to localhost on port 9999
    server = socketserver.TCPServer((HOST, PORT), MyTCPHandler)

    # Activate the server; this will keep running until you
    # interrupt the program with Ctrl-C
    server.serve_forever()
