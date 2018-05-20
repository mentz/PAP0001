import socketserver

class MyTCPHandler(socketserver.BaseRequestHandler):

    def handle(self):
        self.data = self.request.recv(1024).strip()
        print("{} HAS JUST SENT:\n".format(self.client_address[0]))
        data = str(self.data)
        data = data.split()
        print(data)
        # if(data[0] == "b'SENT:"):
        #     print("xxx")
        self.request.sendall(bytes("COORDENADAS E CARGA RECEBIDAS", "utf-8"))

if __name__ == "__main__":
    HOST, PORT = "localhost", 9990

    # Create the server, binding to localhost on port 9999
    server = socketserver.TCPServer((HOST, PORT), MyTCPHandler)

    # Activate the server; this will keep running until you
    # interrupt the program with Ctrl-C
    server.serve_forever()
