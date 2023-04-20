#include "mainfunction.h"
#include "background.h"
#include "meo.h"
#include "bat.h"
#include "skeleton.h"
#include "boss.h"
#include "game_event.h"
#include "setting.h"
#include "menu.h"

int main(int amn, char* arvg[]) {
	srand(time(NULL));

	init(window, render, font);
	setting setting;
	backgroundd x;
	meo meo;
	vector <bat> v_bat;
	bat bat;
	vector <skeleton> v_skeleton;
	skeleton skeleton;
	boss boss;
	menu menu{};
	load_icon(window, "data//image//meo.png");

	bat.loadanimation(render);
	meo.init(render);
	skeleton.loadanimation(render);
	boss.loadanimation(render);
	x.loadbackground(render);
	menu.init(render);
	setting.init(render, font);

	const int framedelay = 30;
	Uint32 framestart;
	int frametime;
	bool is_running = 1;
	SDL_Texture* time{};
	SDL_Texture* pause_texture{};
	Mix_PlayChannel(1, menu.bgmiusic, 1);
	enum game_state { in_game, in_pause, in_menu, in_setting };
	game_state Game_state = in_menu;
	while (is_running) {
		
		int h = 1, y = 1;
		framestart = timer->getTicks();
		SDL_GetMouseState(&menu.start.mouse_x,&menu.start.mouse_y);
		SDL_PollEvent(&e);
		switch (Game_state){
		case in_menu:
			x.backgroundupdate(render);	

			menu.start.set_pos(window_w / 2 - 270 / 2, window_h - 300, 270, 81);
			menu.start.render(render);

			menu.exit.set_pos(window_w / 2 - 50 - button_w / 2, window_h - 200, button_w, button_h);
			menu.exit.render(render);

			menu.off.set_pos(window_w / 2 + 50 - button_w / 2, window_h - 200, button_w, button_h);
			menu.off.render(render);

			menu.hoi.set_pos(window_w / 2 - 150 - button_w / 2, window_h - 200, button_w, button_h);
			menu.hoi.render(render);

			menu.setting.set_pos(window_w / 2 + 150 - button_w / 2, window_h - 200, button_w, button_h);
			menu.setting.render(render);

			meo.idle(render);
			
			if (menu.start.inbut() && e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
				Game_state = in_game;
				timer->start();
				continue;
			}
			if (menu.setting.inbut() && e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
				Game_state = in_setting;
				continue;
			}
			if (menu.exit.inbut() && e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
				return 0;
			}
			break;
		case in_pause:
			SDL_RenderCopy(render, pause_texture, NULL, NULL);
			menu.render_board(render, 600, 500);

			menu.pause.set_pos(window_w / 2 - button_w / 2 + 200, window_h - 300, button_w, button_h);
			menu.pause.render(render);

			menu.home.set_pos(window_w/2+button_w/2-200, window_h - 300, button_w, button_h);
			menu.home.render(render);

			SDL_WaitEvent(&e);
			if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
				if (menu.home.inbut()) {
					meo.reset();
					boss.reset();
					v_bat.clear();
					v_skeleton.clear();
					x.reset();
					Game_state = in_menu;
					timer->start();
					continue;
				}
				if (menu.pause.inbut()) {
					Game_state = in_game;
					timer->unpause();
				}
			}
			break;
		case in_game:
			x.getpos = meo.getpos();

			x.backgroundupdate(render);

			if (framestart % 1000 <= 11 && v_skeleton.size() < 20&& timer->getTicks() < 10000)
				spawn(v_bat, bat, v_skeleton, skeleton);
			if (timer->getTicks()>10000)
				boss_impact(boss, meo, render);

			bat_impact(v_bat, meo,render);

			skeleton_impact(v_skeleton, meo, render);
			
			meo.move(render);

			if (menu.pause.inbut() && e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
				Game_state = in_pause;
				timer->pause();
				pause_screen(render, pause_texture);
				menu.render_board(render, 600, 500);
				menu.pause.set_pos(window_w / 2 - button_w / 2 + 200, window_h - 300, button_w, button_h);

				menu.home.set_pos(window_w / 2 + button_w / 2 - 200, window_h - 300, button_w, button_h);
				menu.home.render(render);
			}
			menu.pause.render(render);
			menu.pause.set_pos(1100, 50, button_w, button_h);
			break;
		case in_setting:
			x.backgroundupdate(render);
			meo.idle(render);
			setting.game_setting(menu.start.mouse_x, menu.start.mouse_y,e);
			setting.render(render);
			menu.exit.render(render);
			menu.exit.set_pos(window_w / 2 - button_w / 2, window_h - 130, button_w, button_h);
			Mix_Volume(1, (float(setting.sound_value())/190)* MIX_MAX_VOLUME);
			if (menu.exit.inbut() && e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
			{
				Game_state = in_menu;
				boss.set_level(setting.hard_level());
				bat.set_level(setting.hard_level());
				skeleton.set_level(setting.hard_level());
			}
			break;
		}
		while (SDL_PollEvent(&e))
			if (e.type == SDL_QUIT)
			{
				is_running = 0;
				return 0;
			}
		
		frametime =  timer->getTicks() - framestart;
		
		if (meo.get_hp() <= 0)
		{
			meo.reset();
			boss.reset();
			v_bat.clear();
			v_skeleton.clear();
			x.reset();
			Game_state=in_menu;
			timer->start();
			continue;
		}
	
		SDL_RenderPresent(render);
		SDL_RenderClear(render);

		if (frametime < framedelay) {
			SDL_Delay(framedelay - frametime);
		}
	}
	return 0;
}