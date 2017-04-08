#define K_ENTER 10 // KEY_ENTER is defined to something else by ncurses

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

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

int toOneD(int y, int x, int maxX){ return y*maxX + x; }

void freeGW(GameWindow* GW){
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

GameWindow* setupGameWin(int yMax, int xMax){
    float relSize = 1.5; // ~1/3 of terminal should be border
    int boundY = (int)(yMax/relSize);
    int boundX = (int)(xMax/relSize);
    int borderTB = (yMax-boundY)/2;
    int borderLR = (xMax-boundX)/2;

    GameWindow *gameWin = calloc(1,sizeof(GameWindow));
    if(!gameWin){
        fprintf(stderr,"Allocation of start screen failed!");
        endwin();
        exit(EXIT_FAILURE);
    }
    gameWin->W = newwin(boundY,boundX,borderTB,borderLR);
    keypad(gameWin->W,TRUE);
    refresh();
    box(gameWin->W,0,0);
    wrefresh(gameWin->W);

    return gameWin;
}

int main(){
    initscr();
    noecho();
    curs_set(0);
    cbreak();

    int yMax, xMax, renderStatus, startHeight, startWidth;
    getmaxyx(stdscr,yMax,xMax);

    runStartScreen(startHeight=20,startWidth=80,yMax,xMax);
    GameWindow* gameWin = setupGameWin(yMax,xMax);
    addPlayer(gameWin);
    addEnemies(gameWin);
    runGame(gameWin);

    delwin(gameWin->W);
    getch();
    endwin();

    return EXIT_SUCCESS;
}

