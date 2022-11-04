#define DELAY 100000
#define max_x 1
#define max_y 60
#define max_l (max_x * max_y)

int anim_inc = 0, sx = 1, sy = 54, x[max_l], y[max_l], l = 0, dx = 0, dy = -2;

///// DRAW SNAKE /////

void drawSnake(int x[], int y[], int l) {
   	mvprintw(x[0],  y[0], "S"); // head of snake
   for(int i = 1; i < l; i++) {
     mvprintw(x[i],  y[i], "s"); // body of snake
   } 
   if(l>2)
     mvprintw(x[l-1], y[l-1], "."); // tail of snake
       refresh();
}

///// INTRO ANIMATION /////

void introAnimation(){
    while(anim_inc != 500){
	   clear();
	   for(int i = 0; i < l; i++){
	       x[l-i] = x[l-i-1];  // Shifting all the previous snake locations to the 
	       y[l-i] = y[l-i-1];  // next slot in the array, to clear up slot [0]
	   }
	     
	   x[0] = sx;   // Setting the current snake head position to slot [0]
	   y[0] = sy;
	   
	   if(l < 11)
	   	l++;
	   
	   drawSnake(x, y, l);
	   
	   usleep(DELAY);
	   
	   if(anim_inc == 20){
	      dx = 1;
	      dy = 0;
	   }
	   if(anim_inc == 22){
	      dx = 0;
	      dy = 2;
	   }
	   if(anim_inc == 24){
	      dx = 1;
	      dy = 0;
	   }
	   if(anim_inc == 26){
	      dx = 0;
	      dy = -2;
	   }
	   if(anim_inc == 28){
	      usleep(DELAY);
	      break;
	   }
	   
	   sx += dx;
	   sy += dy;
	   
	   anim_inc++;
   }
   anim_inc = 0;
}