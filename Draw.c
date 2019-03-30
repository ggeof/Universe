#include <ncurses.h>
#include <math.h>

struct vec2{
	int x;
	int y;
};

vec2 Transformation(int pos, float tmp, int div){
	vec2 coord;
	coord.x = pos*(LINES/div)*sin(tmp)+LINES/2;
	coord.y = pos*(COLS/div)*cos(tmp)+COLS/2;
	return coord;
}

void Planet_S(vec2 pos){
	move(pos.x, pos.y);
	addstr("/\\");
	move(pos.x+1, pos.y);
	addstr("\\/");
}

void Planet_M(vec2 pos, char letters){
	move(pos.x-1,pos.y-1);
	addstr(" __ ");
	move(pos.x, pos.y-1);
	addstr("/");
	char l[15];
	sprintf(l, "%c", letters);
	addstr(l);
	addstr(" \\");
	move(pos.x+1,pos.y-1);
	addstr("\\__/");
}

void Planet_L(vec2 pos, char letters){
	move(pos.x-2, pos.y-3);
	addstr("  ___ ");
	move(pos.x-1, pos.y-3);
	addstr(" /   \\");
	move(pos.x, pos.y-3);
	addstr("|  ");
	char l[15];
	sprintf(l, "%c", letters);
	addstr(l);
	addstr("  |");
	move(pos.x+1, pos.y-3);
	addstr(" \\___/");
}


void Draw_Sun(){
	vec2 pos;
	pos.x=LINES/2;
	pos.y=COLS/2;
	Planet_L(pos, 'S');
}

void Draw_Sun_A(){
		move(LINES/2-3, COLS/2-5);
		addstr("  _______ ");
		move(LINES/2-2, COLS/2-5);
		addstr(" /       \\");
		move(LINES/2-1, COLS/2-5);
		addstr("/         \\");
		move(LINES/2, COLS/2-5);
		addstr("|    S    |");
		move(LINES/2+1, COLS/2-5);
		addstr("|         |");
		move(LINES/2+2, COLS/2-5);
		addstr("\\         /");
		move(LINES/2+3, COLS/2-5);
		addstr(" \\_______/");
}


void Draw_Mercury(float tmp, int pos){
	tmp = tmp/18;
	Planet_S(Transformation(pos, tmp, 20));
}

void Draw_Mercury_A(float tmp, int pos){
	tmp = tmp/18;
	vec2 coord = Transformation(pos, tmp, 40);
	move(coord.x, coord.y);
	addstr(".M");
}

void Draw_Venus(float tmp, int pos){
	tmp = tmp/45;
	Planet_M(Transformation(pos, tmp, 20), 'V');
}

void Draw_Venus_A(float tmp, int pos){
	tmp = tmp/45;
	vec2 coord = Transformation(pos, tmp, 40);
	move(coord.x, coord.y);
	addstr(".V");
}

void Draw_Earth(float tmp, int pos, bool moon){
	float tmp1 = tmp /75;
	vec2 coord = Transformation(pos, tmp1, 20);
	Planet_M(coord, 'E');
	if(moon){
		int xm = 3*cos(tmp/10)+coord.x;
		int ym = 5*sin(tmp/10)+coord.y; 
		move(xm+1, ym+1);
		addstr(".");
	}
}

void Draw_Earth_A(float tmp, int pos){
	tmp = tmp/75;
	vec2 coord = Transformation(pos, tmp, 40);
	move(coord.x, coord.y);
	addstr(".E");
}

void Draw_March(float tmp, int pos){
	tmp = tmp/141;
	Planet_S(Transformation(pos, tmp, 20));
}

void Draw_March_A(float tmp, int pos){
	tmp = tmp/141;
	vec2 coord = Transformation(pos, tmp, 40);
	move(coord.x, coord.y);
	addstr(".M");
}

void Draw_Jupiter_A(float tmp, int pos){
	tmp = tmp/885;
	Planet_L(Transformation(pos, tmp, 40), 'J');
}

void Draw_Saturn_A(float tmp, int pos){
	tmp = tmp/2217;
	Planet_L(Transformation(pos, tmp, 40), 'S');
}

void Draw_Uranus_A(float tmp, int pos){
	tmp = tmp/6300;
	Planet_M(Transformation(pos, tmp, 40), 'U');
}

void Draw_Neptune_A(float tmp, int pos){
	tmp = tmp/12300	;
	Planet_M(Transformation(pos, tmp, 40), 'N');
}

void Draw_Ceinture_A(int pos){
	float div = 20; // Number of asteroide
	float step = 2*M_PI/div;
	int x, y;
	for (int i = 0; i < div; ++i)
	{
		float a = i*step;
		x = pos*(COLS/40)*cos(a)+COLS/2;
		y = pos*(LINES/40)*sin(a)+LINES/2;
		move(y, x);
		addstr(".");
	}
}
