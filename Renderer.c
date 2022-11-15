#define DELAY 100000
#define max_x 15
#define max_y 60
#define max_l (max_x * max_y)
#define SNAKE 1
#define FOOD 2
#define SPEED1 1
#define SPEED2 3
#define SPEED3 4

int choice = 0, selector = 8;

///// DRAW MENU /////

int drawMenu() {
   clear();
   mvprintw(1, 1, " C C C       s s .   N     N     A     K   K   E E E  ");
   mvprintw(2, 1, " C           s       N N   N   A   A   K   K   E      ");
   mvprintw(3, 1, " C           s s s   N   N N   A A A   K K     E E    ");
   mvprintw(4, 1, " C               s   N     N   A   A   K   K   E      ");
   mvprintw(5, 1, " C C C   .   S s s   N     N   A   A   K   K   E E E  ");
   mvprintw(8, 1, "                    MODE  SELECT");
   mvprintw(10, 1, "                     SCOREBOARD");
   mvprintw(12, 1, "                    INSTRUCTIONS");
   mvprintw(14, 1, "                        QUIT");
   while(choice == 0){
   	mvprintw(selector, 15, "*");
   	switch(getch()) {
   	   case 'w':
	         if(selector != 8){
               mvprintw(selector, 15, " ");
               selector -= 2;
            }
   	      break;
   	   case 's':
   	      if(selector != 14){
               mvprintw(selector, 15, " ");
   	         selector +=2;
            }
   	      break;
   	   case '\n':
   	      switch(selector) {
   	      case 8:
   	         return 1;
   	         break;
   	      case 10:
   	         return 2;
   	         break;
   	      case 12:
   	         return 3;
   	         break;
   	      case 14:
               return 4;
   	         break;
   	      }
   	      break;
         refresh();
   	}
    usleep(DELAY);
   }
}

///// DRAW BORDER /////

void drawBorder(char* title, int x1, int x2, int y1, int y2) {  // Draws the box which is representative of the play area
    int b_x = x2 - x1, b_y = y2 - y1;
    mvprintw(x1, y1 + b_y / 2 - (strlen(title) / 2), "%s", title);
    
    mvaddch(x1+1, y1, ACS_ULCORNER);
    for(int y = 1; y < b_y; y++){
        mvaddch(x1+1, y + y1, ACS_HLINE);              // top border
    }
    mvaddch(x1+1, y2, ACS_URCORNER);

    for(int x = 2; x < b_x; x++){
        mvaddch(x + x1, y1, ACS_VLINE);             // side walls
        mvaddch(x + x1, b_y + y1, ACS_VLINE);
    }

    mvaddch(b_x + x1, y1, ACS_LLCORNER);
    for(int y = 1; y < b_y; y++){
        mvaddch(b_x + x1, y + y1, ACS_HLINE);   // bottom border
    }
    mvaddch(b_x + x1, y2, ACS_LRCORNER);
}

///// DIFFICULTY METER /////

void drawMeter(int x, int y, int diff){
    drawBorder("SPEED", x, x+10, y, y+3);
    for(int i = 9; i > (9 - diff); i--){
        if (i > 7)
            attron(COLOR_PAIR(SPEED1));
        else if (i > 5)
            attron(COLOR_PAIR(SPEED2));
        else if (i > 0)
            attron(COLOR_PAIR(SPEED3));
        mvaddch(x + i, y + 1, ACS_CKBOARD);
        mvaddch(x + i, y + 2, ACS_CKBOARD);
        if (i > 7)
            attroff(COLOR_PAIR(SPEED1));
        else if (i > 5)
            attroff(COLOR_PAIR(SPEED2));
        else if (i > 0)
            attroff(COLOR_PAIR(SPEED3));
    }
}

///// GAME OVER /////

FILE* gameOver(int score, FILE* fp) {
    char initials[2], temp;
    int i = 0;
    clear();
    getchar();
    mvprintw(max_x/2 - 2, 3, "G G G    A    M       M  E E E       O     V   V   E E E   R R");
    mvprintw(max_x/2 - 1, 3, "G      A   A  M M   M M  E         O   O   V   V   E       R   R");
    mvprintw(max_x/2, 3,     "G      A A A  M   M   M  E E       O   O   V   V   E E     R R ");
    mvprintw(max_x/2 + 1, 3, "G   G  A   A  M       M  E         O   O   V   V   E       R   R");
    mvprintw(max_x/2 + 2, 3, "G G G  A   A  M       M  E E E       O       V     E E E   R   R");
    mvprintw(max_x/2 + 6, 6, "Enter Your Initials: XX");
    usleep(DELAY);
    refresh();

    while(i < 2) {
        temp = getchar();
        if(temp == 13){
            mvprintw(0, 0, "%c-", temp);
            refresh();
            initials[i] = temp;
            i++;
        }
    }
    
    mvprintw(max_x/2 + 6, 27, "%s", initials);
    mvprintw(max_x/2 + 7, 6, "SCORE %d", score - 100);
    refresh();

    fp = fopen("scores.txt", "a");
    char buf[BUFSIZ];
    fprintf(fp, "\n   %s             %d", initials, score - 100);
    fclose(fp);

    getchar();
    return fp;
}

///// DRAW SCOREBOARD /////

void scoreboard(FILE* f) {
    int sx1 = 3, sx2 = sx1+1, sy1 = 10, sy2 = sy1+30;

    clear();
    char str[250];
    f = fopen("scores.txt", "rw");
    while(fgets(str, 250, f) != NULL){
            mvprintw(sx2, sy1, "%s", str);
        sx2++;
    }
    drawBorder("SCORES", sx1, sx2, sy1, sy2);
    refresh();
    fclose(f);

    getchar();
}

///// DRAW INSTRUCTIONS /////

void instructions() {
    int count = 1;
    clear();
    char str[1000];
    FILE* f = fopen("instructions.txt", "r");
    while(fgets(str, 1000, f) != NULL){
            mvprintw(count, 0, "%s", str);
        count++;
    }
    refresh();
    fclose(f);

    getchar();
}
