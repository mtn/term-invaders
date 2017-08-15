#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

#include "main.h"


struct Player {
    int health;
    Coord* loc;
    Image* img;
};

void initializePlayer(GameWindow* GW);
void movePlayerLeft(GameWindow* GW);
void movePlayerRight(GameWindow* GW);
void shootProjectile(GameWindow* GW);
void clearPlayer(GameWindow* GW);
void renderPlayer(GameWindow* GW);
void derenderPlayer(GameWindow* GW);

#endif /* PLAYER_H */

