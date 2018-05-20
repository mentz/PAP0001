#include "fblib.hpp"

using namespace std;

volatile sig_atomic_t flag = 0;
void sig_handler(int sig)
{
	flag = 1;
}

int main (int argc, char **argv)
{
	signal(SIGINT, sig_handler);
	Screen s;
	vector<Borda> mapa;

	// Ler o mapa
	{
		ifstream fis ("bounds.txt", ifstream::in);
		int n, a;
		fis >> n;
		mapa = vector<Borda>(n);	
		for (int i = 0; i < n; i++)
		{
			fis >> a >> mapa[i].y >> mapa[i].x;
			// Converter para resolução atual
			mapa[i].x *= s.width / 1920;
			mapa[i].y *= s.height / 1080;
		}
	}
	
	int time_start = time (NULL);

	// Desenhar grade do mundo
	
	Color fundo = {30, 30, 120},
		  linhas = {80, 80, 83};
	int linestep  = 30;
	int xinterval = s.width * linestep  / 360;
	int yinterval = s.height * linestep / 180;

	int t = 0;
	while (!flag)
	{
		s.clear(fundo);
		
		// Desenhar o mapa
		for (uint i = 0; i < mapa.size(); i++)
			s.drawPixel(mapa[i].x, mapa[i].y, {10, 240, 30});

		for (uint x = 0; x < s.width; x += xinterval)
			s.drawLine(x, 0, x, s.height - 1, linhas);
		for (uint y = 0; y < s.height; y += yinterval)
			s.drawLine(0, y, s.width - 1, y, linhas);

		s.drawLine(20, 20, 1900, 1060, {0, 255, 100});
		s.drawLine(600, 400, 800, 600, {255, 0, 160});
		s.drawCircle(960, 540, 80, {255, 200, 120});

		//s.swapBuffers();
		t++;
	}

	int time_end = time(NULL);

	printf("Tempo: %d segundos.\n", (time_end - time_start));
	printf("FPS: %.2f\n", (float)t / (time_end - time_start));

	return EXIT_SUCCESS;
}
