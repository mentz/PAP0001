#include "fblib.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

#include <fcntl.h>
#include <linux/fb.h>
#include <linux/kd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>

#define fbdev "/dev/fb0"
#define ttydev "/dev/tty"

typedef struct {
    uint_fast8_t    r, g, b, a;
} Color;

#define Die(Msg, ...) { \
    fprintf (stderr, "fbgrad: " Msg ".\n", __VA_ARGS__); \
    exit(1); \
}\

#define Assumption(Cond, Msg) \
    if (!(Cond)) { \
        fprintf (stderr, "fbgrad: failed assumption: %s\n", Msg);\
        exit(2);\
    }

using namespace std;

int main (int argc, char **argv) {
    int ttyfd = open (ttydev, O_RDWR);
    if (ttyfd < 0)
        Die ("cannot open \"%s\"", ttydev);

    if (ioctl (ttyfd, KDSETMODE, KD_GRAPHICS) == -1)
        Die ("cannot set tty into graphics mode on \"%s\"", ttydev);

    int fbfd = open (fbdev, O_RDWR);
    if (fbfd < 0)
        Die ("cannot open \"%s\"", fbdev);

    struct fb_var_screeninfo vinf;
    struct fb_fix_screeninfo finf;

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


    Screen s;
    // s.size = finf.line_length * vinf.yres;
    s.size = finf.smem_len;
    s.bytes_per_pixel = vinf.bits_per_pixel / 8;
    s.bytes_per_line  = finf.line_length;
    s.red             = vinf.red.offset/8;
    s.green           = vinf.green.offset/8;
    s.blue            = vinf.blue.offset/8;
    s.width           = vinf.xres;
    s.height          = vinf.yres;

    s.buffer = (char*) mmap (0, s.size, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);

    if (s.buffer == MAP_FAILED)
        Die ("cannot map frame buffer \"%s\"", fbdev);





    // cout << s.width << " " << s.height << endl;

    vector<pair<int, pair<int, int> > > pixel;

    ifstream mapa("mapa_codificado.txt");

    while(true)
    {
        int r, g, b;
        mapa >> r >> g >> b;
        if(mapa.eof()) break;        
        pixel.push_back(make_pair(r, make_pair(g, b)));
    }


    int time_start = time (NULL);

    int pixel_id = 0;
    for (uint t = 0; t < 500; t++) {
        for (uint y = 0; y < vinf.yres; y++) {
            for (uint x = 0; x < vinf.xres; x++) {
                uint pix_offset = x * s.bytes_per_pixel + y * s.bytes_per_line;
                s.buffer[pix_offset + s.red] = pixel[pixel_id].first;
                s.buffer[pix_offset + s.green] = pixel[pixel_id].second.first;
                s.buffer[pix_offset + s.blue] = pixel[pixel_id].second.second;
                pixel_id++;
            }
        }
        pixel_id = 0;
    }

    int time_end = time(NULL);

    munmap (s.buffer, s.size);

    if (ioctl (ttyfd, KDSETMODE, KD_TEXT) == -1)
        Die ("cannot set tty into text mode on \"%s\"", ttydev);

    close (fbfd);
    close (ttyfd);

    printf ("FPS: %.2f.\n", 255.0 / (time_end - time_start));

    return EXIT_SUCCESS;
}
