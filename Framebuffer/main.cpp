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
	
	int time_start = time (NULL);

	// Desenhar grade do mundo
	
	Color cinza = {127, 127, 127},
		  preto = {0, 0, 0};
	int linestep  = 30;
	int xinterval = s.width * linestep  / 360;
	int yinterval = s.height * linestep / 180;

	s.clear(preto);

	
	for (uint t = 0; t < 10 && !flag; t++) {
		for (uint x = 0; x < s.width; x += xinterval) {
			s.drawLine(x, 0, x, s.height - 1, cinza);
		}
		for (uint y = 0; y < s.height; y += yinterval) {
			s.drawLine(0, y, s.width - 1, y, cinza);
		}
		s.drawLine(20, 20, 1900, 1060, {0, 255, 100});
		s.drawLine(600, 400, 800, 600, {255, 0, 160});
		s.drawCircle(960, 540, 80, {255, 200, 120});
	}

	int time_end = time(NULL);

	printf("Tempo: %d segundos.\n", (time_end - time_start));

	return EXIT_SUCCESS;
}
