#pragma once
#ifndef background
#define background
#include "mainfunction.h"
#include "meo.h"

class backgroundd
{
public:
	int vel = 0;
	SDL_Rect getpos;
	
	//mây bay :))
	SDL_Texture *layer1;
	SDL_Rect rect1 = {0,0,background_w,background_h};
	SDL_Rect rect11 = { background_w,0,background_w,background_h };
	SDL_Rect rect111 = { -background_w,0,background_w,background_h };
	
	SDL_Texture* layer2;
	SDL_Rect rect2 = { 0,0,background_w,background_h };

	SDL_Texture* house_a;
	SDL_Rect rect_house_a = {0,248,336,366};
	SDL_Texture* house_b;
	SDL_Rect rect_house_b = { 400,126,420,488};
	SDL_Texture* house_c;
	SDL_Rect rect_house_c = { 800,248,442,366};

	SDL_Texture* street_lamp;
	SDL_Rect rect_street_lamp={0,398,70,216};
	SDL_Texture* wagon;
	SDL_Rect rect_wagon={0,464,186,150};
	SDL_Texture* well;
	SDL_Rect rect_well={0,490,130,130};

	SDL_Texture* ground_a;
	SDL_Rect rectground_a = {0,590,39,117 };
	SDL_Texture* ground_b;
	SDL_Rect rectground_b= {39,590,39,117 };

	void loadbackground(SDL_Renderer*&render);
	void backgroundupdate(SDL_Renderer*&render);
	void reset();
};
#endif // !background