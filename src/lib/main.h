#ifndef MAIN_H
#define MAIN_H

#define LEFT                0
#define RIGHT               1
#define MAX_ENEMIES        55
#define K_ENTER            10 // KEY_ENTER is defined to something else by ncurses
#define MIN_TERM_WIDTH    140
#define MIN_TERM_HEIGHT    40
#define MAX_X_DIM          12
#define MAX_Y_DIM           4
#define NUM_IMAGES          9
#define NUM_COLS            7
#define NUM_ROWS            5
#define SHIFT_INTERVAL    0.5

#include <ncurses.h>
#include <stdbool.h>


typedef struct EnemyProjectiles EnemyProjectiles;
typedef struct Projectile Projectile;
typedef struct EnemyLL EnemyLL;
typedef struct Enemy Enemy;
typedef struct Player Player;
typedef struct Image Image;
typedef struct ImgTableElem ImgTableElem;

typedef WINDOW Window;
typedef ImgTableElement** ImgTable;

typedef struct {
    int x;
    int y;
} Coord, *CoordPtr;

typedef struct {
    Window* W;
    Player* P;
    EnemyLL* ELL;
    EnemyProjectiles* EP;
    int enemyHorizOffset;
    int enemyVertOffset;

    ImgTable images;
    int state;           // 0 or 1 for alternating animations
    int shiftDir;        // Shift direction of enemy "block"

    int boundX;          // For convenience
    int boundY;
    // projectiles? Could be very similar to enemies given lim
} GameWindow;

void freeGW(GameWindow* GW);
int renderMenu(Window* W, int menuWidth, char* title, char* subtitle, int numOptions, char** options); // returns selected index
void runGame(GameWindow* GW);

#endif /* MAIN_H */

