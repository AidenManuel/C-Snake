#include <stdio.h>  
#include <stdlib.h>  
#include <time.h> 
#include <curses.h>
#include <unistd.h>
#include <string.h>
#define AIDELAY 100000
#define SCALE 5000
#define SNAKE 1
#define FOOD 2
#define SPEED1 1
#define SPEED2 3
#define SPEED3 4
#define min_x 1
#define min_y 1
#define max_x 20
#define max_y 80
#define width (max_y - min_y)
#define height (max_x - min_x)

///// MAKE FOOD /////

void AImakeFood(int fx_exp, int fy_exp, int fx, int fy) {
    mvprintw(fx_exp, fy_exp, " ");
    mvaddch(fx, fy, ACS_DIAMOND);
    refresh();
}

///// SNAKE x FOOD COLLISION

int AIfoodCollide(int fx, int fy, int sx, int sy) {
   if (fx == sx && fy == sy)
     return 1;
   return 0;
}

void AILoop() {
    int ch, speed = 1;
    
    while(ch != '\n'){
        // declaring AIsnake variables //
        int sx = min_x + (height/2), sy = min_y + (width * 0.2) + 2, l = 1, lsim = 0, dx = 0, dy = 0;
        bool alternator = 0;

        // declaring food variables //
        
        srand(time(0));
        int fx, fx_exp;
        int fy, fy_exp;
        fx = min_x + (height/2);
        fy = min_y + (width*0.8);

        struct Sgmnt* AIsnake = NULL;

        clear();
        
        // drawing border in //
        mainBorder();

        refresh();

        ch = NULL;
        while(ch != '\n'){
            instructions();
            ch = getch();

            if(dy != 2 && sy > fy) {
                dx = 0;
                dy = -2; // left
            }else if(dy != -2 && sy < fy) {
                dx = 0;
                dy = 2;  // right
            }else if(dx != 1 && sx > fx) {
                dy = 0;
                dx = -1; // up
            }else if(dx != -1 && sx < fx) {
                dy = 0;
                dx = 1;  // down
            }

            // detect snake x food collision //
            if(AIfoodCollide(fx, fy, sx, sy)) {
                AIsnake = eat(&AIsnake, sx, sy);
                fx_exp = fx;
                fy_exp = fy;
                fx = 2 + min_x + rand() % (height - 2);
                fy = min_y + (rand() % ((width - 2) / 2)) * 2 + 1;
            } else {
                AIsnake = slither(&AIsnake, sx, sy);
            }

            attron(COLOR_PAIR(FOOD));
            AImakeFood(fx_exp, fy_exp, fx, fy);
            attroff(COLOR_PAIR(FOOD));

            attron(COLOR_PAIR(SNAKE));
            l = draw(AIsnake);
            attroff(COLOR_PAIR(SNAKE));
            
            if(collide(AIsnake) || min_x == sx || sx > max_x || min_y == sx || sy > max_y )
                break;

            switch(ch) {
                case 't':
                    if (speed != 20)
                        speed++;
                    break;
                case 'g':
                    if (speed != 1)
                        speed--;
                    break;
            }

            usleep(AIDELAY/speed);
            
            sx += dx; // update the head position and start again
            sy += dy;
            refresh();
        }
    }
    return;
}