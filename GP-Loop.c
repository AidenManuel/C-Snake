#include <stdio.h>  
#include <stdlib.h>  
#include <time.h> 
#include <curses.h>
#include <unistd.h>
#include <string.h>
#include "Renderer.c"
#define DELAY 100000
#define DIFF 5000
#define SNAKE 1
#define FOOD 2
#define SPEED1 1
#define SPEED2 3
#define SPEED3 4
#define max_x 15
#define max_y 60

///// MAKE FOOD /////

void makeFood(int fx_exp, int fy_exp, int fx, int fy) {
    mvprintw(fx_exp, fy_exp, " ");
    mvaddch(fx, fy, ACS_DIAMOND);
    refresh();
}

///// SNAKE x FOOD COLLISION

int foodCollide(int fx, int fy, int sx, int sy) {
   if (fx == sx && fy == sy)
     return 1;
   return 0;
}

int mainLoop() {
    // declaring snake variables //
    
    int sx = max_x/2, sy = max_y * 0.2, l = 1, lsim = 0, dx = 0, dy = 0, diff = 0, ch;
    
    // declaring food variables //
    
    srand(time(0));
    int fx, fx_exp;
    int fy, fy_exp;
    fx = max_x/2;
    fy = max_y * 0.8;

    struct Sgmnt* snake = NULL;

    clear();
    
    // drawing border and food in //
    drawBorder("C-SNAKE", 0, max_x, 0, max_y);
    drawMeter(5, max_y + 5, diff);
    mvprintw((max_x - 0) + 1 + 0, 0 + max_y / 2 - 4, "score : 000");

    refresh();
    while(ch != '1' && sx < max_x && sx > 1 && sy < max_y && sy > 0){
        ch = getch();  
        switch(ch) {   // This switch case handles player controls
        case 'a':
        if(dy != 2) {
            dx = 0;
            dy = -2; // left
        }
        break;
        case 'd':
        if(dy != -2) {
            dx = 0;
            dy = 2;  // right
        }
        break;
        case 'w':
        if(dx != 1) {
            dy = 0;
            dx = -1; // up
        }
        break;
        case 's':
        if(dx != -1) {
            dy = 0;
            dx = 1;  // down
        }
        break;
        }

        // detect snake x food collision //
        if(foodCollide(fx, fy, sx, sy)) {
            snake = eat(&snake, sx, sy);
            fx_exp = fx;
            fy_exp = fy;
            fx = 2 + rand() % (max_x - 2);
            fy = 2 + (rand() % ((max_y - 2) / 2)) * 2;
            mvprintw((max_x - 0) + 1 + 0, 0 + max_y / 2 - 4, "score : %d", l);  // score

            if(((l/100) > 1) && ((l/100) % 10 == 0) && (diff < 8)){
                diff += 1;
                drawMeter(5, max_y + 5, diff);
            }
        } else {
            snake = slither(&snake, sx, sy);
        }

        attron(COLOR_PAIR(FOOD));
        makeFood(fx_exp, fy_exp, fx, fy);
        attroff(COLOR_PAIR(FOOD));

        attron(COLOR_PAIR(SNAKE));
        l = draw(snake);
        attroff(COLOR_PAIR(SNAKE));

        if(collide(snake))
            break;
        
        usleep(DELAY - (diff * DIFF));
        
        sx += dx; // update the head position and start again
        sy += dy;
        refresh();
    }
    return l;
}