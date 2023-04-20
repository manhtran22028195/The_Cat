#pragma once
#include "mainfunction.h"

class bat {
public:

	~bat() {}

	void set_level(int hard_level);

	void loadanimation(SDL_Renderer* render);

	void attack(SDL_Renderer* render);

	void move(SDL_Renderer* render);

	void fly(SDL_Renderer* render);

	void take_dame() { is_death = 1; };

	void death(SDL_Renderer* render);

	void get_delta_c_pos();

	int get_dame() { return dame; }

	SDL_Rect get_c_pos;

	SDL_Rect pre_c_pos = { 570,0,0,0 };

	bool is_right();

	vector <double> angle;

	SDL_Rect get_skill() {
	}

	SDL_Rect getpos() {
		return pos;
	}

	void set_pos(SDL_Rect _pos) {
		pos = _pos;
	}

	int get_i_death(){return i_death;}

	vector <SDL_Rect> bullet;

private:
	int i_fly=0, i_attack=0, i_idle=0,i_death=0;

	SDL_Rect pos={-100,400,70,70};

	SDL_Rect skill = { 0,0,15,15 };

	string image[25] = { "data//image//bat1.png","data//image//bat2.png","data//image//bat3.png","data//image//bat4.png","data//image//bat5.png","data//image//bat6.png","data//image//bat7.png","data//image//bat8.png","data//image//bat9.png","data//image//bat10.png","data//image//bat11.png","data//image//bat12.png","data//image//bat13.png","data//image//bat14.png","data//image//bat15.png","data//image//bat16.png","data//image//bat17.png","data//image//bat18.png","data//image//bat19.png","data//image//bat20.png","data//image//bat21.png","data//image//bat22.png","data//image//bat23.png","data//image//bat24.png","data//image//chuong1.png" };

	static SDL_Texture** animation;

	unsigned int time = 0;

	unsigned int delay_time = 1000;

	bool attacking = 0;

	int delta_c_pos;

	int dame = 10;

	bool is_death = 0;

	int HP = 40;
};