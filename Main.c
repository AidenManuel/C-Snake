#include <stdio.h>  
#include <stdlib.h>  
#include <time.h> 
#include <curses.h>
#include <unistd.h>
#include "Sgmnt.h"
#include "Scoreboard.h"
#include "GP-Loop.c"
#include "AI-Loop.c"
#include "Animations.c"
#define DELAY 100000
#define BigDELAY 400000
#define SNAKE 1
#define FOOD 2
#define SPEED1 1
#define SPEED2 3
#define SPEED3 4
#define min_x 3
#define min_y 4
#define max_x 17
#define max_y 64

/////////////////////////////////////////////////////////////////////////////////////////////
//    ___                    _                       ___                     _             //
//   | _ \    _ _    ___    | |_     ___     ___    / __|   _ _     __ _    | |__    ___   //
//   |  _/   | '_|  / _ \   |  _|   / _ \   |___|   \__ \  | ' \   / _` |   | / /   / -_)  //
//  _|_|_   _|_|_   \___/   _\__|   \___/   _____   |___/  |_||_|  \__,_|   |_\_\   \___|  //
//_| """ |_|"""""|_|"""""|_|"""""|_|"""""|_|     |_|"""""|_|"""""|_|"""""|_|"""""|_|"""""| //
//"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-' //
/////////////////////////////////////////////////////////////////////////////////////////////
// This is a small and simple project I undertook as an introduction to C and the curses   //
// library. I took inspiration from my professor, Dr. Jyong-Kyou Kim, and got help with    //
// syntax courtesy of the internet. Other than that, all my code is original, included my  //
// funky matrix method of storing the snake. Snake is of course not an original idea, and  //
// this is my humble attempt at a recreation of the classic game.                          //
/////////////////////////////////////////////////////////////////////////////////////////////
// Code by : Aiden Manuel              //              ASCII art courtesy of : patorjk.com //
/////////////////////////////////////////////////////////////////////////////////////////////


///// CURSER INIT /////

void initBruv() {  // Initializes all necessary curser things and madoodles
    initscr();
    noecho();
    curs_set(FALSE);
    cbreak();              // I genuinely don't know what most of these do, I just
    nodelay(stdscr, TRUE); // took them off of Dr. Kim's class example ¯\_(ツ)_/¯
    raw();

    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }

    start_color();
    init_pair(SNAKE, COLOR_GREEN, COLOR_BLACK);
    init_pair(FOOD, COLOR_RED, COLOR_BLACK);
    init_pair(SPEED2, COLOR_BLUE, COLOR_BLACK);
    init_pair(SPEED3, COLOR_RED, COLOR_RED);
    init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(6, COLOR_CYAN, COLOR_CYAN);
}

///// MAIN METHOD /////

int main() {
    
    // Creating Scores File
    FILE* fp = fopen("scores.txt", "rw");

    if(fp == NULL){
        printf("scores.txt DOES NOT EXIST!!!");
        exit(1);
    }   

    fclose(fp);

    int choice, difficulty;
    struct Player* nullFella = createPlayer(0, 'n', 'f', 0);
    nullFella = loadFile(nullFella);

    // Curses Init
    initBruv();

    // Play animation only on startup
    introAnimation();

    // The Program Loop
    while(choice != 5){
        choice = drawMenu();
        switch(choice) {
            case 1:
                difficulty = drawDifficulty();
                int l = mainLoop(difficulty);
                usleep(DELAY);
                mvprintw(max_x / 2, max_y / 2 - 3, "D E A D");
                mvprintw(max_x / 2 + 1, max_y / 2 - 12, "press ANY KEY to continue");
                refresh();
                nullFella = gameOver(l, fp, nullFella, difficulty);
                break;
            case 2:
                scoreboard(fp);
                break;
            case 3:
                AILoop();
                break;
            case 4:
                if(drawConfirm()) {
                    fp = fopen("scores.txt", "w");
                    fprintf(fp, "\n");
                    fclose(fp);
                    free(nullFella);
                    struct Player* nullFella = createPlayer(0, 'n', 'f', 0);
                }
                break;
            case 5:
                break;
        }
    }

    // End of Program
    endwin();
    free(nullFella);
    return 0;
}
