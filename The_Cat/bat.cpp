#include "bat.h"
SDL_Texture** bat::animation = new SDL_Texture * [25];

void bat::set_level(int hard_level) {
	dame += hard_level / 10;
}

void bat::loadanimation(SDL_Renderer* render) {
	for (int i = 0; i < 25; i++)
		loadtexture(render, animation[i], image[i]);
}

void bat::move(SDL_Renderer*render) {
	//e pos
	get_delta_c_pos();
	if (is_death) {
		death(render);
		e_move(get_c_pos, delta_c_pos, pos, 0,200);
	}
	else {
		e_move(get_c_pos, delta_c_pos, pos, step / 2,200);
		
		if (cooldown(time, 5000, timer) || attacking) { attack(render); time = timer->getTicks(); }
		else fly(render);
		for (int i = 0; i < bullet.size(); i++)
		{
			bullet[i].x += cos(angle[i]) * v_bullet;
			bullet[i].y += sin(angle[i]) * v_bullet;
			if (get_c_pos.x > 570 && get_c_pos.x < map_w - 630) {
				bullet[i].x += delta_c_pos;
			}
			//xoa dan
			if (bullet[i].x > 1500 || bullet[i].x < -500 || bullet[i].y>800 || bullet[i].y < -100)
			{
				bullet.erase(bullet.begin() + i);
				angle.erase(angle.begin() + i);
			}
			else
			{
				SDL_RenderCopy(render, animation[24], NULL, &bullet[i]);
			}
		}
	}
}

void bat::fly(SDL_Renderer* render) {
	if (!is_right())
		SDL_RenderCopyEx(render, animation[i_fly + 11], NULL, &pos, 180, 0, SDL_FLIP_VERTICAL);
	else
		SDL_RenderCopy(render, animation[i_fly + 11], NULL, &pos);

	i_fly=++i_fly%6;
}

bool bat::is_right() {
	if (get_c_pos.x > 570 && get_c_pos.x < map_w - 630) {
		return (pos.x + pos.w / 2 > window_w / 2);
	}
	else if (get_c_pos.x <= 570)
		return (pos.x + pos.w / 2 > get_c_pos.x);
	else
		return pos.x + pos.w / 2 > get_c_pos.x - (map_w - 1200);
}

void bat::attack(SDL_Renderer* render) {

	if (!is_right())
		SDL_RenderCopyEx(render, animation[i_attack], NULL, &pos, 180, 0, SDL_FLIP_VERTICAL);
	else
		SDL_RenderCopy(render, animation[i_attack], NULL, &pos);

	if (i_attack == 1)
	{
		if (get_c_pos.x > 570 && get_c_pos.x < map_w - 630)
		{
			angle.push_back(atan2(-pos.y + get_c_pos.y + 20, -pos.x + 600));
		}
		else if(get_c_pos.x <= 570)
			angle.push_back(atan2(-pos.y + (get_c_pos.y+20), -pos.x + (get_c_pos.x+10)));
		else
			angle.push_back(atan2(-pos.y + (get_c_pos.y + 20), -pos.x + (get_c_pos.x + 10) - (map_w - 1200)));

		skill.x = pos.x + 10; skill.y = pos.y + 20;
		bullet.push_back(skill);
	}

	i_attack++;
	if (i_attack == 7){
		i_attack = 0;
		attacking = 0;
	}
	else
	attacking = 1;
}

void bat::death(SDL_Renderer* render) {
	if (!is_right())
		SDL_RenderCopyEx(render, animation[i_death/5 + 17], NULL, &pos, 180, 0, SDL_FLIP_VERTICAL);
	else
		SDL_RenderCopy(render, animation[i_death/5 + 17], NULL, &pos);
	if(i_death<30)
	i_death++;
	get_i_death();
}

void bat::get_delta_c_pos() {
	delta_c_pos = pre_c_pos.x - get_c_pos.x;
	pre_c_pos = get_c_pos;
}