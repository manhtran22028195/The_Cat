#pragma once
#include "mainfunction.h"
class button{
public:
	static int mouse_x, mouse_y;
	void render(SDL_Renderer* renderr);
	void loadbutton(SDL_Renderer* render,string up,string down);
	void set_pos(int x, int y,int w,int h);
	bool inbut();
	SDL_Rect get_pos() { return pos; }
private:
	SDL_Texture* up, *down;
	SDL_Rect pos={-1000,0,0,0};
};