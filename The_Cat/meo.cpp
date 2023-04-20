#include "meo.h"
int meo::score = 0;
void meo::init(SDL_Renderer*render) {
	for(int j=0;j<76;j++)
		loadtexture(render, textureanimation[j], image[j]);
	skill_1 = skill(20, skill_1_cooldown);
	skill_2 = skill(20, skill_2_cooldown);
	skill_3 = skill(100, skill_3_cooldown);
}
void meo::move(SDL_Renderer* render) {
	if (is_death) { death(render); if (!onground()) { i_fall++; if (i_fall == 13)i_fall = 0; if (pos.y + (i_fall)*gravity < ground) { pos.y += (i_fall)*gravity; } else { pos.y = ground; jumping = 1; i_jump = 0; i_fall = 0; } }}
	else if ((state[SDL_SCANCODE_C] && skill_3.is_ready()) || attacking3) { attack3(render); if (pos.y + 30 < ground) pos.y += 30;  else { pos.y = ground; jumping = 1; i_jump = 0; i_fall = 0; } }
	else if ((state[SDL_SCANCODE_X] && skill_2.is_ready()) || attacking2) { attack2(render); }
	else if (is_take_dame) { takedame(render); if (!onground()) { i_fall++; if (i_fall == 13)i_fall = 0; if (pos.y + (i_fall)*gravity < ground) { pos.y += (i_fall)*gravity; } else { pos.y = ground; jumping = 1; i_jump = 0; i_fall = 0; } }}
	else {
		SDL_PollEvent(&e);
		//get meo pos
		if (map_pos.x<window_w / 2 - 30 || map_pos.x>map_w - (window_w / 2 + 30)) {
			if (state[SDL_SCANCODE_LEFT] && pos.x > -105) { is_right = 0; pos.x -= step; }

			if (state[SDL_SCANCODE_RIGHT] && pos.x < 1060) { is_right = 1; pos.x += step; }

			if (map_pos.x < window_w)
			{
				map_pos.x = pos.x + 110;
			}
			else
			{
				map_pos.x = pos.x + 110 + map_w - window_w;
			}
		}
		else
		{
			if (state[SDL_SCANCODE_LEFT]) { is_right = 0; map_pos.x -= step; }

			if (state[SDL_SCANCODE_RIGHT]) { is_right = 1; map_pos.x += step; }
		} 
		
		
		//SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
		//SDL_RenderDrawRect(render, &real_pos);
		
		// jump
		if ((!onground() && !state[SDL_SCANCODE_UP]) || pos.y <= maxh) { jumping = 0; }

		if (state[SDL_SCANCODE_UP] && jumping) { pos.y -= (13 - i_jump) * gravity; i_jump++; if (i_jump == 13)i_jump = 0; }

		else if (!onground()) { i_fall++; if (i_fall == 13)i_fall = 0; if (pos.y + (i_fall)*gravity < ground) { pos.y += (i_fall)*gravity; } else { pos.y = ground; jumping = 1; i_jump = 0; i_fall = 0; } }

		//animation
		if ((state[SDL_SCANCODE_Z] && skill_1.is_ready()) || attacking1) { attack1(render); }
		else if (state[SDL_SCANCODE_UP] && jumping) { jump(render); }
		else if (!onground()) { fall(render); }
		else if (state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT]) { if (onground()) { walk(render); } }
		else if (state[SDL_SCANCODE_RIGHT] && !state[SDL_SCANCODE_LEFT]) { if (onground()) { walk(render); } }
		else { idle(render); }
		range_update();
	}
	if(skill_2.get_range()->x > -10000)
	range2_update(render);
	map_pos.y = pos.y + 140;
	real_pos.x = pos.x + 100, real_pos.y = pos.y + 140;
	draw_hp(render);
	cool_down_skill(render);
}
void meo::walk(SDL_Renderer* render) {
	if (is_right)
		SDL_RenderCopy(render, textureanimation[i_walk/2], NULL, &pos);
	else
		SDL_RenderCopyEx(render, textureanimation[i_walk/2], NULL, &pos, 180, NULL, SDL_FLIP_VERTICAL);

	i_walk++;
	if (i_walk == 16)
		i_walk = 0;
}
void meo::jump(SDL_Renderer* render) {
	if (is_right)
		SDL_RenderCopy(render, textureanimation[i_jump/2+15], NULL, &pos);
	else
		SDL_RenderCopyEx(render, textureanimation[i_jump/2+15], NULL, &pos, 180, 0, SDL_FLIP_VERTICAL);
}

void meo::idle(SDL_Renderer*render) {
	if (is_right)
		SDL_RenderCopy(render, textureanimation[i_idle/3+8], NULL, &pos);
	else
		SDL_RenderCopyEx(render, textureanimation[i_idle/3+8], NULL, &pos, 180, 0, SDL_FLIP_VERTICAL);

	i_idle++;
	if (i_idle == 12){
		i_idle = 0;
	}
}

void meo::fall(SDL_Renderer*render) {
	if (is_right)
		SDL_RenderCopy(render, textureanimation[i_fall/2+20], NULL, &pos);
	else
		SDL_RenderCopyEx(render, textureanimation[i_fall/2+20], NULL, &pos, 180, 0, SDL_FLIP_VERTICAL);
}
bool meo::onground() {
	return (ground == pos.y);
}

void meo::attack1(SDL_Renderer* render) {
	if (is_right)
		SDL_RenderCopy(render, textureanimation[i_attack1/3 + 45], NULL, &pos);
	else
		SDL_RenderCopyEx(render, textureanimation[i_attack1/3 + 45], NULL, &pos, 180, 0, SDL_FLIP_VERTICAL);
	if (i_attack1 == 0)
		skill_1.use();
	i_attack1++;
	if (i_attack1 == 9) {
		i_attack1 = 0;
		attacking1 = 0;
	}
	else 
		attacking1 = 1;	
	//cout << skill_1.get_pre_use()<< endl;
}
void meo::attack2(SDL_Renderer* render) {
	if (is_right)
		SDL_RenderCopy(render, textureanimation[i_attack2 / 3 + 27], NULL, &pos);
	else
		SDL_RenderCopyEx(render, textureanimation[i_attack2 / 3 + 27], NULL, &pos, 180, 0, SDL_FLIP_VERTICAL);

	i_attack2++;
	if (i_attack2 == 18) {
		i_attack2 = 0;
		attacking2 = 0;
	}
	else
		attacking2 = 1;
	if (i_attack2 == 10) {
		skill_2.set_right(is_right);
		skill_2.set_range({ real_pos.x + real_pos.w,real_pos.y + 10,30,20 });
	}
	else if (i_attack2 == 1) {
		skill_2.use();
	}
}
void meo::attack3(SDL_Renderer* render) {
	if (is_right)
		SDL_RenderCopy(render, textureanimation[i_attack3 / 3 + 53], NULL, &pos);
	else
		SDL_RenderCopyEx(render, textureanimation[i_attack3 / 3 + 53], NULL, &pos, 180, 0, SDL_FLIP_VERTICAL);
	if (i_attack3 == 0) {
		skill_3.use();
	}
	i_attack3++;
	if (i_attack3 == 21) {
		i_attack3 = 0;
		attacking3 = 0;
		skill_3.set_range({-100, -100, 0, 0});
	}
	else{
		attacking3 = 1;
		if (i_attack3 < 15) {
			skill_3.set_range({ real_pos.x + real_pos.w / 2 - i_attack3 * 10 / 2,real_pos.y + 30,i_attack3 * 10,30 });
		}
	}
}
void meo::range_update() {
	if (is_right&&attacking1)
	{
		skill_1.set_range({ pos.x + 130, pos.y + 130, 60, 60 });
	}
	else if(attacking1)
	{
		skill_1.set_range({ pos.x + 45,pos.y + 130, 60, 60 });
	}
	else 
		skill_1.set_range({ -100,-100,0,0 });
}

void meo::range2_update(SDL_Renderer* render) {
	if (skill_2.get_right())
		skill_2.set_range({ skill_2.get_range()->x +20, skill_2.get_range()->y, 60, 50});
	else if(!skill_2.get_right())
		skill_2.set_range({ skill_2.get_range()->x - 20, skill_2.get_range()->y, 60, 50 });
	if (map_pos.x > 570 && map_pos.x < map_w - 630) {
		skill_2.get_range()->x += -(-state[SDL_SCANCODE_LEFT] + state[SDL_SCANCODE_RIGHT])*step;
	}
	if (skill_2.get_range()->x > 3000 || skill_2.get_range()->x < -3000)
		skill_2.set_range({ -11000,0,0,0 });
	if(skill_2.get_right())
		SDL_RenderCopy(render, textureanimation[75], NULL, skill_2.get_range());
	else
		SDL_RenderCopyEx(render, textureanimation[75], NULL, skill_2.get_range(),180, 0, SDL_FLIP_VERTICAL);
}

void meo::takedame(SDL_Renderer* render) {
	if (is_right)
		SDL_RenderCopy(render, textureanimation[i_takedame/5 + 61], NULL, &pos);
	else
		SDL_RenderCopyEx(render, textureanimation[i_takedame/5 + 61], NULL, &pos, 180, 0, SDL_FLIP_VERTICAL);

	i_takedame++;
	if (i_takedame == 15) {
		i_takedame = 0;
		is_take_dame = 0;
		time_take_dame = timer->getTicks();
	}
}
void meo::death(SDL_Renderer* render) {
	if (is_right)
		SDL_RenderCopy(render, textureanimation[i_death + 64], NULL, &pos);
	else
		SDL_RenderCopyEx(render, textureanimation[i_death + 64], NULL, &pos, 180, 0, SDL_FLIP_VERTICAL);
	if(i_death<4)
	i_death++;
}

SDL_Rect meo::getrange() { return *skill_1.get_range(); }

void meo::reset() {
	pos = { 0,420,240,240 };
	map_pos = { 0,0,40,50 };
	real_pos = { 0,0,40,50 };
	i_jump = 0, i_walk = 0, i_idle = 0, i_fall = 0, i_attack3 = 0, i_takedame = 0, i_death = 0, attacking1=0;
	is_right = 1;
	jumping = 1;
	is_death = 0;
	is_take_dame = 0;
	time_take_dame = 0;
	skill_2.set_range({ -13000,0,0,0 });
	skill_1 = skill(20, skill_1_cooldown);
	skill_2 = skill(20, skill_2_cooldown);
	skill_3 = skill(100, skill_3_cooldown);
	HP = 100;
}

SDL_Rect meo::getpos() { 
	return map_pos;
}

void meo::take_damed(int dame) {
	is_take_dame = 1;
	HP -= dame;
	time_take_dame = timer->getTicks();
}

void meo::draw_hp(SDL_Renderer* render) {
	SDL_Rect tmp = { 10,10,128,34 };
	SDL_RenderCopy(render, textureanimation[69],NULL, &tmp);
	tmp = { 38,10,98,34};
	SDL_RenderCopy(render, textureanimation[70], NULL, &tmp);
	tmp = { 38+ int(float(98) * (float(HP) / 100)),19,98-int(float(98) * (float(HP) / 100)),16 };
	SDL_SetRenderDrawColor(render, 30, 30, 30, 30);
	SDL_RenderFillRect(render,&tmp);
}

void meo::cool_down_skill(SDL_Renderer* render) {
	SDL_Rect tmp = {70,window_h-70,60,60};
	SDL_Rect tmp1 = { 77,window_h - 62,40,40 };
	for (int i = 0; i < 3; i++) {
		SDL_RenderCopy(render, textureanimation[71+i], NULL, &tmp1);
		SDL_SetRenderDrawColor(render, 120, 120, 120, 120);
		if (i == 0)
		{
			SDL_Rect tmp2 = { 77,window_h - 62+ 40*(min(int(timer->getTicks()) - skill_1.get_pre_use(),skill_1_cooldown)) / skill_1_cooldown,40,40 * (max(skill_1_cooldown-(int(timer->getTicks()) - skill_1.get_pre_use()),0)) / skill_1_cooldown };
			SDL_RenderFillRect(render, &tmp2);
		}
		else if (i == 1)
		{
			SDL_Rect tmp2 = { tmp.x+10 ,window_h - 62 + 40 * (min(int(timer->getTicks()) - skill_2.get_pre_use(),skill_2_cooldown)) / skill_2_cooldown,40,40 * (max(skill_2_cooldown - (int(timer->getTicks()) - skill_2.get_pre_use()),0)) / skill_2_cooldown };
			SDL_RenderFillRect(render, &tmp2);
		}
		else{
			SDL_Rect tmp2 = { tmp.x + 10 ,window_h - 62 + 40 * (min(int(timer->getTicks()) - skill_3.get_pre_use(),skill_3_cooldown)) / skill_3_cooldown,40,40 * (max(skill_3_cooldown - (int(timer->getTicks()) - skill_3.get_pre_use()),0)) / skill_3_cooldown };
			SDL_RenderFillRect(render, &tmp2);
		}
		SDL_RenderCopy(render, textureanimation[74], NULL, &tmp);
		tmp.x += 100;
		tmp1.x += 100;
	}
}