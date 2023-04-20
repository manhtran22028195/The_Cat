#pragma once
#include "mainfunction.h"
#include "button.h"
class menu {
public:
	void init(SDL_Renderer * render);
	button start, hoi, yes, no,exit,off,home,pause,setting;
	SDL_Rect rect_board;
	SDL_Texture* board;
	void render_board(SDL_Renderer*render, int w,int h);
	Mix_Chunk* bgmiusic;
};