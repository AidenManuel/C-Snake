#include <stdio.h>  
#include <stdlib.h>  
#include <time.h> 
#include <curses.h>
#include <unistd.h>
#include <string.h>
#include "Renderer.c"
#define DELAY 100000
#define max_x 15
#define max_y 60

///// MAKE FOOD /////

void makeFood(int fx, int fy) {
   mvprintw(fx, fy, "F");
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
    
    int sx = max_x/2, sy = max_y * 0.2, l = 1, lsim = 0, dx = 0, dy = 0, ch;
    
    // declaring food variables //
    
    srand(time(0));
    int fx;
    int fy;
    fx = max_x/2;
    fy = max_y * 0.8;

    struct Sgmnt* snake = NULL;

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
        clear();
        
        // drawing border and food in //
        drawBorder("C-SNAKE", l, 0, max_x, 0, max_y);

        makeFood(fx, fy);
        
        // detect snake x food collision //
        if(foodCollide(fx, fy, sx, sy)) {
            snake = eat(&snake, sx, sy);
            fx = 2 + rand() % (max_x - 2);
            fy = 2 + (rand() % ((max_y - 2) / 2)) * 2;
        } else {
            snake = slither(&snake, sx, sy);
        }

        l = draw(snake);
        
        if(collide(snake))
            break;

        usleep(DELAY);
        
        sx += dx; // update the head position and start again
        sy += dy;
    }
    return l;
}