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
    Coord* loc;
    Image* img1;
    Image* img2;
};

void initializeEnemies(GameWindow* GW);
void moveEnemyLeft(GameWindow* GW, Enemy* E);
void moveEnemyRight(GameWindow* GW, Enemy* E);
void renderEnemies(GameWindow* GW);
void derenderEnemies(GameWindow* GW);
void clearEnemies(GameWindow* GW);
Coord* positionFromInd(GameWindow* GW,int ind);

#endif /* ENEMY_H */

