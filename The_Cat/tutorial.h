#pragma once
#include "mainfunction.h"
#include "button.h"

class tutorial {
	string s = "			You play the role of Super Cat, defending your hometown against the evil wizard. The fate of the town rests on your shoulders, and you must use all your skills and abilities to defeat the powerful wizard.\n			To attack you can press the z, x, or c keys on your keyboard.\n			To move use the up, left, and right arrow keys.\n			With quick reflexes and smart tactics, you can defeat the wizardand save your town from certain doom.Are you up to the challenge ? Give it your best shot and see if you can emerge victorious!\n";
	SDL_Texture* doc;
	SDL_Rect rect_doc = { 350,125,10,30 };
	int size_h = 30, size_w = 10;
public:
	void load_doc(SDL_Renderer* render, TTF_Font* font, SDL_Color color);
	tutorial();
};