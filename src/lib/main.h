#ifndef MAIN_H
#define MAIN_H

#define MAX_ENEMIES 55

#include <ncurses.h>
#include <stdbool.h>


typedef WINDOW Window;
typedef struct Enemy Enemy;
typedef struct EnemyLL EnemyLL;
typedef struct Player Player;

typedef struct {
    int x;
    int y;
} Coord, *CoordPtr;

typedef struct {
    int xDim;
    int yDim;
    char** img;
} Image;

typedef struct {
    Image* player;
    Image* nearEnemy1;
    Image* nearEnemy2;
    Image* midEnemy1;
    Image* midEnemy2;
    Image* farEnemy1;
    Image* farEnemy2;
    Image* barricade;
} Images;

typedef struct {
    Window* W;
    Player* P;
    EnemyLL* ELL;

    Images* images;
    int state;           // 0 or 1 for alternating animations

    int boundX;          // For convenience
    int boundY;
    // projectiles? Could be very similar to enemies given lim
} GameWindow;

void freeGW(GameWindow* GW);
int renderMenu(Window* W, int menuWidth, char* title, char* subtitle, int numOptions, char** options); // returns selected index
void renderImg(GameWindow* GW, Image* img, int y, int x);
void derenderImg(GameWindow* GW, Image* img, int y, int x);
void runGame(GameWindow* GW);

#endif /* MAIN_H */

