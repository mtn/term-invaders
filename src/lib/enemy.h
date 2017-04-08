#ifndef ENEMY_H
#define ENEMY_H

#include <ncurses.h>
#include <stdbool.h>

#include "main.h"


typedef struct {
    bool isAlive;
    Coord C;
} Enemy;

void addEnemies(GameWindow* GW);
void addPlayer(GameWindow* GW);
void shiftLeft(GameWindow* GW);
void shiftRight(GameWindow* GW);

#endif /* ENEMY_H */

