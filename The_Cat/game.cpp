#include "mainfunction.h"
#include "background.h"
#include "meo.h"
#include "bat.h"
#include "skeleton.h"
#include "boss.h"
#include "game_event.h"
#include "setting.h"
#include "menu.h"
#include "ending.h"
#include "tutorial.h"
#include "high_socre.h"

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
	ending ending;
	tutorial tutorial;
	HighScore highscore;
	load_icon(window, "data//image//meo.png");

	bat.loadanimation(render);
	meo.init(render);
	ending.init(render, font);
	skeleton.loadanimation(render);
	boss.loadanimation(render);
	x.loadbackground(render);
	menu.init(render);
	setting.init(render, font);

	const int framedelay = 30;
	Uint32 framestart;
	int frametime;
	bool is_running = 1;
	SDL_Texture* pause_texture{};
	Mix_PlayChannel(1, menu.bgmiusic, 1);
	int boss_time = 20000;
	enum game_state { in_game, in_pause, in_menu, in_setting,in_lose,in_win ,in_toturial,in_highscore};
	game_state Game_state = in_menu;
	while (is_running) {
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

			menu.record.set_pos(window_w / 2 + 50 - button_w / 2, window_h - 200, button_w, button_h);
			menu.record.render(render);

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
			if (menu.record.inbut() && e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
				Game_state = in_highscore;
				continue;
			}
			if (menu.setting.inbut() && e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
				Game_state = in_setting;
				continue;
			}
			if (menu.exit.inbut() && e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
				return 0;
			}
			if (menu.hoi.inbut() && e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
			{
				Game_state = in_toturial;
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

			if (framestart % 1000 <= 11 && v_skeleton.size() < 20&& timer->getTicks() < boss_time)
				spawn(v_bat, bat, v_skeleton, skeleton);
			if (timer->getTicks()>boss_time)
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
		case in_win:
			SDL_RenderCopy(render, pause_texture, NULL, NULL);
			ending.winning(render);
			menu.yes.set_pos(window_w / 2 - 100 - button_w / 2, window_h - 200, button_w, button_h);
			menu.yes.render(render);
			menu.no.set_pos(window_w / 2 + 100 - button_w / 2, window_h - 200, button_w, button_h);
			menu.no.render(render);
			if (menu.yes.inbut() && e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
				Game_state = in_game;
				timer->start();
				continue;
			}
			if (menu.no.inbut() && e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
				Game_state = in_menu;
				timer->start();
				continue;
			}
			break;
		case in_lose:
			SDL_RenderCopy(render, pause_texture, NULL, NULL);
			ending.losing(render);
			menu.yes.set_pos(window_w / 2 - 100 - button_w / 2, window_h - 200, button_w, button_h);
			menu.yes.render(render);
			menu.no.set_pos(window_w / 2 + 100 - button_w / 2, window_h - 200, button_w, button_h);
			menu.no.render(render);
			if (menu.yes.inbut() && e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
				Game_state = in_game;
				timer->start();
				continue;
			}
			if (menu.no.inbut() && e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
				Game_state = in_menu;
				timer->start();
				continue;
			}
			break;
		case in_toturial:
			x.backgroundupdate(render);
			meo.idle(render);
			menu.render_board(render, 600, 500);
			tutorial.load_doc(render, font, brown);
			menu.exit.render(render);
			menu.exit.set_pos(window_w / 2 - button_w / 2, window_h - 160, button_w, button_h);
			if (menu.exit.inbut() && e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
			{
				Game_state = in_menu;
			}
			break;
		case in_highscore:
			x.backgroundupdate(render);
			meo.idle(render);
			menu.render_board(render, 600, 500);
			highscore.printScores(render,font);
			menu.exit.render(render);
			menu.exit.set_pos(window_w / 2 - button_w / 2, window_h - 160, button_w, button_h);
			if (menu.exit.inbut() && e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
			{
				Game_state = in_menu;
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
		
		if (meo.dead())
		{
			pause_screen(render, pause_texture);
			Game_state = in_lose;
			meo.reset();
			boss.reset();
			v_bat.clear();
			v_skeleton.clear();
			x.reset();
		}
		if (boss.get_HP() <= 0) {
			pause_screen(render, pause_texture);
			Game_state = in_win;
			meo.reset();
			boss.reset();
			v_bat.clear();
			v_skeleton.clear();
			x.reset();
			highscore.addScore({ setting.hard_level() + 95, timer->getTicks()/1000 });
		}
	
		SDL_RenderPresent(render);
		SDL_RenderClear(render);
		if (frametime < framedelay) {
			SDL_Delay(framedelay - frametime);
		}
	}
	return 0;
}