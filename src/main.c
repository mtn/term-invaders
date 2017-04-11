#define K_ENTER            10 // KEY_ENTER is defined to something else by ncurses
#define MIN_TERM_WIDTH    140
#define MIN_TERM_HEIGHT    40
#define MAX_X_DIM          12
#define MAX_Y_DIM           4
#define NUM_IMAGES          9

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "lib/main.h"
#include "lib/enemy.h"
#include "lib/player.h"

bool wmvaddch(Window* W, int y, int x, int ch){
    int xMax, yMax;
    getmaxyx(W,yMax,xMax);
    if(yMax < y || xMax < x) return false;

    wmove(W,y,x);
    waddch(W,ch);
    return true;
}

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
    };
    for(int i = 0; i < 2; ++i)
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
    endwin();
}

GameWindow* setupGame(int yMax, int xMax){
    float relSize = 1.1; // ~90% of terminal should be border
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
    gameWin->W = newwin(boundY,boundX,borderTB,borderLR);
    keypad(gameWin->W,TRUE);
    refresh();
    box(gameWin->W,0,0);
    wrefresh(gameWin->W);

    halfdelay(1); // The game proceeds in the absence of input after 1/10 sec

    return gameWin;
}

void renderEnemies(GameWindow* GW){
    // TODO add sprite alternation
    EnemyLL* e = GW->ELL;
    while(e){
        // TODO better naming lol
        renderImg(GW,e->E->img1,e->E->loc->y,e->E->loc->x);
        e = e->next;
    }
    wrefresh(GW->W);
}

void renderPlayer(GameWindow* GW){
    renderImg(GW,GW->P->img,GW->P->loc->y,GW->P->loc->x);
    wrefresh(GW->W);
}

void renderImg(GameWindow* GW, Image* img, int y, int x){
    for(int i = 0; i < img->yDim; i++){
        int shift = (int)((img->xDim-strlen(img->img[i]))/2); // bad naming
        mvwaddstr(GW->W,y+i,x+shift,img->img[i]);
    }
    wrefresh(GW->W);
}

void derenderImg(GameWindow* GW, Image* img, int y, int x){
    for(int i = 0; i < img->xDim; i++){
        for(int j = 0; j < img->yDim; j++){
            mvwaddch(GW->W,y+j,x+i,' ');
        }
    }
    wrefresh(GW->W);
}

void runGame(GameWindow* gameWin){
    initializePlayer(gameWin);
    initializeEnemies(gameWin);

    int choice;
    while((gameWin->P)->health > 0){
        renderPlayer(gameWin);
        renderEnemies(gameWin);

        choice = getch();
        switch(choice){
            case KEY_LEFT:
                movePlayerLeft(gameWin);
                break;
            case KEY_RIGHT:
                movePlayerRight(gameWin);
                break;
        }
        renderEnemies(gameWin);

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

void loadImages(GameWindow* GW){
    FILE *fp;
    int xDim, yDim;
    Images *images  = malloc(sizeof(Images));

    images->player = malloc(sizeof(Image));
    fp = fopen("../img/player.txt","r");
    fscanf(fp,"%d,%d",&xDim,&yDim);
    for(int i = 0; i < yDim; i++)
        fscanf(fp,"%s",images->player->img[i]);
    images->player->xDim = xDim;
    images->player->yDim = yDim;


    images->nearEnemy1 = malloc(sizeof(Image));
    images->nearEnemy2 = malloc(sizeof(Image));
    fp = fopen("../img/nearEnemy.txt","r");
    fscanf(fp,"%d,%d",&xDim,&yDim);
    for(int i = 0; i < yDim; i++)
        fscanf(fp,"%s",images->nearEnemy1->img[i]);
    images->nearEnemy1->xDim = xDim;
    images->nearEnemy1->yDim = yDim;
    for(int i = 0; i < yDim; i++)
        fscanf(fp,"%s",images->nearEnemy2->img[i]);
    images->nearEnemy2->xDim = xDim;
    images->nearEnemy2->yDim = yDim;


    images->midEnemy1 = malloc(sizeof(Image));
    images->midEnemy2 = malloc(sizeof(Image));
    fp = fopen("../img/midEnemy.txt","r");
    fscanf(fp,"%d,%d",&xDim,&yDim);
    for(int i = 0; i < yDim; i++)
        fscanf(fp,"%s",images->midEnemy1->img[i]);
    images->midEnemy1->xDim = xDim;
    images->midEnemy1->yDim = yDim;
    for(int i = 0; i < yDim; i++)
        fscanf(fp,"%s",images->midEnemy2->img[i]);
    images->midEnemy2->xDim = xDim;
    images->midEnemy2->yDim = yDim;

    images->farEnemy1 = malloc(sizeof(Image));
    images->farEnemy2 = malloc(sizeof(Image));
    fp = fopen("../img/farEnemy.txt","r");
    fscanf(fp,"%d,%d",&xDim,&yDim);
    for(int i = 0; i < yDim; i++)
        fscanf(fp,"%s",images->farEnemy1->img[i]);
    images->farEnemy1->xDim = xDim;
    images->farEnemy1->yDim = yDim;
    for(int i = 0; i < yDim; i++)
        fscanf(fp,"%s",images->farEnemy2->img[i]);
    images->farEnemy2->xDim = xDim;
    images->farEnemy2->yDim = yDim;

    GW->images = images;
}

int main(){
    int yMax, xMax, renderStatus, startHeight, startWidth;
    initCurses();
    getmaxyx(stdscr,yMax,xMax);

    runStartScreen(startHeight=20,startWidth=80,yMax,xMax);
    GameWindow* gameWin = setupGame(yMax,xMax);
    runGame(gameWin);
    cbreak();

    delwin(gameWin->W);
    getch();
    endwin();

    return EXIT_SUCCESS;
}

