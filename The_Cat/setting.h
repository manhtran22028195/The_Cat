#pragma once
#include "mainfunction.h"

class setting {
public:
	setting();
	void set_volume(int x);
	void set_hard(int x);
	void render(SDL_Renderer* render);
	int in_but(int x,int y);
	void init(SDL_Renderer* render, TTF_Font* font);
	void game_setting(int x,int y,SDL_Event&e);
	int hard_level() { return rect_but_hard.x-625; }
	int sound_value() { return rect_but_volume.x - 530; }
private:
	SDL_Rect rect_board, rect_settingg, rect_but_hard, rect_but_volume, rect_setting_volume_bar, rect_setting_hard_bar, rect_hard, rect_volume, Default;
	SDL_Texture* board, *settingg, *but_hard,*but_volume, *setting_bar_on, *setting_bar_off,*hard,*volume;
	int bar_w = 192, bar_h = 32;
};