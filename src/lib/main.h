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
    Window* W;
    Player* P;
    EnemyLL* ELL;

    Image* player;
    Image* nearEnemy;
    Image* midEnemy;
    Image* farEnemy;

    int boundX;          // For convenience
    int boundY;
    // projectiles? Could be very similar to enemies given lim
} GameWindow;

bool wmvaddch(Window* W, int y, int x, int ch);
bool isOccupied(GameWindow* GW, int y, int x, int xMax);
void freeGW(GameWindow* GW);
int renderMenu(Window* W, int menuWidth, char* title, char* subtitle, int numOptions, char** options); // returns selected index
void renderImg(GameWindow* GW, Image* img, int y, int x);
void runGame(GameWindow* GW);

#endif /* MAIN_H */

