#ifndef ENEMY_H
#define ENEMY_H

#include <ncurses.h>
#include <stdbool.h>

#include "main.h"


// Enemy type described in terms of distance from player
// For now the UFO isn't actually implemented
typedef enum {NEAR, MEDIUM, FAR, UFO} EnemyType;

typedef struct {
    bool isAlive;
    EnemyType type;
    Coord C;
} Enemy;

void addEnemies(GameWindow* GW);
void shiftLeft(GameWindow* GW);
void shiftRight(GameWindow* GW);
void renderEnemies(GameWindow* GW);

#endif /* ENEMY_H */

