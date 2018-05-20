#ifndef _FBLIB_H_
#define _FBLIB_H_

#include <stdint.h>
#include <stdlib.h>

// typedef uint_fast16_t uint;

// typedef struct {
//     char    *buffer;
//     size_t  size,
//             bytes_per_pixel, bytes_per_line,
//             width, height;
//     uint    red, green, blue;
// } Screen;

class Screen{
public:
    // uint size;
    // uint bytes_per_pixel;
    // uint bytes_per_line ;
    // uint red;
    // uint green;
    // uint blue;
    // uint width;
    // uint height;
    char    *buffer;
    size_t  size,
            bytes_per_pixel, bytes_per_line,
            width, height;
    uint    red, green, blue;
};


#endif
