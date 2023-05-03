#ifndef meo_h_
#define meo_h_
#include "mainfunction.h"

class meo {
public:
	void init(SDL_Renderer* render);

	void move(SDL_Renderer* render);

	void jump(SDL_Renderer* render);

	void walk(SDL_Renderer* render);

	void idle(SDL_Renderer* render);

	void fall(SDL_Renderer* render);

	void attack1(SDL_Renderer* render);
	void attack2(SDL_Renderer* render);
	void attack3(SDL_Renderer* render);

	void cool_down_skill(SDL_Renderer* render);

	void takedame(SDL_Renderer* render);

	void death(SDL_Renderer* render);

	void reset();

	void draw_hp(SDL_Renderer*render);

	bool onground();

	void range_update();
	void range2_update(SDL_Renderer* render);

	void take_damed(int dame);

	SDL_Rect getrange();

	SDL_Rect getpos();

	SDL_Rect get_real_pos() { return real_pos; }

	int get_skill_1_dame() { return skill_1_dame; }

	int get_skill_2_dame() { return skill_2_dame; }

	int get_skill_3_dame() { return skill_3_dame; }

	int get_hp() { return HP; }

	bool dead() { return (i_death == 16); }

	static int score;

	unsigned int get_time_take_dame() { return time_take_dame; }

	class skill {
		public:
			
			void set_range(SDL_Rect _range) {
				range = _range;
			}

			SDL_Rect* get_range() {
				return &range;
			}
			
			skill(int _dame, int _cooldown_time) : dame(_dame), cooldown_time(_cooldown_time) {
				pre_use = -cooldown_time + 1;
			}

			int get_dame() {
				return dame;
			}

			bool is_ready() {
				return cooldown(pre_use,cooldown_time,timer);
			}

			void use() {
				if (is_ready()) {
					pre_use = timer->getTicks();
				}
			}
			void set_right(bool is_right) {
				right = is_right;
			}

			bool get_right() {
				return right;
			}

			int get_pre_use() { return pre_use; }

		private:
			int dame{};
			int cooldown_time{};
			SDL_Rect range = { -100,-100,0,0 };
			int pre_use = 0;
			bool right{};
	};

	skill skill_1 = skill (skill_1_dame, skill_1_cooldown);
	skill skill_2 = skill (skill_2_dame, skill_2_cooldown);
	skill skill_3 = skill (skill_3_dame, skill_3_cooldown);

private:

	bool attacking1 = 0, attacking2 = 0, attacking3 = 0;

	string image[76] = { "data//image//Meow_Knight1.png","data//image//Meow_Knight2.png","data//image//Meow_Knight3.png","data//image//Meow_Knight4.png","data//image//Meow_Knight5.png","data//image//Meow_Knight6.png","data//image//Meow_Knight7.png","data//image//Meow_Knight8.png","data//image//Meow_Knight9.png","data//image//Meow_Knight10.png","data//image//Meow_Knight11.png","data//image//Meow_Knight12.png","data//image//Meow_Knight13.png","data//image//Meow_Knight14.png","data//image//Meow_Knight15.png","data//image//Meow_Knight16.png","data//image//Meow_Knight17.png","data//image//Meow_Knight18.png","data//image//Meow_Knight19.png","data//image//Meow_Knight20.png","data//image//Meow_Knight21.png","data//image//Meow_Knight22.png","data//image//Meow_Knight23.png","data//image//Meow_Knight24.png","data//image//Meow_Knight25.png","data//image//Meow_Knight26.png","data//image//Meow_Knight27.png","data//image//Meow_Knight28.png","data//image//Meow_Knight29.png","data//image//Meow_Knight30.png","data//image//Meow_Knight31.png","data//image//Meow_Knight32.png","data//image//Meow_Knight33.png","data//image//Meow_Knight34.png","data//image//Meow_Knight35.png","data//image//Meow_Knight36.png","data//image//Meow_Knight37.png","data//image//Meow_Knight38.png","data//image//Meow_Knight39.png","data//image//Meow_Knight40.png","data//image//Meow_Knight41.png","data//image//Meow_Knight42.png","data//image//Meow_Knight43.png","data//image//Meow_Knight44.png","data//image//Meow_Knight45.png","data//image//Meow_Knight46.png","data//image//Meow_Knight47.png","data//image//Meow_Knight48.png","data//image//Meow_Knight49.png","data//image//Meow_Knight50.png","data//image//Meow_Knight51.png","data//image//Meow_Knight52.png","data//image//Meow_Knight53.png","data//image//Meow_Knight54.png","data//image//Meow_Knight55.png","data//image//Meow_Knight56.png","data//image//Meow_Knight57.png","data//image//Meow_Knight58.png","data//image//Meow_Knight59.png","data//image//Meow_Knight60.png","data//image//Meow_Knight61.png","data//image//Meow_Knight62.png","data//image//Meow_Knight63.png","data//image//Meow_Knight64.png","data//image//Meow_Knight65.png","data//image//Meow_Knight66.png","data//image//Meow_Knight67.png","data//image//Meow_Knight68.png","data//image//Meow_Knight69.png" ,"data//image//health_bar_decoration.png","data//image//health_bar.png","data//image//attack.png","data//image//attack_1.png","data//image//attack_2.png","data//image//vien.png","data//image//attack_3.png" };

	SDL_Texture* textureanimation[76];

	SDL_Rect pos = { 0,420,240,240 };

	SDL_Rect map_pos={0,0,40,50};

	SDL_Rect real_pos = { 0,0,40,50 };

	int i_jump = 0, i_walk = 0, i_idle = 0, i_fall = 0,i_attack1=0,i_attack2=0,i_attack3=0,i_takedame=0,i_death=0;

	const Uint8* state = SDL_GetKeyboardState(NULL);

	bool is_right = 1;

	bool jumping = 1;

	int skill_1_dame = 1000;
	int skill_1_cooldown = 500;

	int skill_2_dame = 40;
	int skill_2_cooldown = 4000;

	int skill_3_dame = 80;
	int skill_3_cooldown = 5000;

	bool is_take_dame = 0;

	int gravity = 2;

	unsigned int time=0,time_take_dame=0;

	int HP = 100;
};
#endif // meo.h