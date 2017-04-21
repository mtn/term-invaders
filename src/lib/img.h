#ifndef IMG_H
#define IMG_H

#include "main.h"

struct Image {
    int xDim;
    int yDim;
    char** img;
};

struct ImgTableElem {
    char* type;
    Image* img;
};

void renderImg(GameWindow* GW, Image* img, int y, int x);
void derenderImg(GameWindow* GW, Image* img, int y, int x);
Image* searchImgTable(GameWindow* GW, char* type);
void insertImg(GameWindow* GW, char* type, Image* img);
void loadImages(GameWindow* GW);

#endif /* IMG_H */

