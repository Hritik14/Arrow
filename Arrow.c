#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<time.h>
#define MAX_X 77
#define MAX_Y 49
#define FD_CL GREEN
#define E_CL RED
#define E_CL_SP FD_CL
#define DEFAULT AR_CL
#define MAX_E 10
#define AR_CL YELLOW
#define SP_COLOR WHITE
#define SP_REPEAT 4
#define LVL_CHNG 3
#define SP_MAX 100
enum active{NO,YES};
void putfood(void);
void show_points(void);
void ene(void);
struct pos
{
int x;
int y;
}arrow,food,e[10];
void move(char,struct pos *);
int points,sp_points,no_of_e,count,sp;
int main(){
	int i;
	int c,speed=80,ctmp;
	count=0;
	no_of_e = 0;
	arrow.x=25;
	arrow.y=25;
	food.x=30;
	food.y=30;
	points=0;
	srand(time(0));
	putfood();
	_setcursortype(0);

	for(i=0;i<MAX_E;i++)
		e[i].x = rand()%5, e[i].y=rand()%10;
	clrscr();
	textcolor(GREEN);
	cprintf("ARROW: Press any key");
	gotoxy(1,10);
	cprintf("Note: Set window size to 80/50 if on Windows");
	getch();
	clrscr();
	textcolor(AR_CL);
	c = 'd'; //Inital move left
	for(;;){
		if(kbhit())
			switch(ctmp=getch()){
				case 'q':
				case 27:
				return 0;
				case 0:
					ctmp=getch();
				case 'a': case 's': case 'w': case 'd':
				c = ctmp;
				break;
			}
  if(arrow.x == MAX_X)
		arrow.x = 1;
	if(arrow.y == MAX_Y)
		arrow.y = 1;
	if(arrow.x == 0)
		arrow.x = MAX_X -1;
	if(arrow.y == 0)
		arrow.y = MAX_Y-1;
	switch(c){
case 's':
case 80:
	arrow.y+=1;
	clrscr();
	gotoxy(arrow.x,arrow.y);
	cprintf("|",arrow.x);
	break;
case 'a':
case 75:
	arrow.x-=1;
	clrscr();
	gotoxy(arrow.x,arrow.y);
	cprintf("<-");
	break;
case 'w':
case 72:
	arrow.y-=1;
	clrscr();
	gotoxy(arrow.x,arrow.y);
	cprintf("^");
	break;
case 'd':
case 77:
	arrow.x+=1;
	clrscr();
	gotoxy(arrow.x,arrow.y);
	cprintf("->");
	break;
}

	if(arrow.x == food.x && arrow.y == food.y){
		food.x = rand()%MAX_X;
		food.y = rand()%MAX_Y;
		if(!(points % SP_REPEAT) && points)
			points++,sp_points++,sp=SP_MAX;
		else
			points++;
		if(!(points % LVL_CHNG) && points!=0 && sp!=SP_MAX ) //Not in case of SP eating
			speed-=10,no_of_e++;
	}
	for(i=0;i<no_of_e;i++){
		if(e[i].x == MAX_X)
			e[i].x = 1;
		if(e[i].y == MAX_Y)
			e[i].y = 1;
		if(e[i].x == 0)
			e[i].x = MAX_X - 1;
		if(e[i].y == 0)
			e[i].y = MAX_Y - 1;
	}
	putfood();
	show_points();
	for(i=0;i<no_of_e;i++) //e handling
	if(e[i].x == arrow.x && e[i].y == arrow.y)
		if(sp){
			struct pos etmp;
			etmp = e[i];
			e[i] = e[no_of_e-1];
			e[no_of_e-1] = etmp;
			no_of_e--;
			points++;
		}
		else{
			clrscr();
			gotoxy(MAX_X/2,MAX_Y/2);
			textcolor(RED);
			cprintf("GAME OVER (Score: %d)\n",points+sp_points);
			textcolor(RED+BLINK);
			cprintf("Press q to  exit");
			while((c=getch())!='q')
				;
			return 0;

		}

	ene();
	delay(speed);
	count++;
	if(sp>0)
		sp--;
	}
}
void putfood(){
	textcolor(FD_CL);
	gotoxy(food.x,food.y);
	if(!(points%SP_REPEAT) && points){
		textcolor(SP_COLOR);
		cprintf("O");
	}
	else
		cprintf("*");
	textcolor(AR_CL);
	gotoxy(arrow.x,arrow.y);
}
void show_points(void){
	gotoxy(1,1);
	textcolor(GREEN);
	cprintf("Points: %d",points+sp_points);
	if(sp){
		cprintf("   ");
		textcolor(RED + BLINK);
		cprintf("Superpower(%d%%)",sp*100/SP_MAX);
	}
	textcolor(AR_CL);
	gotoxy(arrow.x,arrow.y);
}

void ene(){
	int i,r;
	if(!(count % 2 ))   //Decides speed
		for(i=0;i<no_of_e;i++){
	    if(!sp){
		if( e[i].y < arrow.y ){
		    e[i].y+=1;
		    gotoxy(e[i].x,e[i].y);
		    textcolor(E_CL);
		    cprintf("|");
		}
		else if( e[i].x > arrow.x ){
			e[i].x-=1;
			gotoxy(e[i].x,e[i].y);
			textcolor(E_CL);
			cprintf("<-");
		}
		else if( e[i].y > arrow.y ){
			e[i].y-=1;
			gotoxy(e[i].x,e[i].y);
			textcolor(E_CL);
			cprintf("^");
		}
		else if(e[i].x < arrow.x){
		    e[i].x+=1;
		    gotoxy(e[i].x,e[i].y);
		    textcolor(E_CL);
		    cprintf("->");
		} }
	    else{
		if( e[i].y < arrow.y ){
		    e[i].y-=1;
		    gotoxy(e[i].x,e[i].y);
		    textcolor(E_CL_SP);
		    cprintf("^");
		}
		else if( e[i].x > arrow.x ){
			e[i].x+=1;
			gotoxy(e[i].x,e[i].y);
			textcolor(E_CL_SP);
			cprintf("<-");
		}
		else if( e[i].y > arrow.y ){
			e[i].y+=1;
			gotoxy(e[i].x,e[i].y);
			textcolor(E_CL_SP);
			cprintf("|");
		}
		else if(e[i].x < arrow.x){
		    e[i].x-=1;
		    gotoxy(e[i].x,e[i].y);
		    textcolor(E_CL_SP);
		    cprintf("->");
		}   }
	}
	else  //Simply be there where you are
			for(i=0;i<no_of_e;i++)
			if( e[i].y < arrow.y )
	{
		gotoxy(e[i].x,e[i].y);
		textcolor(E_CL);
		cprintf("|");
	}
	else if( e[i].x > arrow.x ){
		gotoxy(e[i].x,e[i].y);
		textcolor(E_CL);
		cprintf("<-");
	}
	else if( e[i].y > arrow.y ){
		gotoxy(e[i].x,e[i].y);
		textcolor(E_CL);
		cprintf("^");
	}
	else if(e[i].x < arrow.x){
		gotoxy(e[i].x,e[i].y);
		textcolor(E_CL);
		cprintf("->");
	}
textcolor(DEFAULT);
}
