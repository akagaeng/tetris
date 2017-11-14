#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char block[7][4][4][2]={
			{
			{{ 0, 0},{-1, 0},{ 1, 0},{ 2, 0}},
			{{ 0, 0},{ 0,-1},{ 0, 1},{ 0, 2}},
			{{ 0, 0},{-2, 0},{-1, 0},{ 1, 0}},
			{{ 0, 0},{ 0, 1},{ 0,-1},{ 0,-2}}
			}, //block[0][][][] : long block

			{
			{{ 0, 0},{ 0, 1},{ 1, 0},{ 1, 1}},
			{{ 0, 0},{ 0, 1},{ 1, 0},{ 1, 1}},
			{{ 0, 0},{ 0, 1},{ 1, 0},{ 1, 1}},
			{{ 0, 0},{ 0, 1},{ 1, 0},{ 1, 1}}
			}, //block[1][][][] : rectangle block

			{
			{{ 0, 0},{ 0, 1},{-1, 0},{-2, 0}},
			{{ 0, 0},{-1, 0},{ 0,-1},{ 0,-2}},
			{{ 0, 0},{ 1, 0},{ 2, 0},{ 0,-1}},
			{{ 0, 0},{ 0, 1},{ 0, 2},{ 1, 0}}
			}, //block[2][][][] : L  block

			{
			{{ 0, 0},{-1, 0},{-2, 0},{ 0,-1}},
			{{ 0, 0},{ 1, 0},{ 0,-1},{ 0,-2}},
			{{ 0, 0},{ 0, 1},{ 1, 0},{ 2, 0}},
			{{ 0, 0},{ 0, 1},{ 0, 2},{-1, 0}}
			}, //block[3][][][] : reverse L block

			{
			{{ 0, 0},{ 1, 0},{ 0,-1},{-1,-1}},
			{{ 0, 0},{ 0, 1},{ 1, 0},{ 1,-1}},
			{{ 0, 0},{-1, 0},{ 0, 1},{ 1, 1}},
			{{ 0, 0},{ 0,-1},{-1, 0},{-1, 1}}
			}, //block[4][][][] : Y block

			{
			{{ 0, 0},{-1, 0},{ 0,-1},{ 1,-1}},
			{{ 0, 0},{ 0,-1},{ 1, 0},{ 1, 1}},
			{{ 0, 0},{ 1, 0},{ 0, 1},{-1, 1}},
			{{ 0, 0},{ 0, 1},{-1, 0},{-1,-1}}
			}, //block[5][][][] : reverse Y block

			{
			{{ 0, 0},{ 0, 1},{-1, 0},{ 0,-1}},
			{{ 0, 0},{ 1, 0},{ 0,-1},{-1, 0}},
			{{ 0, 0},{ 0, 1},{ 0,-1},{ 1, 0}},
			{{ 0, 0},{ 0, 1},{ 1, 0},{-1, 0}}
			}, //block[6][][][] : E block
		       };

int x,y,b,r;
int b_next;
int shadow_y;
int strike_cnt;
int shadow_strike_cnt;
int strike_or_not;
int line_cnt[22]={0,};
int board[23][17]={0,};
int next_block_board[9][11]={0,};
int gap_var=0;
int game_cnt=1;
int score=0;
int line_score=0;
int high_score=0;
int ch;
int moved;
char gameover;
char yesno;
int i,j,k,l;
int pause_cnt;
int level_cnt;
int down_delay;
int time_start;
int time_end;
char game_msg[29];
char *tile[]={".", "#", "M", "@", " ", "*", "/"};

void board_arr(){
 for(i=0;i<23;i++){
  for(j=0;j<17;j++){
   if( i>=0 && i<4 && j!=0 && j!=16){	board[i][j]=4; }
   else if( i==22 || j==0 || j==16){	board[i][j]=2; }
   else{ 				board[i][j]=0; }
  }
 }
}

void next_block_board_arr(){
 for(i=0;i<9;i++){
  for(j=0;j<11;j++){
   if(i>0 && i<8 && j>0 && j<10){ next_block_board[i][j]=4; }
   else if(i==0 || i==8 || j==0 || j==10){ next_block_board[i][j]=6;}
  }
 }
}

void board_print(){
 for(i=0;i<23;i++){
  for(j=0;j<17;j++){
   move(1+i,5+j);
   addstr(tile[board[i][j]]);
  }
 }

 for(i=0;i<9;i++){
  for(j=0;j<11;j++){
   move(2+i,23+j);
   addstr(tile[next_block_board[i][j]);
  }
 }
}


void showblock(){
 for(i=0;i<4;i++){
  move(1+block[b][r][i][0]+y, 5+block[b][r][i][1]+x);
  addstr(tile[1]);
 }
}


void show_next_block(){
 for(i=0;i<4;i++){
  move(6+block[b_next][0][i][0], 28+block[b_next][0][i][1]);
  addstr(tile[1]);
 }
}


void shadow(){
shadow_strike_cnt=0;
shadow_y=3;

while(shadow_strike_cnt!=1){
 if( board[shadow_y+block[b][r][0][0]+1 ][x+block[b][r][0][1] ] ==2 ||
     board[shadow_y+block[b][r][1][0]+1 ][x+block[b][r][1][1] ] ==2 ||
     board[shadow_y+block[b][r][2][0]+1 ][x+block[b][r][2][1] ] ==2 ||
     board[shadow_y+block[b][r][3][0]+1 ][x+block[b][r][3][1] ] ==2 ||

     board[shadow_y+block[b][r][0][0]+1 ][x+block[b][r][0][1] ] ==3 ||
     board[shadow_y+block[b][r][1][0]+1 ][x+block[b][r][1][1] ] ==3 ||
     board[shadow_y+block[b][r][2][0]+1 ][x+block[b][r][2][1] ] ==3 ||
     board[shadow_y+block[b][r][3][0]+1 ][x+block[b][r][3][1] ] ==3 ){

  shadow_strike_cnt++;
  }
 else(shadow_y++;}
 }
 if(shadow_strike_cnt==1){
  for(i=0;i<4;i++){
   move(1+block[b][r][i][0]+shadow_y, 5+block[b][r][i][1]+x);
   addstr(tile[5]);
  }
 }
 shadow_strike_cnt=0;
}


void move_down(){

 if( board[y+block[b][r][0][0]+1 ][x+block[b][r][0][1] ] ==2 ||
     board[y+block[b][r][1][0]+1 ][x+block[b][r][1][1] ] ==2 ||
     board[y+block[b][r][2][0]+1 ][x+block[b][r][2][1] ] ==2 ||
     board[y+block[b][r][3][0]+1 ][x+block[b][r][3][1] ] ==2 ||

     board[y+block[b][r][0][0]+1 ][x+block[b][r][0][1] ] ==3 ||
     board[y+block[b][r][1][0]+1 ][x+block[b][r][1][1] ] ==3 ||
     board[y+block[b][r][2][0]+1 ][x+block[b][r][2][1] ] ==3 ||
     board[y+block[b][r][3][0]+1 ][x+block[b][r][3][1] ] ==3 ){

 else{ y++; }
}


void strike_block(){

 if( board[y+block[b][r][0][0]+1 ][x+block[b][r][0][1] ] ==2 ||
     board[y+block[b][r][1][0]+1 ][x+block[b][r][1][1] ] ==2 ||
     board[y+block[b][r][2][0]+1 ][x+block[b][r][2][1] ] ==2 ||
     board[y+block[b][r][3][0]+1 ][x+block[b][r][3][1] ] ==2 ||

     board[y+block[b][r][0][0]+1 ][x+block[b][r][0][1] ] ==3 ||
     board[y+block[b][r][1][0]+1 ][x+block[b][r][1][1] ] ==3 ||
     board[y+block[b][r][2][0]+1 ][x+block[b][r][2][1] ] ==3 ||
     board[y+block[b][r][3][0]+1 ][x+block[b][r][3][1] ] ==3 ){

   strike_cnt++;
 }
}


void striked_block(){
int this_score;
 if(strike_cnt==2){

     board[y+block[b][r][0][0] ][x+block[b][r][0][1] ] =3;
     board[y+block[b][r][1][0] ][x+block[b][r][1][1] ] =3;
     board[y+block[b][r][2][0] ][x+block[b][r][2][1] ] =3;
     board[y+block[b][r][3][0] ][x+block[b][r][3][1] ] =3;

	this_score=100
	score=score+this_score+line_score;
	if(high_score<=score){ high_score=score; }
	x=8;y=3;
	strike_cnt=0;
	strike_or_not=1;
 }
}


void auto_move_down(){
time_end=clock();

if( (time_end-time_start) / 10000 ==down_delay ){
time_start=clock();
move_down();
gap_var=-1;
strike_block();
striked_block();
board_print();
showblock();
 }
 refresh();
}


void move_left(){

 if( board[ y+block[b][r][0][0] ][x+block[b][r][0][1]-1 ] ==2 ||
     board[ y+block[b][r][1][0] ][x+block[b][r][1][1]-1 ] ==2 ||
     board[ y+block[b][r][2][0] ][x+block[b][r][2][1]-1 ] ==2 ||
     board[ y+block[b][r][3][0] ][x+block[b][r][3][1]-1 ] ==2 ||

     board[ y+block[b][r][0][0] ][x+block[b][r][0][1]-1 ] ==3 ||
     board[ y+block[b][r][1][0] ][x+block[b][r][1][1]-1 ] ==3 ||
     board[ y+block[b][r][2][0] ][x+block[b][r][2][1]-1 ] ==3 ||
     board[ y+block[b][r][3][0] ][x+block[b][r][3][1]-1 ] ==3 ){}

else { x--; }

}


void move_right(){

 if( board[ y+block[b][r][0][0] ][x+block[b][r][0][1]+1 ] ==2 ||
     board[ y+block[b][r][1][0] ][x+block[b][r][1][1]+1 ] ==2 ||
     board[ y+block[b][r][2][0] ][x+block[b][r][2][1]+1 ] ==2 ||
     board[ y+block[b][r][3][0] ][x+block[b][r][3][1]+1 ] ==2 ||

     board[ y+block[b][r][0][0] ][x+block[b][r][0][1]+1 ] ==3 ||
     board[ y+block[b][r][1][0] ][x+block[b][r][1][1]+1 ] ==3 ||
     board[ y+block[b][r][2][0] ][x+block[b][r][2][1]+1 ] ==3 ||
     board[ y+block[b][r][3][0] ][x+block[b][r][3][1]+1 ] ==3 ){}

else { x++; }

}

void rotation(){

 if( board[ y+block[b][(r+1)%4][0][0] ][x+block[b][(r+1)%4][0][1] ] ==2 ||
     board[ y+block[b][(r+1)%4][1][0] ][x+block[b][(r+1)%4][1][1] ] ==2 ||
     board[ y+block[b][(r+1)%4][2][0] ][x+block[b][(r+1)%4][2][1] ] ==2 ||
     board[ y+block[b][(r+1)%4][3][0] ][x+block[b][(r+1)%4][3][1] ] ==2 ||

     board[ y+block[b][(r+1)%4][0][0] ][x+block[b][(r+1)%4][0][1] ] ==3 ||
     board[ y+block[b][(r+1)%4][1][0] ][x+block[b][(r+1)%4][1][1] ] ==3 ||
     board[ y+block[b][(r+1)%4][2][0] ][x+block[b][(r+1)%4][2][1] ] ==3 ||
     board[ y+block[b][(r+1)%4][3][0] ][x+block[b][(r+1)%4][3][1] ] ==3 ){}

else { r=(r+1)%4; }

}


void line_check(){
int remove_line;

 for(i=0;remove_line=0;i<22;i++){ 
  line_cnt[i]=0;
  for(j=0;j<16;j++){
   if( board[i][j]==3 ){ line_cnt[i]++; }
   if( line_cnt[i]==15{
    level_cnt++;
    remove_line++;
     if(level_cnt%2==0){down_delay*=0.8;}
     time_start=clock();
	if(remove_line==1){
		score+=500;
		mvprintw(7,38," remove 1 line! ");
		mvprintw(8,38,"  you got bonus ");
		mvprintw(9,38,"  +500 point!!! ");
		refresh();}

	if(remove_line==2){
		score+=1000;
		mvprintw(7,38," remove 2 line! ");
		mvprintw(8,38,"  you got bonus ");
		mvprintw(9,38," +1500 point!!! ");
		refresh();}

	if(remove_line==3){
		score+=1500;
		mvprintw(7,38," remove 3 line! ");
		mvprintw(8,38,"  you got bonus ");
		mvprintw(9,38," +3000 point!!! ");
		refresh();}

	if(remove_line==4){
		score+=2000;
		mvprintw(7,38,"*****TETRIS*****");
		mvprintw(8,38,"* BONUS  +5000 *");
		mvprintw(9,38,"****************");
		refresh();}

	if(high_score<=score){ high_score=score; }
		for(l=i;l>=4;l--){
		 for(k=1;k<16;k++){
		  board[l][k]=board[l-1][k];
		  if(l==4){ board[l][k]=0;} //make top line "." not " "
		 }
		}
	}
  }
 }
refresh();
}


void initiate_tetris(){
 clear();
 score=0;
 ch=0;
 x=8;
 y=3;
 shadow_y=3;
 srand(time(NULL));
 b=rand()%7;
 b_next=rand()%7;
 r=0;
 strike_cnt=0;
 shadow_strike_cnt=0;
 pause_cnt=0;
 level_cnt=0;
 down_delay=100;
 board_arr();
 next_block_board_arr();
 strike_or_not=0; //0: not strike 1:strike
 gap_var=0;
}


void message_box(){
refresh();
mvprintw(1,23,"NEXT BLOCK");
refresh();
mvprintw(13,23,"==========KEY DESCRIPTION=========");
mvprintw(14,23," left KEY: move left");
mvprintw(15,23,"right KEY: move right");
mvprintw(16,23," down KEY: move down");
mvprintw(17,23,"   up KEY: change block rotation");
mvprintw(18,23,"space KEY: move directly down");
mvprintw(20,23,"  F10 KEY: pause game");
mvprintw(21,23,"  F12 KEY: exit game");
mvprintw(22,23,"==================================");
refresh();

mvprintw( 2,36,"HIGH SCORE: %d pt",high_score);
mvprintw( 3,36,"     SCORE: %d pt",score);
mvprintw( 4,36,"     TRIAL: %d th trial",game_cnt);
mvprintw( 5,36,"down delay: %d (drop time)",down_delay);
mvprintw( 6,36,"o------------------o",high_score);
mvprintw( 7,36,"|");mvprintw(7,55,"|");
mvprintw( 8,36,"|");mvprintw(8,55,"|");
mvprintw( 9,36,"|");mvprintw(9,55,"|");
mvprintw(10,36,"o------------------o");
refresh();
mvprintw(13, 58,"==GAME DESCRIPTION==");
mvprintw(14, 58,"drop block: +100pt");
mvprintw(15, 58,"remove 1 line: +500");
mvprintw(16, 58,"remove 2 line: +1500");
mvprintw(17, 58,"remove 3 line: +3000");
mvprintw(18, 58,"remove 4 line: +5000");
mvprintw(20, 58,"remove every 2 line");
mvprintw(21, 58,"downspeed 20%% faster");
mvprintw(22, 58,"===================");
}

int main(){
ch=0;
initscr();
curs_set(0);
keypad(stdscr,TRUE);
time_start=clock();
nodelay(stdscr,TRUE);
initiate_tetris();

while(1){
 message_box();
 if(strike_or_not==1){ //0: not strike 1: strike
 b=b_next;
 b_next=rand()%7;
 strike_or_not=0;
}
board_print();
shadow();
showblock();
show_next_block();
refresh();
if( (ch=getch() ) == ERR ) { auto_move_down(); }
else{
	switch(ch){
			case KEY_UP:
					rotation();
					refresh();
					break;
			case KEY_DOWN:
					move_down();
					gap_var=-1;
					strike_block();
					striked_block();
					refresh();
					break;
			case KEY_LEFT:
					move_left();
					refresh();
					break;
			case KEY_RIGHT:
					move_right();
					refresh();
					break;
			case ' ':
					while(strike_cnt!=1){
						move_down();
						strike_block();
						}
					strike_cnt++;
					gap_var=0;
					striked_block();
					gap_var=-1;
					refresh();
					strike_cnt=0;
					break;
			case KEY_F(12):
					mvprintw(7,38,"    GAME OVER    ");
					mvprintw(8,38,"                 ");
					mvprintw(9,38,"    GOOD BYE!    ");
					refresh();
					sleep(1);
					endwin();
					exit(0);
					break;
			case KEY_F(10):
					while( getch()!=KEY_F(10) ){
					 mvprintw(7,38,"    GAME PAUSE    ");
					 mvprintw(8,38,"  press F10 KEY   ");
					 mvprintw(9,38,"  to resume GAME  ");
					 refresh();
					 sleep(1);
					}
					 mvprintw(7,38,"  GAME RESTART    ");
					 mvprintw(8,38,"    E N J O Y     ");
					 mvprintw(9,38,"   T E T R I S    ");
			default:

		}//end switch(ch)
	}//end else

	line_check();
	refresh();

/*	GAME OVER CHECK		*/

for(i=0;i<16;i++){
 if(board[3][i]==3){
  while(1){
   yesno==getch();
    refresh();
    mvprintw(7,38,"    GAME OVER    ");
    mvprintw(8,38,"                 ");
    mvprintw(9,38,"TRY AGAIN? (Y/N)");
    refresh();
	if(yesno=='y'){
	 game_cnt++;
	 initiate_tetris();
	 gameover=1;
	 break;
	}
	else if(yesno=='n'){
	 refresh();
	 mvprintw(7,38,"    GAME OVER    ");
	 mvprintw(8,38,"                 ");
	 mvprintw(9,38,"    GOOD BYE!    ");
	 refresh();
	 sleep(1);
	 endwin();
	 exit(0);
	}
  }
 }
}
refresh();
}//end while
endwin();

return 0;
}
