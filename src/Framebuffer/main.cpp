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
	
	Avioes avioes;
	requestParadas(host, porta, avioes);

	signal(SIGINT, sig_handler);
	vector<Borda> mapa;

	Screen s;

	// Ler o mapa
	{
		stringstream ss;
		char * buf = new char[512];
		buf = getcwd(buf, 511);
		ss << buf << "/src/Framebuffer/bounds.txt";
		cout << ss.str() << endl;
		ifstream fis (ss.str(), ifstream::in);
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
	
	float xinterval = s.width * linestep  / 360;
	float yinterval = s.height * linestep / 180;

	int t = 0;
	while (!flag)
	{
		requestParadas(host, porta, avioes);
		s.clear(fundo);

		// Desenhar o mapa
		for (uint i = 0; i < mapa.size(); i++)
			s.drawPixel(mapa[i].x, mapa[i].y, bordas);

		for (float x = 0; x < s.width; x += xinterval)
			s.drawDottedLine((uint)x, 0, (uint)x, s.height - 1, 3, linhas);
		for (float y = 0; y < s.height; y += yinterval)
			s.drawDottedLine(0, (uint)y, s.width - 1, (uint)y, 3, linhas);

		cout << "Qtde avioes: " << avioes.mapa.size() << "\n";
		for (auto &a : avioes.mapa)
		{
			uint x = 0, y = 0, xa, ya;
			cout << "Avião " << a.first << ": " << a.second.size() << " paradas:\n";
			for (uint i = 0; i < a.second.size(); i++)
			{
				xa = x; ya = y;
				cout << "\tParada " << a.second[i].num_parada;
				x = a.second[i].x * s.width;
				y = a.second[i].y * s.height;
				cout << a.second[i].x << ", " << a.second[i].y << "\n";
				s.drawCircle(x, y, 13, preto);
				s.drawCircle(x, y, 11, branco);
				if (i != 0)
					s.drawLine(x, y, xa, ya, branco); 
			}
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
