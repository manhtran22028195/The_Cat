#pragma once
#include "mainfunction.h"
class boss {
public:

	void set_level(int hard_level);

	void loadanimation(SDL_Renderer* render);

	void attack1(SDL_Renderer* render);

	void attack2(SDL_Renderer* render);

	void attack3(SDL_Renderer* render);

	void move(SDL_Renderer* render);

	void fly(SDL_Renderer* render);

	//int get_dame() { return dame; }

	void take_dame(int i) {
		HP -= i;
	}

	void death(SDL_Renderer* render);

	bool is_right();

	void get_delta_c_pos();

	SDL_Rect get_c_pos;

	SDL_Rect pre_c_pos = { 570,0,0,0 };

	vector <double> angle1;

	double get_angle(SDL_Point pos);

	SDL_Rect get_skill() {
	}

	SDL_Rect getpos() {
		return { pos.x + 160,pos.y + 160,pos.w - 300,pos.h - 230 };
	}

	int get_i_death() { return i_death; }

	vector <SDL_Rect> bullet1;
	void remove_bullet1(int i);

	vector <SDL_Rect> bullet2;
	void remove_bullet2(int i);

	vector <SDL_Rect> bullet3;

	int get_dame() { return dame; }

	int get_HP() { return HP; }

	void reset();
private:
	int i_fly = 0, i_attack1 = 0, i_attack2 = 0,i_attack3=0, i_idle = 0, i_death = 0;

	SDL_Rect pos = { 1300,100,400,400 };

	string image[70] = { "data//image//boss1.png", "data//image//boss2.png", "data//image//boss3.png", "data//image//boss4.png", "data//image//boss5.png", "data//image//boss6.png", "data//image//boss7.png", "data//image//boss8.png", "data//image//boss9.png", "data//image//boss10.png", "data//image//boss11.png", "data//image//boss12.png", "data//image//boss13.png", "data//image//boss14.png", "data//image//boss15.png", "data//image//boss16.png", "data//image//boss17.png", "data//image//boss18.png", "data//image//boss19.png", "data//image//boss20.png", "data//image//boss21.png", "data//image//boss22.png", "data//image//boss23.png", "data//image//boss24.png", "data//image//boss25.png", "data//image//boss26.png", "data//image//boss27.png", "data//image//boss28.png", "data//image//boss29.png", "data//image//boss30.png", "data//image//boss31.png", "data//image//boss32.png", "data//image//boss33.png", "data//image//boss34.png", "data//image//boss35.png", "data//image//boss36.png", "data//image//boss37.png", "data//image//boss38.png", "data//image//boss39.png", "data//image//boss40.png", "data//image//boss41.png", "data//image//boss42.png", "data//image//boss43.png", "data//image//boss44.png", "data//image//boss45.png", "data//image//boss46.png", "data//image//boss47.png", "data//image//boss48.png", "data//image//boss49.png", "data//image//boss50.png", "data//image//boss51.png", "data//image//boss52.png", "data//image//boss53.png", "data//image//boss54.png", "data//image//boss55.png", "data//image//boss56.png", "data//image//boss57.png", "data//image//boss58.png", "data//image//boss59.png", "data//image//boss60.png", "data//image//boss61.png", "data//image//boss62.png", "data//image//boss63.png", "data//image//boss64.png", "data//image//boss65.png", "data//image//boss66.png", "data//image//boss67.png", "data//image//boss68.png", "data//image//boss69.png","data//image//chuong1.png"};

	SDL_Texture* animation[70];

	int time = 0;

	unsigned int delay_time = 1000;

	int dame = 20;

	//bullet type 1

	float angle_attack1;

	vector <float> r;

	SDL_Point center;

	bool attacking1 = 0;

	int delta_c_pos;

	int attack1_time = 0;

	int r_attack1 = pos.w / 3;

	void spawn_triangle();
	void spawn_square();
	void bullet1_clear();
	//bullet type 2

	vector <float> angle2;

	float turn_attack;

	vector <float> angle_attack2;

	bool attacking2 = 0;

	int attack2_time = 0;

	int r_attack2 = pos.w / 2;

	void bullet2_move(SDL_Renderer*render);
	
	//bullet type 3

	bool attacking3 = 0;

	int attack3_time = 0;

	int spawn_time = 0;

	bool is_death = 0;

	int default_HP = 4000;

	int HP = 4000;

	void draw_hp(SDL_Renderer*render);

	int a = 0;
};