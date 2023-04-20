#include "skeleton.h"
SDL_Texture** skeleton::animation= new SDL_Texture * [65];

skeleton::~skeleton() {}

void skeleton::set_level(int hard_level) {
	hp += hard_level*4;
	dame += hard_level / 5;
}

void skeleton::loadanimation(SDL_Renderer* render) {
	for (int i = 0; i < 65; i++)
		loadtexture(render, animation[i], image[i]);
}
void skeleton::move(SDL_Renderer* render) {
	get_delta_c_pos();
	if (hp <= 0) { death(render); e_move(get_c_pos, delta_c_pos, pos, 0, 0); }
	else if (is_take_dame) { takedame(render); attacking = 0; i_attack = 0; range.y = 0; e_move(get_c_pos, delta_c_pos, pos, 0,40);}
	else if ((cooldown(time, 3000, timer) && (abs(real_pos.x + real_pos.w / 2 - get_c_real_pos().x - get_c_real_pos().w / 4) < 100)) || attacking)
	{
		range.y = 0;
		attack(render);
		time = timer->getTicks();
		e_move(get_c_pos, delta_c_pos, pos, 0, 50);
	}
	else {
		e_move(get_c_pos, delta_c_pos, pos, 3, 50);
		if (abs(real_pos.x + real_pos.w / 2 - get_c_real_pos().x - get_c_real_pos().w / 4) < 70)
			idle(render);
		else
			walk(render);
	}
	
	real_pos = { pos.x + 50,pos.y + 30,pos.h - 60,pos.w - 80 };
	draw_hp(render);
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
	SDL_RenderDrawRect(render, &range);
}

void skeleton::death(SDL_Renderer* render){
	if (is_right())
		SDL_RenderCopyEx(render, animation[i_death+18], NULL, &pos, 180, 0, SDL_FLIP_VERTICAL);
	else
		SDL_RenderCopy(render, animation  [i_death+18], NULL, &pos);
	if(i_death<15)
	i_death++;
}		

void skeleton::attack(SDL_Renderer* render){
	attacking = 1;
	if(i_attack==0)
		right=is_right();

	if (right)
		SDL_RenderCopyEx(render, animation[i_attack/2], &pos_s, &pos, 180, 0, SDL_FLIP_VERTICAL);
	else
		SDL_RenderCopy(render, animation[i_attack/2], &pos_s, &pos);
	i_attack++;
	if (i_attack == 36)
	{
		i_attack = 0;
		attacking = 0;
		range.x = 0;
		range.y = 0;
	}
	else if(i_attack==18) {
		range_update();
	}
}

void skeleton::walk(SDL_Renderer* render){
	if (is_right())
		SDL_RenderCopyEx(render, animation[i_walk/2 + 52], NULL, &pos, 180, 0, SDL_FLIP_VERTICAL);
	else
		SDL_RenderCopy(render, animation[i_walk/2+52], NULL, &pos);
	i_walk++;
	if (i_walk == 26)
	{
		i_walk = 0;
	}
}

void skeleton::takedame(SDL_Renderer* render) {
	is_take_dame = 1;
	if (is_right())
		SDL_RenderCopyEx(render, animation[i_takedame / 2 + 33], NULL, &pos, 180, 0, SDL_FLIP_VERTICAL);
	else
		SDL_RenderCopy(render, animation[i_takedame / 2 + 33], NULL, &pos);
	i_takedame++;
	if (i_takedame == 16)
	{i_takedame = 0;
	is_take_dame = 0;
	}
}

void skeleton::idle(SDL_Renderer*render) {
	if (is_right())
		SDL_RenderCopyEx(render, animation[i_idle/3+41], NULL, &pos, 180, 0, SDL_FLIP_VERTICAL);
	else
		SDL_RenderCopy(render, animation[i_idle/3 + 41], NULL, &pos);

	i_idle++;
	if (i_idle == 33)
		i_idle = 0;
}

bool skeleton::is_right() {
	if (get_c_pos.x > 570 && get_c_pos.x < map_w - 630) {
		return (pos.x + pos.w / 2 > window_w / 2);
	}
	else if (get_c_pos.x <= 570)
		return (pos.x + pos.w / 2 > get_c_pos.x);
	else
		return pos.x + pos.w / 2 > get_c_pos.x - (map_w - 1200);
}
void skeleton::get_delta_c_pos() {
	delta_c_pos = pre_c_pos.x - get_c_pos.x;
	pre_c_pos = get_c_pos;
}

void skeleton::range_update() {
	if (!right)
		range = { real_pos.x + real_pos.w / 2,real_pos.y, 90,50};
	else
		range = {real_pos.x + real_pos.w / 2 - 70, real_pos.y,  90,50 };
}
SDL_Rect skeleton::get_c_real_pos() {
	if (get_c_pos.x > 570 && get_c_pos.x < map_w - 630)
	{
		return { 600,550,40,50 };
	}
	else if (get_c_pos.x <= 570)
	{
		return { get_c_pos.x,get_c_pos.y , 40, 50 };
	}
	else
	{
		return { get_c_pos.x, get_c_pos.y - (map_w - 1200),40, 50 };
	}
}

SDL_Rect skeleton::get_range() {
	return range;
}

void skeleton::draw_hp(SDL_Renderer* render) {
	SDL_Rect H;
	if (!is_right())
		H = { pos.x + pos.w / 2 - 35, pos.y + 25, 1, 3 };
	else
		H = { pos.x + pos.w / 2 - 10, pos.y + 25, 1, 3 };
	SDL_SetRenderDrawColor(render, 255, 0, 0, 0);
	for (int i = 0; i < hp; i+=10) {
		SDL_RenderFillRect(render, &H);
		H.x += H.w;
	}
}