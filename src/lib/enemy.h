#ifndef ENEMY_H
#define ENEMY_H

#include <ncurses.h>
#include <stdbool.h>

#include "main.h"


struct EnemyLL {
    Enemy* E;
    struct EnemyLL* next;
    struct EnemyLL* prev;
};

// Enemies don't require individual positions
struct Enemy {
    bool isAlive;
    Coord* c;
    Image* img;
};

EnemyLL* initializeEnemies(GameWindow* GW);
void shiftEnemiesLeft(GameWindow* GW);
void shiftEnemiesRight(GameWindow* GW);
void clearEnemies(GameWindow* GW);
void renderEnemies(GameWindow* GW);
void renderNear(GameWindow* GW, int ind);
void renderMedium(GameWindow* GW, int ind);
void renderFar(GameWindow* GW, int ind);
Coord* positionFromInd(GameWindow* GW,int ind);

#endif /* ENEMY_H */

