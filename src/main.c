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
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lib/main.h"
#include "lib/enemy.h"
#include "lib/player.h"

void freeGW(GameWindow* GW){
    // TODO
    delwin(GW->W);
    free(GW);
}

int renderMenu(Window* W, int menuWidth, char* title, char* subtitle, int numOptions, char** options){
    wattron(W,A_REVERSE);
    mvwprintw(W,1,(menuWidth-strlen(title))/2,title);
    wattroff(W,A_REVERSE);
    mvwprintw(W,3,2,subtitle);
    int highlight = 0;
    while(true){
        for(int i = 0; i < numOptions; ++i){
            if(i==highlight){
                wattron(W,A_BOLD);
                mvwprintw(W,5+i,5,"*");
            }
            else
                mvwprintw(W,5+i,5," ");
            mvwprintw(W,5+i,6,options[i]);
            wattroff(W,A_BOLD);
        }
        int choice = wgetch(W);

        switch(choice){
            case KEY_DOWN:
                if(highlight < 2) highlight++;
                break;
            case KEY_UP:
                if(highlight > 0) highlight--;
            default:
                break;
        }
        refresh();
        // wgetch 10  -> enter -> no more rendering
        wrefresh(W);
        if(choice==K_ENTER) break;
    }
    return highlight;
}

void runStartScreen(int startHeight,int startWidth, int yMax, int xMax){
    if(yMax <= startHeight || xMax <= startWidth){
        printw("Terminal window too small!");
        getch();
        endwin();
        exit(EXIT_FAILURE);
    }

    Window *startScreen= newwin(startHeight,startWidth,(yMax-startHeight)/2,(xMax-startWidth)/2);
    if(!startScreen){
        fprintf(stderr,"Allocation of start screen failed!");
        endwin();
        exit(EXIT_FAILURE);
    }

    refresh();
    box(startScreen,0,0);

    wattron(startScreen,A_REVERSE);
    char* title = "TermInvaders";
    mvwprintw(startScreen,1,(startWidth-strlen(title))/2,title);
    wattroff(startScreen,A_REVERSE);

    char* instructions[2] = {
        "Move your ship with the arrow keys",
        "Press R to pause and R to resume",
    }; for(int i = 0; i < 2; ++i)
        mvwprintw(startScreen,3 + i,(startWidth-strlen(instructions[i]))/2,instructions[i]);

    char* pressEnter = "Press enter to continue...";
    mvwprintw(startScreen,12,(startWidth-strlen(pressEnter))/2,pressEnter);
    // TODO: add snazzy art
    wrefresh(startScreen);

    int choice;
    do{
        choice = getch();
    } while(choice != K_ENTER);

    delwin(startScreen);
}

GameWindow* setupGame(int yMax, int xMax){
    float relSize = 1.1; // ~90% of terminal should be occupied
    int boundY = (int)(yMax/relSize);
    int boundX = (int)(xMax/relSize);
    int borderTB = (yMax-boundY)/2;
    int borderLR = (xMax-boundX)/2;

    // Compare to minimum dimensions, which are based on size of enemies to be displayed
    if(boundY < MIN_TERM_HEIGHT || boundX < MIN_TERM_WIDTH){
        clear();
        printw("Terminal size too small! Resize window to play game!");
        getch();
        endwin();
        exit(EXIT_FAILURE);
    }

    GameWindow *gameWin = calloc(1,sizeof(GameWindow));
    if(!gameWin){
        fprintf(stderr,"Allocation of start screen failed!");
        endwin();
        exit(EXIT_FAILURE);
    }
    gameWin->boundX = boundX;
    gameWin->boundY = boundY;
    gameWin->state = 0;
    gameWin->shiftDir = RIGHT;
    gameWin->W = newwin(boundY,boundX,borderTB,borderLR);
    keypad(gameWin->W,TRUE);
    nodelay(gameWin->W,TRUE);
    refresh();
    box(gameWin->W,0,0);
    wrefresh(gameWin->W);

    return gameWin;
}

// i doesn't matter
int imgShift(Image* img, int i){
    return (int)((img->xDim-strlen(img->img[i]))/2); // bad naming
}

void renderImg(GameWindow* GW, Image* img, int y, int x){
    int shift;
    for(int i = 0; i < img->yDim; i++){
        shift = imgShift(img,i);
        mvwaddstr(GW->W,y+i,x+shift,img->img[i]);
    }
}

void derenderImg(GameWindow* GW, Image* img, int y, int x){
    for(int i = 0; i < img->xDim; i++)
        for(int j = 0; j < img->yDim; j++)
            mvwaddch(GW->W,y+j,x+i,' ');
}

void runGame(GameWindow* gameWin){
    initializePlayer(gameWin);
    initializeEnemies(gameWin);
    renderEnemiesandProjectiles(gameWin);
    renderPlayer(gameWin);

    int choice, random;
    double secsElapsed, temp;
    clock_t t = clock();
    while((gameWin->P)->health > 0){
        temp = clock() - t;
        secsElapsed = ((double)temp)/CLOCKS_PER_SEC; // seconds
        if(secsElapsed >= SHIFT_INTERVAL){
            if(gameWin->shiftDir == LEFT) moveEnemyBlockLeft(gameWin);
            else moveEnemyBlockRight(gameWin);
            random = rand() % 2; // 1/2 chance of enemy shot being fired
            if(random) fireProjectile(gameWin);

            renderEnemiesandProjectiles(gameWin);
            gameWin->state = !gameWin->state;
            t = clock();
        }

        choice = wgetch(gameWin->W);
        switch(choice){
            case KEY_LEFT:
                movePlayerLeft(gameWin);
                derenderPlayer(gameWin);
                renderPlayer(gameWin);
                break;
            case KEY_RIGHT:
                movePlayerRight(gameWin);
                derenderPlayer(gameWin);
                renderPlayer(gameWin);
                break;
            case ERR:
                break;
        }
        wrefresh(gameWin->W);
    }

    cbreak();
    getch();
}

void initCurses(){
    initscr();
    noecho();
    curs_set(0);
    cbreak();
    keypad(stdscr,TRUE);

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
}

Image* loadImage(char* filePath){
    int xDim, yDim;
    Image* img = malloc(sizeof(Image));
    FILE* fp = fopen(filePath,"r");
    fscanf(fp,"%d,%d",&xDim,&yDim);

    char** imgStr = malloc(yDim*sizeof(char*));
    for(int i = 0; i < yDim; i++){
        imgStr[i] = malloc(sizeof(char)*(xDim+1));
        fscanf(fp,"%s",imgStr[i]);
    }
    img->img = imgStr;
    img->xDim = xDim;
    img->yDim = yDim;

    return img;
}

void loadImages(GameWindow* GW){
    Images *images  = malloc(sizeof(Images));

    images->player = loadImage("img/player.txt");
    images->nearEnemy1 = loadImage("img/nearEnemy1.txt");
    images->nearEnemy2 = loadImage("img/nearEnemy2.txt");
    images->midEnemy1 = loadImage("img/midEnemy1.txt");
    images->midEnemy2 = loadImage("img/midEnemy2.txt");
    images->farEnemy1 = loadImage("img/farEnemy1.txt");
    images->farEnemy2 = loadImage("img/farEnemy2.txt");

    GW->images = images;
}

int main(){
    int yMax, xMax, renderStatus, startHeight, startWidth;
    srand(time(NULL));
    initCurses();
    getmaxyx(stdscr,yMax,xMax);

    runStartScreen(startHeight=20,startWidth=80,yMax,xMax);
    GameWindow* gameWin = setupGame(yMax,xMax);
    loadImages(gameWin);
    runGame(gameWin);
    cbreak();

    delwin(gameWin->W);
    getch();
    endwin();

    return EXIT_SUCCESS;
}

