#ifndef ENEMY_H
#define ENEMY_H

#include <ncurses.h>
#include <stdbool.h>

#include "main.h"


struct Enemy {
    Coord* loc;
    Image* img1;
    Image* img2;
};

void initializeEnemies(GameWindow* GW);
void moveEnemyBlockLeft(GameWindow* GW);
void moveEnemyBlockRight(GameWindow* GW);
bool moveEnemyBlockDown(GameWindow* GW);
void renderEnemies(GameWindow* GW);
void checkLeftBound(GameWindow* GW);
void checkRightBound(GameWindow* GW);
void derenderEnemies(GameWindow* GW);
int getBlockWidth(int lCol, int rCol);
bool checkShiftDir(GameWindow* GW);

#endif /* ENEMY_H */

