#ifndef PLAYER_H
#define PLAYER_H

#include <ncurses.h>
#include <stdbool.h>

#include "main.h"


typedef struct {
    int health;
    Coord* loc;
} Player;

void addPlayer(GameWindow* GW);
void moveLeft(GameWindow* GW);
void moveRight(GameWindow* GW);
void shootProjectile(GameWindow* GW);
void renderPlayer(GameWindow* GW);

#endif /* PLAYER_H */

