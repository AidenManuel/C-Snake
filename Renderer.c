#define DELAY 100000
#define SNAKE 1
#define FOOD 2
#define SPEED1 1
#define SPEED2 3
#define SPEED3 4
#define min_x 0
#define min_y 0
#define max_x 15
#define max_y 60
#define max_l (max_x * max_y)

int choice = 0, selector, flavour;

///// DRAW MAIN BORDER /////

void mainBorder() {
    mvaddch(0, 0, ACS_ULCORNER);
    for(int y = 1; y < 80; y++){
        mvaddch(0, y, ACS_HLINE);              // top border
    }
    mvaddch(0, 80, ACS_URCORNER);

    for(int x = 1; x < 20; x++){
        mvaddch(x, 0, ACS_VLINE);             // side walls
        mvaddch(x, 80, ACS_VLINE);
    }

    mvaddch(20, 0, ACS_LLCORNER);
    for(int y = 1; y < 80; y++){
        mvaddch(20, y, ACS_HLINE);   // bottom border
    }
    mvaddch(20, 80, ACS_LRCORNER);
    refresh();
}

///// DRAW MENU /////

int drawMenu() {
   selector = 8;
   clear();
   mainBorder();
   mvprintw(1, 13, " C C C       s s .   N     N     A     K   K   E E E  ");
   mvprintw(2, 13, " C           s       N N   N   A   A   K   K   E      ");
   mvprintw(3, 13, " C           s s s   N   N N   A A A   K K     E E    ");
   mvprintw(4, 13, " C               s   N     N   A   A   K   K   E      ");
   mvprintw(5, 13, " C C C   .   S s s   N     N   A   A   K   K   E E E  ");
   mvprintw(8, 13, "                    MODE  SELECT");
   mvprintw(10, 13, "                     SCOREBOARD");
   mvprintw(12, 13, "                    INSTRUCTIONS");
   mvprintw(14, 13, "                        QUIT");
   while(choice == 0){
   	mvprintw(selector, 28, "*");
   	switch(getch()) {
   	   case 'w':
	         if(selector != 8){
               mvprintw(selector, 28, " ");
               selector -= 2;
            }
   	      break;
   	   case 's':
   	      if(selector != 14){
               mvprintw(selector, 28, " ");
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
       default:
            break;
   	}
    usleep(DELAY);
   }
}

///// DRAW DIFFICULTY /////

char* flavourText(int selection) {
    switch(selection) {
        case 1:
            return "For new players, who are still learning to slither...";
            break;
        case 2:
            return "For the average player, an every day apple eater!";
            break;
        case 3:
            return "For the experienced player, a certified snake specialist!";
            break;
        case 4:
            return "For the mad, the lost, and the insane... Why are you this way?";
            break;
    }
}

int drawDifficulty() {
   flavour = 1;
   clear();
   mainBorder();
   mvprintw(1, 13, " C C C       s s .   N     N     A     K   K   E E E  ");
   mvprintw(2, 13, " C           s       N N   N   A   A   K   K   E      ");
   mvprintw(3, 13, " C           s s s   N   N N   A A A   K K     E E    ");
   mvprintw(4, 13, " C               s   N     N   A   A   K   K   E      ");
   mvprintw(5, 13, " C C C   .   S s s   N     N   A   A   K   K   E E E  ");
   mvprintw(8, 13, "                   DANGER  NOODLE");
   attron(COLOR_PAIR(SNAKE));
   mvprintw(10, 13, "                    GARDEN SNAKE");
   attroff(COLOR_PAIR(SNAKE));
   attron(COLOR_PAIR(SPEED2));
   mvprintw(12, 13, "                     PIT  VIPER");
   attroff(COLOR_PAIR(SPEED2));
   attron(COLOR_PAIR(FOOD));
   mvprintw(14, 13, "                    BLACK  MAMBA");
   attroff(COLOR_PAIR(FOOD));
   mvprintw(18, 3, "%s", flavourText(flavour));
   while(choice == 0){
   	mvprintw(selector, 28, "*");
   	switch(getch()) {
   	   case 'w':
	         if(selector != 8){
               mvprintw(selector, 28, " ");
               selector -= 2;
               flavour--;
               mvprintw(18, 3, "                                                                 ");
               mvprintw(18, 3, "%s", flavourText(flavour));
            }
   	      break;
   	   case 's':
   	      if(selector != 14){
               mvprintw(selector, 28, " ");
   	         selector +=2;
             flavour++;
               mvprintw(18, 3, "                                                                ");
               mvprintw(18, 3, "%s", flavourText(flavour));
            }
   	      break;
   	   case '\n':
   	      switch(selector) {
   	      case 8:
   	         return 0;
   	         break;
   	      case 10:
   	         return 1;
   	         break;
   	      case 12:
   	         return 2;
   	         break;
   	      case 14:
             return 4;
   	         break;
   	      }
   	      break;
         refresh();
       default:
            break;
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

void drawTurboMeter(int x, int y, bool alternator){
    drawBorder("TURBO", x, x+10, y, y+3);
    if(alternator){
        for(int i = 9; i > 2; i-=2){
            attron(COLOR_PAIR(5));
            mvaddch(x + i, y + 1, ACS_CKBOARD);
            mvaddch(x + i, y + 2, ACS_CKBOARD);
            attroff(COLOR_PAIR(5));
            attron(COLOR_PAIR(6));
            mvaddch(x + i - 1, y + 1, ACS_CKBOARD);
            mvaddch(x + i - 1, y + 2, ACS_CKBOARD);
            attroff(COLOR_PAIR(6));
        }
    } else {
        for(int i = 9; i > 2; i-=2){
            attron(COLOR_PAIR(6));
            mvaddch(x + i, y + 1, ACS_CKBOARD);
            mvaddch(x + i, y + 2, ACS_CKBOARD);
            attroff(COLOR_PAIR(6));
            attron(COLOR_PAIR(5));
            mvaddch(x + i - 1, y + 1, ACS_CKBOARD);
            mvaddch(x + i - 1, y + 2, ACS_CKBOARD);
            attroff(COLOR_PAIR(5));
        }
    }

}

///// GAME OVER /////

struct Player* gameOver(int score, FILE* fp, struct Player* nullFella, int mode) {
    char initials[2], temp;
    int i = 0;
    clear();
    getchar();
    mainBorder();
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
        if(temp != 13){
            refresh();
            initials[i] = temp;
            i++;
        }
    }
    
    mvprintw(max_x/2 + 6, 27, "%s", initials);
    mvprintw(max_x/2 + 7, 6, "SCORE %d", score - 100);
    refresh();

    fp = fopen("scores.txt", "w");
    fprintf(fp, " ");
    fclose(fp);
    addPlayer(createPlayer(score - 100, initials[0], initials[1], mode), nullFella);
    BEEG2smol(nullFella);

    getchar();
    return nullFella;
}

///// DRAW SCOREBOARD /////

void scoreboard(FILE* f) {
    int sx1 = 3, sx2 = sx1+1, sy1 = 25, sy2 = sy1+30;
    char mode;

    clear();
    char str[250];
    f = fopen("scores.txt", "rw");
    while(fgets(str, 250, f) != NULL && sx2 < 19){
            mode = str[0];
            if (mode == '1')
                attron(COLOR_PAIR(SPEED1));
            else if (mode == '2')
                attron(COLOR_PAIR(SPEED2));
            else if (mode == '4')
                attron(COLOR_PAIR(FOOD));
            mvprintw(sx2, sy1, "%s", str+1);
            if (mode == '1')
                attroff(COLOR_PAIR(SPEED1));
            else if (mode == '2')
                attroff(COLOR_PAIR(SPEED2));
            else if (mode == '4')
                attroff(COLOR_PAIR(FOOD));
        sx2++;
    }
    drawBorder("SCORES", sx1, sx2, sy1, sy2);
    refresh();
    fclose(f);

    mainBorder();

    getchar();
}

///// DRAW INSTRUCTIONS /////

void instructions() {
    int count = 1;
    char str[1000];
    FILE* f = fopen("instructions.txt", "r");
    while(fgets(str, 1000, f) != NULL){
            mvprintw(count, 22, "%s", str);
        count++;
    }
    refresh();
    fclose(f);
    mainBorder();
}
