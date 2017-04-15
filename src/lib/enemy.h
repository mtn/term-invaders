#ifndef ENEMY_H
#define ENEMY_H

#include <ncurses.h>
#include <stdbool.h>

#include "main.h"


struct EnemyLL {
    Enemy* E;
    EnemyLL* next;
    EnemyLL* prev;
};

struct Enemy {
    Coord* loc;
    Enemy* above;
    Enemy* below;
    Image* img1;
    Image* img2;
};

void initializeEnemies(GameWindow* GW);
void moveEnemyBlockLeft(GameWindow* GW);
void moveEnemyBlockRight(GameWindow* GW);
bool moveEnemyBlockDown(GameWindow* GW);
void renderEnemies(GameWindow* GW);
void derenderEnemies(GameWindow* GW);

#endif /* ENEMY_H */

