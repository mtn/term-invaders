#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lib/main.h"
#include "lib/enemy.h"
#include "lib/player.h"
#include "lib/img.h"

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

void runGame(GameWindow* gameWin){
    initializePlayer(gameWin);
    initializeEnemies(gameWin);
    renderEnemiesAndProjectiles(gameWin);
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

            renderEnemiesAndProjectiles(gameWin);
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

int hashFunction(char* imageName){
    int sum = 0;
    for(int i = 0; i < strlen(imageName); i++){
        sum += (int)imageName[i];
    }
    return sum;
}

int main(){
    int yMax, xMax, startHeight, startWidth;
    srand(time(NULL));
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

