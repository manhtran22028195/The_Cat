#include "ending.h"

void ending::init(SDL_Renderer* render, TTF_Font* font) {
	loadtext(font, win, render, "YOU WIN", brown);
	loadtext(font, lose, render, "YOU LOSE", brown);
	loadtext(font, again, render, "DO YOU WANT TO PLAY AGAIN?", brown);
}

void ending::winning(SDL_Renderer* render) {
	int h = 30;
	SDL_Rect tmp = { window_w/2 - 4 * letter_size,200,letter_size * 8, h};
	SDL_RenderCopy(render, win, NULL, &tmp);
	tmp = { window_w / 2 - letter_size * 13*2/3, 300, 27*letter_size / 3 * 2, 20 };
	SDL_RenderCopy(render, again, NULL, &tmp);
}
void ending::losing(SDL_Renderer* render) {
	int h = 30;
	SDL_Rect tmp = { window_w / 2 - 4 * letter_size,200,letter_size * 8, h };
	SDL_RenderCopy(render, lose, NULL, &tmp);
	tmp = { window_w / 2 - letter_size * 13 * 2 / 3, 300, 27 * letter_size / 3 * 2, 20 };
	SDL_RenderCopy(render, again, NULL, &tmp);
}