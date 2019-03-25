/*----------------------------------\
|	Create by						|
|	HEURTEL Geoffroy				|
\----------------------------------*/

#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <termios.h> 
#include <unistd.h> 
#include <sys/time.h> 
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>

#include "Draw.c"

bool moon=false;
bool mercury=false;
bool venus=false;
bool march=false;
bool all_Galaxie = false;


bool background = false;
float tmp_Pause = 0.6; //en seconde

int unix_text_kbhit(void) 
{ 
    struct timeval tv = { 0, 0 }; 
    fd_set readfds; 

    FD_ZERO(&readfds); 
    FD_SET(STDIN_FILENO, &readfds); 
  
    return select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv) == 1; 
}

void option(int argc, char *argv[]){
	for (int i = 1; i < argc; ++i)
	{
		if(std::string(argv[i]) == "m")
			mercury = true;
		if(std::string(argv[i]) == "v")
			venus = true;
		if(std::string(argv[i]) == "M")
			march = true;
		if(std::string(argv[i]) == "moon")
			moon = true;
		if(std::string(argv[i]) == "all"){
			mercury = true;
			venus = true;
			march = true;
			moon = true;
		}
		if(std::string(argv[i]) == "All")
			all_Galaxie = true;
	}
}

bool read_clavier(){

	for(int i=0; i < 1000; i++)
	{
		if(unix_text_kbhit()){
			switch (getchar()){
				case 113 :
					return 1;
				case 112 :
					getchar();
					break;
				case 66 :
					if(tmp_Pause > 0)
						tmp_Pause-=0.1;
					break;
				case 65 :
					if(tmp_Pause < 2)
						tmp_Pause+=0.1;
					break;

			}
		}
		usleep(tmp_Pause*100);
	}
	return 0;
}


void First_Section()
{
	for(float i = 0; true; i++){
		clear();
		float tmp = i*(2*M_PI);

		Draw_Sun();
		if(mercury)
			Draw_Mercury(tmp, 3);
		if(venus)
			Draw_Venus(tmp, 5);
		Draw_Earth(tmp,7,moon);
		if(march)
			Draw_March(tmp, 9);

		move(1, 1);
		char sec[15];
		sprintf(sec, "%f", tmp_Pause);
		addstr(sec);
		addstr("s/an");
		refresh();

		if(read_clavier())
			return;
	}
}


void All_Galaxie()
{
	system("xdotool key Ctrl+minus");
	system("xdotool key Ctrl+minus");
	system("xdotool key Ctrl+minus");
	system("xdotool key Ctrl+minus");
	system("xdotool key Ctrl+minus");
	tmp_Pause=0.1;
	for(float i = 0; true; i++){
		clear();
		float tmp = i*(2*M_PI);

		Draw_Sun_A();
		Draw_Mercury_A(tmp, 3);
		Draw_Venus_A(tmp, 4);
		Draw_Earth_A(tmp,5);
		Draw_March_A(tmp, 6);
		Draw_Ceinture_A(7);

		Draw_Jupiter_A(tmp, 9);
		Draw_Saturn_A(tmp, 12);
		Draw_Uranus_A(tmp, 16);
		Draw_Neptune_A(tmp, 20);


		move(1, 1);
		char sec[15];
		sprintf(sec, "%f", tmp_Pause*750);
		addstr(sec);
		addstr("s/an");
		refresh();

		if(read_clavier())
			return;
	}

}


int main(int argc, char *argv[])
{
	if(std::string(argv[argc-1])== "back"){
     	std::cout << "salut" << std::endl;
      	system("xterm ./prog");
		return 0;	
	}
	initscr();
	cbreak();
	if(argc > 1){
		option(argc, argv);
	}
	
	noecho();
	curs_set(0);	
	nodelay(stdscr, TRUE);
	leaveok(stdscr, TRUE);
	scrollok(stdscr, FALSE);
	system("xdotool key Ctrl+0");

    if(all_Galaxie)
    	All_Galaxie();
    else
    	First_Section();


	system("xdotool key Ctrl+0");
	endwin();
	return 0;
}
