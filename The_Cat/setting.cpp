#include "setting.h"

setting::setting() {
	rect_board = {window_w-900,window_h-650,window_w-600,window_h-100};
	
	rect_settingg = { window_w/2- (150)/2,window_h-600,150,100};
	rect_but_hard = { window_w - 575,window_h - 355,28,42};
	rect_but_volume = { window_w - 575,window_h - 255,28,42};
	rect_setting_volume_bar = { window_w - 661,window_h - 250,bar_w,bar_h };
	rect_setting_hard_bar = { window_w - 661,window_h - 350,bar_w,bar_h };
	rect_hard = { window_w - 731,window_h - 350,14 * 3,13 * 3};
	rect_volume = { window_w - 731,window_h - 250,14 * 3,13 * 3 };

}

void setting::init(SDL_Renderer*render,TTF_Font*font) {
	loadtexture(render, board, "data//image//board.png");
	loadtext(font, settingg, render, "Setting", { 140,78,0 });
	loadtexture(render, but_hard, "data//image//setting_but.png");
	loadtexture(render, but_volume, "data//image//setting_but.png");
	loadtexture(render, setting_bar_on, "data//image//bar1.png");
	loadtexture(render, setting_bar_off, "data//image//bar2.png");
	loadtexture(render, volume, "data//image//volume.png");
	loadtexture(render, hard, "data//image//hard.png");
}

int setting::in_but(int x, int y) {
	if (check_collision({ x,y,0,0 }, rect_setting_hard_bar))
	{
		return 1;
	}
	else if (check_collision({ x,y,0,0 }, rect_setting_volume_bar))
		return 2;
	return 0;
}
void setting::game_setting(int x, int y,SDL_Event &e) {

	if (e.button.button == SDL_BUTTON_LEFT&& (x >= 530 && x < 720)) {
			if (in_but(x, y) == 1) {
				rect_but_hard.x = x;
			}
			else if (in_but(x, y) == 2) {
				rect_but_volume.x = x;
			}
	}
}
void setting::render(SDL_Renderer* render) {
	SDL_RenderCopy(render, board, NULL, &rect_board);
	SDL_RenderCopy(render, settingg, nullptr, &rect_settingg);
	SDL_RenderCopy(render, setting_bar_on, NULL, &rect_setting_volume_bar);
	SDL_RenderCopy(render, setting_bar_on, NULL, &rect_setting_hard_bar);

	SDL_Rect tmp = { (rect_but_volume.x - 530) / 2 ,0,rect_setting_volume_bar.w, rect_setting_volume_bar.h };
	SDL_Rect tmp1 = { rect_but_volume.x + 9,rect_setting_volume_bar.y, -rect_but_volume.x - 9 + (rect_setting_volume_bar.x + rect_setting_volume_bar.w), rect_setting_volume_bar.h };;
	SDL_RenderCopy(render, setting_bar_off, &tmp, &tmp1);
	
	tmp = { (rect_but_hard.x - 530)/2 ,0,rect_setting_hard_bar.w, rect_setting_hard_bar.h };
	tmp1 = { rect_but_hard.x+9,rect_setting_hard_bar.y, -rect_but_hard.x - 9+ (rect_setting_hard_bar.x+ rect_setting_hard_bar.w), rect_setting_hard_bar.h };
	SDL_RenderCopy(render, setting_bar_off, &tmp, &tmp1);

	SDL_RenderCopy(render, but_hard, NULL, &rect_but_hard);
	SDL_RenderCopy(render, but_volume, NULL, &rect_but_volume);

	SDL_RenderCopy(render, hard, NULL, &rect_hard);
	SDL_RenderCopy(render, volume, NULL, &rect_volume);
}
