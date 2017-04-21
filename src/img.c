#include "lib/img.h"

#include <string.h>
#include <stdlib.h>
#include <dirent.h>

// i doesn't matter
int imgShift(Image* img, int i){
    return (int)((img->xDim-strlen(img->img[i]))/2); // bad naming
}

void renderImg(GameWindow* GW, Image* img, int y, int x){
    int shift;
    for(int i = 0; i < img->yDim; i++){
        shift = imgShift(img,i);
        mvwaddstr(GW->W,y+i,x+shift,img->img[i]);
    }
}

void derenderImg(GameWindow* GW, Image* img, int y, int x){
    for(int i = 0; i < img->xDim; i++)
        for(int j = 0; j < img->yDim; j++)
            mvwaddch(GW->W,y+j,x+i,' ');
}

int hash(char* type){
    int hash = 0;
    for (int i = 0; i < strlen(type); i++)
        hash += hash*7 + type[i];
    return hash % NUM_IMAGES;
}

Image* loadImage(char* filePath){
    int xDim, yDim;
    Image* img = malloc(sizeof(Image));
    FILE* fp = fopen(filePath,"r");
    fscanf(fp,"%d,%d",&xDim,&yDim);

    char** imgStr = malloc(yDim*sizeof(char*));
    for(int i = 0; i < yDim; i++){
        imgStr[i] = malloc(sizeof(char)*(xDim+1));
        fscanf(fp,"%s",imgStr[i]);
    }
    img->img = imgStr;
    img->xDim = xDim;
    img->yDim = yDim;

    return img;
}

void loadImages(GameWindow* GW){
    GW->images = malloc(NUM_IMAGES*sizeof(ImgTableElem*));
    Image* img;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("img")) != NULL){
        while ((ent = readdir(dir)) != NULL)
            insertImg(GW,ent->d_name,loadImage(ent->d_name)); // parsing the type or something would be nicer
        closedir (dir);
    }
    else perror("Image loading");
}

void insertImg(GameWindow* GW, char* type, Image* img){
    ImgTableElem* imgElem = malloc(sizeof(ImgTableElem));
    imgElem->type = type;
    imgElem->img = img;

    int hashInd = hash(type), count;
    while(GW->images[hashInd] != NULL){
        hashInd++;
        hashInd %= NUM_IMAGES;
        count++;
        // table isn't resizable
        if(count > NUM_IMAGES){
            printw("Implementation failure!");
            getch();
            endwin();
            exit(EXIT_FAILURE);
        }
    }
}

Image* searchImgTable(GameWindow* GW, char* type){
    int hashInd = hash(type);
    while(GW->images[hashInd] != NULL){
        // 0 from strcmp indicates match
        if(!strcmp(GW->images[hashInd]->type,type))
            return GW->images[hashInd]->img;
        hashInd++;
        hashInd %= NUM_IMAGES;
    }
   return NULL;
}


