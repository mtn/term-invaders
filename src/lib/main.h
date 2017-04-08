#ifndef MAIN_H
#define MAIN_H

#define MAX_ENEMIES 55

#include <ncurses.h>
#include <stdbool.h>


typedef WINDOW Window;

typedef struct {
    int x;
    int y;
} Coord, *CoordPtr;

typedef struct {
    Window* W;
    void* P;    // Player
    void** E;
    int boundX; // For convenience
    int boundY;
    // projectiles? Could be very similar to enemies given lim
} GameWindow;

bool wmvaddch(Window* W, int y, int x, int ch);
int toOneD(int y, int x, int maxX);
bool isOccupied(GameWindow* GW, int y, int x, int xMax);
void freeGW(GameWindow* GW);
int renderMenu(Window* W, int menuWidth, char* title, char* subtitle, int numOptions, char** options); // returns selected index
void runGame(GameWindow* GW);

#endif /* MAIN_H */

