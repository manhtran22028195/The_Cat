#pragma once
#include "mainfunction.h"
class skeleton {
public:
	~skeleton();

	void set_level(int hard_level);

	void move(SDL_Renderer* render);

	void death(SDL_Renderer* render);

	void attack(SDL_Renderer* render);

	void walk(SDL_Renderer* render);

	void takedame(SDL_Renderer* render);

	void idle(SDL_Renderer* render);

	bool is_right();

	void loadanimation(SDL_Renderer* render);

	void get_delta_c_pos();

	void range_update();

	void take_dame(int dame) { is_take_dame = 1; hp -= dame; }

	void draw_hp(SDL_Renderer* render);

	int get_dame() { return dame; }

	SDL_Rect get_c_real_pos();

	void set_pos(SDL_Rect _pos) {
		pos = _pos;
	}

	SDL_Rect get_range();

	SDL_Rect get_real_pos() { return real_pos; }

	int get_i_death() { return i_death; }

	int delta_c_pos=0;
	
	SDL_Rect get_c_pos = { 0,0,0,0 };
private:
	int hp = 500;

	int dame = 10;

	unsigned int time = 0;

	int i_walk = 0, i_attack = 0, i_idle = 0, i_takedame = 0, i_death = 0;

	bool attacking = 0, is_take_dame = 0;

	bool right = is_right();

	SDL_Rect range = { -1000,0,0,0 };

	SDL_Rect pre_c_pos={ 0,0,0,0 };

	string image[65] = { "data//image//Skeleton1.png","data//image//Skeleton2.png","data//image//Skeleton3.png","data//image//Skeleton4.png","data//image//Skeleton5.png","data//image//Skeleton6.png","data//image//Skeleton7.png","data//image//Skeleton8.png","data//image//Skeleton9.png","data//image//Skeleton10.png","data//image//Skeleton11.png","data//image//Skeleton12.png","data//image//Skeleton13.png","data//image//Skeleton14.png","data//image//Skeleton15.png","data//image//Skeleton16.png","data//image//Skeleton17.png","data//image//Skeleton18.png","data//image//Skeleton19.png","data//image//Skeleton20.png","data//image//Skeleton21.png","data//image//Skeleton22.png","data//image//Skeleton23.png","data//image//Skeleton24.png","data//image//Skeleton25.png","data//image//Skeleton26.png","data//image//Skeleton27.png","data//image//Skeleton28.png","data//image//Skeleton29.png","data//image//Skeleton30.png","data//image//Skeleton31.png","data//image//Skeleton32.png","data//image//Skeleton33.png","data//image//Skeleton34.png","data//image//Skeleton35.png","data//image//Skeleton36.png","data//image//Skeleton37.png","data//image//Skeleton38.png","data//image//Skeleton39.png","data//image//Skeleton40.png","data//image//Skeleton41.png","data//image//Skeleton42.png","data//image//Skeleton43.png","data//image//Skeleton44.png","data//image//Skeleton45.png","data//image//Skeleton46.png","data//image//Skeleton47.png","data//image//Skeleton48.png","data//image//Skeleton49.png","data//image//Skeleton50.png","data//image//Skeleton51.png","data//image//Skeleton52.png","data//image//Skeleton53.png","data//image//Skeleton54.png","data//image//Skeleton55.png","data//image//Skeleton56.png","data//image//Skeleton57.png","data//image//Skeleton58.png","data//image//Skeleton59.png","data//image//Skeleton60.png","data//image//Skeleton61.png","data//image//Skeleton62.png","data//image//Skeleton63.png","data//image//Skeleton64.png","data//image//Skeleton65.png" };
	
	static SDL_Texture** animation;
	
	SDL_Rect pos = { 0,513,150,100};

	SDL_Rect pos_s = { 0,0,70,70 };

	SDL_Rect real_pos = { pos.x + 50,pos.y + 30,pos.h - 60,pos.w - 80 };

};