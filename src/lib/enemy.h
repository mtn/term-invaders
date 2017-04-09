#ifndef ENEMY_H
#define ENEMY_H

#include <ncurses.h>
#include <stdbool.h>

#include "main.h"


// Enemy type described in terms of distance from player
// For now the UFO isn't actually implemented
typedef enum {NEAR, MEDIUM, FAR, UFO} EnemyType;

// Enemies don't require individual positions
typedef struct {
    bool isAlive;
    EnemyType type;
} Enemy;

void initializeEnemies(GameWindow* GW);
void shiftEnemiesLeft(GameWindow* GW);
void shiftEnemiesRight(GameWindow* GW);
void clearEnemies(GameWindow* GW);
void renderEnemies(GameWindow* GW);
void renderNear(GameWindow* GW, int ind);
void renderMedium(GameWindow* GW, int ind);
void renderFar(GameWindow* GW, int ind);
Coord* positionFromInd(GameWindow* GW,int ind);

#endif /* ENEMY_H */

