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

struct EnemyProjectiles {
    Projectile* P;
    EnemyProjectiles* next;
    EnemyProjectiles* prev;
};

struct Projectile {
    Coord* loc;
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
void derenderEnemies(GameWindow* GW);
void fireProjectile(GameWindow* GW);
void renderEnemiesandProjectiles(GameWindow* GW);

#endif /* ENEMY_H */

