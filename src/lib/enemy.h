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
void moveEnemyBlockLeft(GameWindow* GW);
void moveEnemyBlockRight(GameWindow* GW);
void renderEnemies(GameWindow* GW);
void derenderEnemies(GameWindow* GW);

#endif /* ENEMY_H */

