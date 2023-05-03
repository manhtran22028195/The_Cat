#pragma once
#include "mainfunction.h"
class ending {
	SDL_Texture* win, * lose, * again, * time, * hard;
	int letter_size = 20;
public:
	void init(SDL_Renderer* render, TTF_Font* font);
	void winning(SDL_Renderer* render);
	void losing(SDL_Renderer* render);
	//void (
};