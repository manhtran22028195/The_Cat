#include "button.h"
int button::mouse_x = 0;
int button::mouse_y = 0;
void button::loadbutton(SDL_Renderer* render, string s_up, string s_down) {
	loadtexture(render, up, s_up);
	loadtexture(render, down, s_down);
	SDL_QueryTexture(up, NULL, NULL, &pos.w, &pos.h);
}
void button::set_pos(int x,int y,int w, int h) {
	pos.x = x;
	pos.y = y;
	pos.w = w;
	pos.h = h;
}

void button::render(SDL_Renderer*renderr) {
	if (inbut())
		SDL_RenderCopy(renderr, down, NULL, &pos);
	else
		SDL_RenderCopy(renderr, up, NULL, &pos);
}

bool button::inbut() {
	return check_collision({ mouse_x,mouse_y,0,0 }, pos);
}