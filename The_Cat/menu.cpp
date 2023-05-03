#include "menu.h"
void menu::init(SDL_Renderer* render) {
	start.loadbutton(render, "data//image//start1.png", "data//image//start2.png");
	
	hoi.loadbutton(render, "data//image//hoicham1.png", "data//image//hoicham2.png");
	
	exit.loadbutton(render, "data//image//exit1.png", "data//image//exit2.png");

	record.loadbutton(render, "data//image//record1.png", "data//image//record2.png");
	
	off.loadbutton(render, "data//image//off1.png", "data//image//off2.png");
	
	setting.loadbutton(render, "data//image//setting1.png", "data//image//setting2.png");
	
	home.loadbutton(render, "data//image//home1.png", "data//image//home2.png");
	
	pause.loadbutton(render, "data//image//pause1.png", "data//image//pause3.png");
	
	yes.loadbutton(render, "data//image//yes1.png", "data//image//yes2.png");
	
	no.loadbutton(render, "data//image//no1.png", "data//image//no2.png");
	
	loadtexture(render, board, "data//image//board.png");

	bgmiusic = Mix_LoadWAV("data//music//bgmusic.MP3");
	
	if (bgmiusic == nullptr) {
		cout << Mix_GetError();
	}
}

void menu::render_board(SDL_Renderer*render,int w, int h) {
	rect_board = { window_w / 2 - w / 2,window_h / 2 - h / 2,w,h };
	SDL_RenderCopy(render, board, NULL, &rect_board);
	yes.set_pos(window_w / 2 - 100 - button_w / 2, window_h - 200, button_w, button_h);
	no.set_pos(window_w / 2 + 100 - button_w / 2, window_h - 200, button_w, button_h);
}