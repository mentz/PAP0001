#include "fblib.hpp"
#include "comunicacao.hpp"

using namespace std;

volatile sig_atomic_t flag = 0;
void sig_handler(int sig)
{
	flag = 1;
}

int main (int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Uso: $ %s <server_ip>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	string host(argv[1]);
	int porta = 9998;
	int contador = 0;
	vector<Parada> paradas;
	requestParadas(host, porta, paradas, contador);

	signal(SIGINT, sig_handler);
	Screen s;
	vector<Borda> mapa;

	// Ler o mapa
	{
		ifstream fis ("bounds.txt", ifstream::in);
		int n;
		fis >> n;
		mapa = vector<Borda>(n);	
		for (int i = 0; i < n; i++)
		{
			fis >> mapa[i].y >> mapa[i].x;
			// Converter para resolução atual
			mapa[i].x *= s.width / 1920.0;
			mapa[i].y *= s.height / 1080.0;
		}
	}

	int time_start = time (NULL);
	
	Color fundo  = {20, 25, 80},
		  linhas = {150, 150, 150},
		  bordas = {10, 230, 30},
		  branco = {255, 255, 255},
		  preto  = {0, 0, 0};
	int linestep  = 15;
	int xinterval = s.width * linestep  / 360;
	int yinterval = s.height * linestep / 180;

	int t = 0;
	while (!flag)
	{
		s.clear(fundo);
		
		// Desenhar o mapa
		for (uint i = 0; i < mapa.size(); i++)
			s.drawPixel(mapa[i].x, mapa[i].y, bordas);

		for (uint x = 0; x < s.width; x += xinterval)
			s.drawDottedLine(x, 0, x, s.height - 1, 3, linhas);
		for (uint y = 0; y < s.height; y += yinterval)
			s.drawDottedLine(0, y, s.width - 1, y, 3, linhas);

		for (uint i = 0; i < paradas.size(); i++)
		{
			cout << "avião " << i << ": ";
			uint x = ((paradas[i].longitude / 360.0) + 0.5) * s.width;
			uint y = ((paradas[i].latitude / -180.0) + 0.5) * s.height;
			cout << x << ", " << y << "\n";
			s.drawCircle(x, y, 13, preto);
			s.drawCircle(x, y, 11, branco);
		}

		// Desenhar 'frame' pra deixar bonito
		s.drawLine(0, 0, 0, s.height - 1, branco);
		s.drawLine(0, s.height - 1, s.width - 1, s.height - 1, branco);
		s.drawLine(s.width - 1, 0, s.width - 1, s.height - 1, branco);
		s.drawLine(0, 0, s.width - 1, 0, branco);

		s.swapBuffers();
		t++;
	}

	int time_end = time(NULL);

	printf("Tempo: %d segundos.\n", (time_end - time_start));
	printf("FPS: %.2f\n", (float)t / (time_end - time_start));

	return EXIT_SUCCESS;
}
