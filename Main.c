#include <stdio.h>  
#include <stdlib.h>  
#include <time.h> 
#include <curses.h>
#include <unistd.h>
#include "Sgmnt.h"
#include "GP-Loop.c"
#include "Animations.c"
#define DELAY 100000
#define BigDELAY 400000
#define max_x 15
#define max_y 60

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
   keypad(stdscr, TRUE);
}

///// MAIN METHOD /////

int main() {
    int choice;

    // Creating Scores File
    FILE* fp = fopen("scores.txt", "w");
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0)
        fprintf(fp, "\t._______________________________.\n\t|    INITIALS   |     SCORE     |");
    fclose(fp);

    // Curses Init
    initBruv();

    // Play animation only on startup
    introAnimation();

    // The Program Loop
    while(choice != 4){
        choice = drawMenu();
        switch(choice) {
            case 1:
                int l = mainLoop();
                mvprintw(max_x / 2, max_y / 2 - 3, "D E A D");
                refresh();
                fp = gameOver(l, fp);
                break;
            case 2:
                scoreboard(fp);
                break;
            case 3:
                instructions();
                break;
            case 4:
                break;
        }
    }

    // End of Program
    endwin();
    return 0;
}
