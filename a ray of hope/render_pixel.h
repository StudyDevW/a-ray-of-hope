#pragma once

//PIXEL - размер пикселей
enum pixels {
    PIXEL = 3,
    PIXELB = 5 //5 def
};

class pixels_other_t {
public:
    int width_pix = 0;
    int pix_space = 0;
    int pix_start_pos = 0;

    pixels_other_t(int w, int space, int start_pos = 0) {
        width_pix = w;
        pix_space = space;
        pix_start_pos = start_pos;
    }

    void reset_pos() {
        pix_start_pos = 0;
    }
};



