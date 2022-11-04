#define DELAY 100000
#define max_x 15
#define max_y 60
#define max_l (max_x * max_y)

int choice = 0, selector = 8;

///// DRAW MENU /////

int drawMenu() {
   while(choice == 0){
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
   	
   	mvprintw(selector, 15, "*");
   	switch(getch()) {
   	   case 'w':
	      if(selector != 8)
   	         selector -= 2;
   	      break;
   	   case 's':
   	      if(selector != 14)
   	         selector +=2;
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
   	}
    usleep(DELAY);
   }
}

///// DRAW BORDER /////

void drawBorder(char* title, int length, int x1, int x2, int y1, int y2) {  // Draws the box which is representative of the play area
    int b_x = x2 - x1, b_y = y2 - y1;
    mvprintw(0, y1 + b_y / 2 - (strlen(title) / 2), "%s", title);
    
    for(int y = 1; y < b_y; y++){
        mvprintw(1, y + y1, "_");              // top border
        refresh();
    }
    for(int x = 2; x < b_x; x++){
        mvprintw(x + x1, y1, "|");
        refresh();                      // side walls
        mvprintw(x + x1, b_y + y1, "|");
        refresh();
    }
    for(int y = 1; y < b_y; y++){
        mvprintw(b_x - 1 + x1, y + y1, "_");          // bottom border
        refresh();
    }
   
   mvprintw(b_x + 1 + x1, y1 + b_y / 2 - 4, "score : %d", length);  // score
}

///// GAME OVER /////

FILE* gameOver(int score, FILE* fp) {
    char initials[2];
    clear();
    getchar();
    mvprintw(max_x/2 - 2, 3, "G G G    A    M       M  E E E       O     V   V   E E E   R R");
    mvprintw(max_x/2 - 1, 3, "G      A   A  M M   M M  E         O   O   V   V   E       R   R");
    mvprintw(max_x/2, 3,     "G      A A A  M   M   M  E E       O   O   V   V   E E     R R ");
    mvprintw(max_x/2 + 1, 3, "G   G  A   A  M       M  E         O   O   V   V   E       R   R");
    mvprintw(max_x/2 + 2, 3, "G G G  A   A  M       M  E E E       O       V     E E E   R   R");
    mvprintw(max_x/2 + 6, 6, "Enter Your Initials: XX");
    refresh();
    usleep(DELAY);
    initials[0] = getchar();
    initials[1] = getchar();
    mvprintw(max_x/2 + 6, 27, "%s", initials);
    mvprintw(max_x/2 + 7, 6, "SCORE %d", score);
    refresh();

    fp = fopen("scores.txt", "a");
    char buf[BUFSIZ];
    fprintf(fp, "\n\t|%s\t\t|%d\t\t|", initials, score);
    fclose(fp);

    getchar();
    return fp;
}

///// DRAW SCOREBOARD /////

void scoreboard(FILE* f) {
    int count = 1;
    clear();
    char str[250];
    f = fopen("scores.txt", "rw");
    while(fgets(str, 250, f) != NULL){
            mvprintw(count, 0, "%s", str);
        count++;
    }
    mvprintw(count, 0, "\t|_______________|_______________|");
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
