#ifndef _FBLIB_H_
#define _FBLIB_H_

#include <stdint.h>
#include <stdlib.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include <fcntl.h>
#include <linux/fb.h>
#include <linux/kd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ctime>
#include <cmath>
#include <signal.h>

#define MAX(a,b) ((a>b)?a:b)
#define ABS(a) ((a>=0)?a:-a)
#define fbdev "/dev/fb0"
#define ttydev "/dev/tty"

#define Die(Msg, ...) {\
	fprintf (stderr, "drawPlane: " Msg ".\n", __VA_ARGS__);\
	exit(1);\
}\

#define Assumption(Cond, Msg) \
	if (!(Cond)) { \
		fprintf (stderr, "drawPlane: failed assumption: %s\n", Msg);\
		exit(2); \
	}

typedef unsigned int uint;

typedef struct {
	uint_fast8_t r, g, b;
} Color;

class Screen
{
private:
	char 	*buffer;
	uint	red, green, blue;
	int 	ttyfd, fbfd;
	size_t	size, bytes_per_pixel, bytes_per_line;
	struct fb_var_screeninfo vinf;
	struct fb_fix_screeninfo finf;

public:
	size_t width, height;
	
	Screen ()
	{
		ttyfd = open (ttydev, O_RDWR);
		if (ttyfd < 0)
			Die ("cannot open \"%s\"", ttydev);

		if (ioctl (ttyfd, KDSETMODE, KD_GRAPHICS) == -1)
			Die ("cannot set tty into graphics mode on \"%s\"", ttydev);

		fbfd = open (fbdev, O_RDWR);
		if (fbfd < 0)
			Die ("cannot open \"%s\"", fbdev);


		if (ioctl (fbfd, FBIOGET_FSCREENINFO, &finf) == -1)
			Die ("cannot open fixed screen info for \"%s\"", fbdev);

		if (ioctl (fbfd, FBIOGET_VSCREENINFO, &vinf) == -1)
			Die ("cannot open variable screen info for \"%s\"", fbdev);

		Assumption ((vinf.red.offset%8) == 0 && (vinf.red.length == 8) &&
					(vinf.green.offset%8) == 0 && (vinf.green.length == 8) &&
					(vinf.blue.offset%8) == 0 && (vinf.blue.length == 8) &&
					(vinf.transp.offset) == 0 && (vinf.transp.length == 0) &&
					vinf.xoffset == 0 && vinf.yoffset == 0 &&
					vinf.red.msb_right == 0 &&
					vinf.green.msb_right == 0 &&
					vinf.blue.msb_right == 0,
					"Color masks are 8bit, byte aligned, little endian, no transparency."
		);

		this->size				= finf.smem_len;
		this->bytes_per_pixel	= vinf.bits_per_pixel / 8;
		this->bytes_per_line	= finf.line_length;
		this->red				= vinf.red.offset/8;
		this->green				= vinf.green.offset/8;
		this->blue				= vinf.blue.offset/8;
		this->width				= vinf.xres;
		this->height				= vinf.yres;
		this->buffer = (char*) mmap (0, this->size, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
	
		if (this->buffer == MAP_FAILED)
			Die ("cannot map frame buffer \"%s\"", fbdev);
	}

	void drawPixel(uint x, uint y, Color c)
	{
		if (x < 0 || x >= this->width ||
			y < 0 || y >= this->height)
			return;

		uint pix_offset = x * this->bytes_per_pixel + y * this->bytes_per_line;
		this->buffer[pix_offset + this->red]   = c.r;
		this->buffer[pix_offset + this->green] = c.g;
		this->buffer[pix_offset + this->blue]  = c.b;
	}

	void clear(Color c)
	{
		for (uint y = 0; y < this->height; y++)
			for (uint x = 0; x < this->width; x++)
				drawPixel(x, y, c);
	}

	/*
	void drawLineLow(uint x0, uint x1, uint y0, uint y1, Color c)
	{
		int dx = x1 - x0;
		int dy = y1 - y0;
		int yi = 1;
	}
	*/

	void drawLine(uint x0, uint y0, uint x1, uint y1, Color c)
	{
		// TODO Implementar Bresenham's line
		float dx = x1 - x0, dy = y1 - y0, x = x0, y = y0;
		const float fmax = MAX(fabs(dx), fabs(dy));
		dx /= fmax; dy /= fmax;
		for (int i = 0; i < (int) fmax && i <= 3840; i++)
		{
			drawPixel((uint) x, (uint) y, c);
			x += dx; y += dy;
		}
	}

	// Desenhar círculos
	void drawCircle(uint x, uint y, uint r, Color c)
	{
		for (uint i = y - r; i < y + r; i++)
			for (uint j = x - r; j < x + r; j++)
				if (hypot(ABS(j - x), ABS(i - y)) <= r)
					drawPixel(j, i, c);
	}

	// Destrutor
	~Screen ()
	{
		munmap (this->buffer, this->size);

		if (ioctl (ttyfd, KDSETMODE, KD_TEXT) == -1)
			Die ("cannot set tty into text mode on \"%s\"", ttydev);

		close (fbfd);
		close (ttyfd);
	}
};


#endif
