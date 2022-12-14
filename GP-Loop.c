#include <stdio.h>  
#include <stdlib.h>  
#include <time.h> 
#include <curses.h>
#include <unistd.h>
#include <string.h>
#include "Renderer.c"
#define DELAY 100000
#define SCALE 5000
#define DEFAULT 0
#define SNAKE 1
#define FOOD 2
#define SPEED1 1
#define SPEED2 3
#define SPEED3 4
#define min_x 3
#define min_y 4
#define max_x 17
#define max_y 64
#define width (max_y - min_y)
#define height (max_x - min_x)

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

int mainLoop(int difficulty) {
    // declaring snake variables //
    
    int sx = min_x + (height/2), sy = min_y + (width * 0.2), l = 1, lsim = 0, dx = 0, dy = 0, diff = difficulty, ch, pts = l,ptScale, colour;
    bool alternator = 0;  
    char* title; 

    switch(difficulty) {
   	    case 0:
   	        ptScale = 100;
            title = "DANGER NOODLE";
            colour = 0;
   	        break;
   	    case 1:
   	        ptScale = 200;
            title = "GARDEN SNAKE";
            colour = 1;
   	        break;
   	    case 2:
   	        ptScale = 400;
            title = "PIT VIPER";
            colour = 3;
   	        break;
   	    case 4:
            ptScale = 600;
            title = "BLACK MAMBA";
            colour = 2;
   	        break;
   	} 

    // declaring food variables //
    
    srand(time(0));
    int fx, fx_exp;
    int fy, fy_exp;
    fx = min_x + (height/2);
    fy = min_y + (width*0.8);

    struct Sgmnt* snake = NULL;

    clear();
    
    // drawing border and food in //
    mainBorder();

    attron(COLOR_PAIR(colour));
    drawBorder(title, min_x, max_x, min_y, max_y);
    attroff(COLOR_PAIR(colour));

    drawMeter(5, max_y + 5, diff - difficulty * 2);
    mvprintw(max_x + 1, min_y + (width/2) - 4, "score : 000");

    refresh();

    // START OF GAME LOOP //
    while(ch != '1' && sx < max_x && sx > (min_x + 1) && sy < max_y && sy > min_y){
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
            fx = 2 + min_x + rand() % (height - 2);
            fy = 2 + min_y + (rand() % ((width - 2) / 2)) * 2;
            mvprintw(max_x + 1, min_y + (width/2) - 4, "score : %d", pts);  // score

            if(((l) > 1) && ((l) % (20/(difficulty+1)) == 0) && (diff < 9)){
                diff += difficulty;
                drawMeter(5, max_y + 5, diff - difficulty);
            }
        } else {
            snake = slither(&snake, sx, sy);
        }

        if (diff > 8) {
            drawTurboMeter(5, max_y + 5, alternator);
            alternator = !alternator;
        }

        attron(COLOR_PAIR(FOOD));
        makeFood(fx_exp, fy_exp, fx, fy);
        attroff(COLOR_PAIR(FOOD));

        attron(COLOR_PAIR(SNAKE));
        l = draw(snake);
        pts = l * ptScale;
        attroff(COLOR_PAIR(SNAKE));



        if(collide(snake))
            break;
        
        usleep(DELAY - (diff * SCALE));
        
        sx += dx; // update the head position and start again
        sy += dy;
        refresh();
    }
    // END OF GAME LOOP //

    free(snake);
    return pts - ptScale;
}