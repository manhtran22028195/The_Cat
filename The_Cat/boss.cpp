#include "boss.h"

void boss::set_level(int hard_level) {
	default_HP += hard_level * 10;
	HP += hard_level * 10;
	dame += hard_level /2;
}

void boss::loadanimation(SDL_Renderer* render){
	for (int i = 0; i <70; i++)
		loadtexture(render, animation[i], image[i]);
}
void boss::move(SDL_Renderer* render) {
	get_delta_c_pos();
	if (cooldown(time, 4000, timer) || attacking1 || attacking2 || attacking3) {
		if (!attacking1 && !attacking2 && !attacking3) {
			int i = rand() % 3;
			if (i == 0) {
				attacking1 = 1;
			}
			if (i == 1) {
				attacking2 = 1;
			}
			if (i == 2) {
				attacking3 = 1;
			}
		}
		if (attacking1) { attack1(render); }
		else if (attacking2) { attack2(render);}
		else if (attacking3) { attack3(render); }
		e_move(get_c_pos, delta_c_pos, pos, 0, 50);
	}
	else {
		boss::fly(render);
		e_move(get_c_pos, delta_c_pos, pos, 7, 200);
	}
	if (bullet2.size())
		bullet2_move(render);
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
	SDL_Rect poss = { pos.x + 160,pos.y + 160,pos.w - 300,pos.h - 230 };
	SDL_RenderDrawRect(render, &poss);
	draw_hp(render);
}
void boss::fly(SDL_Renderer* render) {
	if (!is_right())
		SDL_RenderCopy(render, animation[i_fly/2 + 4], NULL, &pos);
	else
		SDL_RenderCopyEx(render, animation[i_fly/2 + 4], NULL, &pos, 180, 0, SDL_FLIP_VERTICAL);
	i_fly++;
	if (i_fly == 30)
		i_fly = 0;
}

void boss::attack1(SDL_Renderer* render) {
	attacking1 = 1;
	if (i_attack1 == 0) {
		attack1_time = timer->getTicks();
	}
	if ((timer->getTicks() - attack1_time) / 30==4)
	{
		center = { (pos.x + pos.w / 2 - 20), (pos.y + pos.h / 2) };
		spawn_square();
		angle_attack1 = get_angle(center);
	}
	else if (!bullet1.size() && (timer->getTicks() - attack1_time) / 30 > 5)
	{
		center = { (pos.x + pos.w / 2 - 20), (pos.y + pos.h / 2) };
		spawn_triangle();
		angle_attack1 = get_angle(center);
		attack1_time = -100000;
	}
	else if (bullet1.size() && (center.x > 1500 || center.x < -500 || center.y>800 || center.y < -100)) {
		bullet1_clear();
	}
	if (!is_right())
		SDL_RenderCopy(render, animation[i_attack1 / 3 + 33], NULL, &pos);
	else
		SDL_RenderCopyEx(render, animation[i_attack1 / 3 + 33], NULL, &pos, 180, 0, SDL_FLIP_VERTICAL);
	if (i_attack1 < 11)
		i_attack1++;
	if (bullet1.size()) {
		int i = 0;
		if (get_c_pos.x > 570 && get_c_pos.x < map_w - 630) {
			center.x += delta_c_pos;
		}
		center = { center.x += 8 * cos(angle_attack1),center.y += 8 * sin(angle_attack1) };
		while (i < bullet1.size()) {
			angle1[i] += M_PI / 40;
			bullet1[i] = { center.x + int(cos(angle1[i]) * r[i]), center.y + int(sin(angle1[i]) * r[i]), 40, 40 };
			SDL_RenderCopy(render, animation[69], NULL, &bullet1[i]);
			i++;
		}
	}
	if (timer->getTicks()-attack1_time>100000)
	{
		if (!bullet1.size())
		{
			attacking1 = 0;
			time = timer->getTicks();
			i_attack1 = 0;
		}
	}
}
void boss::spawn_square() {
	//tao khung
	for (int i = 0; i < 4; i++)
	{
		angle1.push_back(((2 * M_PI) / 4) * i);
		bullet1.push_back({ (pos.x + pos.w / 2 - 20) + int(cos(angle1[i]) * (r_attack1)), (pos.y + pos.h / 2) + int(sin(angle1[i]) * (r_attack1)), 40, 40 });
		r.push_back((r_attack1));
	}
	//tao dan ben trong khung
	vector <SDL_Point> tmp;
	int n = bullet1.size();
	for (int i = 0; i < 4; i++)
		for (int j = 1; j < 3; j++) {
			if (i == 3) {
				tmp.push_back({ bullet1[n - 4].x * (j) / 3 + bullet1[n - 1].x * (3 - j) / 3,bullet1[n - 4].y * (j) / 3 + bullet1[n - 1].y * (3 - j) / 3 });
			}
			else
				tmp.push_back({ bullet1[n - i - 1].x * (j) / 3 + bullet1[n - i - 2].x * (3 - j) / 3,bullet1[n - i - 1].y * (j) / 3 + bullet1[n - i - 2].y * (3 - j) / 3 });
		}
	//di chuyen dan
	auto it = tmp.begin();
	while (it != tmp.end()) {
		angle1.push_back(atan2(-center.y + it->y, -center.x + it->x));
		bullet1.push_back({ (pos.x + pos.w / 2 - 20) + it->x, (pos.y + pos.h / 2) + it->y, 40, 40 });
		r.push_back(sqrt((-center.y + it->y) * (-center.y + it->y) + (-center.x + it->x) * (-center.x + it->x)));
		it++;
	}
}

void boss::spawn_triangle() {
	bullet1_clear();
	vector <SDL_Point> tmp;
	int n = bullet1.size();
	for (int i = 0; i < 3; i++)
	{
			angle1.push_back(((2 * M_PI) / 3) * i);
			bullet1.push_back({ (pos.x + pos.w / 2 - 20) + int(cos(angle1[i]) * (r_attack1)), (pos.y + pos.h / 2) + int(sin(angle1[i]) * (r_attack1)), 40, 40 });
			r.push_back((r_attack1));
	}
		n = bullet1.size();
	for (int i = 0; i < 3; i++) {
		for (int j = 1; j < 3; j++) {
			if (i == 2) {
				tmp.push_back({bullet1[n - 3].x*(j) / 3 + bullet1[n - 1].x * (3 - j) / 3,bullet1[n - 3].y*(j) / 3 + bullet1[n - 1].y * (3-j) / 3 });
				}
			else
				tmp.push_back({bullet1[n - i - 1].x* (j) / 3 + bullet1[n - i - 2].x * (3 - j) / 3,bullet1[n - i - 1].y*(j) / 3 + bullet1[n - i - 2].y * (3-j) / 3 });
			}
		}
	auto it = tmp.begin();
	while (it != tmp.end()) {
		angle1.push_back(atan2(-center.y + it->y, -center.x + it->x));
		bullet1.push_back({ (pos.x + pos.w / 2 - 20) + it->x, (pos.y + pos.h / 2) + it->y, 40, 40 });
		r.push_back(sqrt((-center.y + it->y) * (-center.y + it->y) + (-center.x + it->x) * (-center.x + it->x)));
		it++;
	}
}
void boss::bullet1_clear() {
	bullet1.clear();
	angle1.clear();
	r.clear();
}

void boss::remove_bullet1(int i) {
	bullet1.erase(bullet1.begin() + i);
	angle1.erase(angle1.begin() + i);
	r.erase(r.begin() + i);
}

void boss::attack2(SDL_Renderer* render) {
	
	if (i_attack2 == 0) {
		attack2_time = timer->getTicks();attacking2 = 1;
	}
	if (!is_right())
		SDL_RenderCopy(render, animation[i_attack2 / 2 + 33], NULL, &pos);
	else
		SDL_RenderCopyEx(render, animation[i_attack2 / 2 + 33], NULL, &pos, 180, 0, SDL_FLIP_VERTICAL);
	if (i_attack2 < 60)
		i_attack2++;
	else
		i_attack2 = 45;
	//spawn dan
	if (cooldown(attack2_time, 70, timer))
		for (int i = 0; i < 20; i++)
		{
			angle_attack2.push_back(((2 * M_PI) / 20) * i + turn_attack);
			angle2.push_back(((2 * M_PI) / 20) * i);
			bullet2.push_back({ (pos.x + pos.w / 2 - 20) + int(cos(angle2.back()) * (pos.w / 2)), (pos.y + pos.h / 2) + int(sin(angle2.back()) * (pos.h / 2)), 40, 40 });
			attack2_time = timer->getTicks();
		}
	turn_attack += M_PI / 20;
	if (turn_attack > 6 * M_PI) {
		turn_attack = 0;
		attacking2 = 0;
		time = timer->getTicks();
		i_attack2 = 0;
	}
	int i = 0;
}

void boss::bullet2_move(SDL_Renderer*render) {
	int i = 0;
	while (i < angle2.size()) {
		bullet2[i].x += sin(angle2[i]) * sin(angle_attack2[i]) * 10; bullet2[i].y -= cos(angle2[i]) * sin(angle_attack2[i]) * 10;
		bullet2[i].x += cos(angle2[i]) * 15; bullet2[i].y += sin(angle2[i]) * 15;
		if (get_c_pos.x > 570 && get_c_pos.x < map_w - 630) {
			bullet2[i].x += delta_c_pos;
		}
		SDL_RenderCopy(render, animation[69], NULL, &bullet2[i]);
		angle_attack2[i] += M_PI / 5;
		i++;
	}
}

void boss::remove_bullet2(int i) {
	bullet2.erase(bullet2.begin() + i);
	angle2.erase(angle2.begin() + i);
	angle_attack2.erase(angle_attack2.begin() + i);
}
void boss::attack3(SDL_Renderer* render) {
	if (i_attack3 == 0) {
		attack3_time = timer->getTicks();
		attacking3 = 1;
		spawn_time = attack3_time;
	}
	if (!is_right())
		SDL_RenderCopy(render, animation[i_attack3 / 3 + 33], NULL, &pos);
	else
		SDL_RenderCopyEx(render, animation[i_attack3 / 3 + 33], NULL, &pos, 180, 0, SDL_FLIP_VERTICAL);
	if (i_attack3 < 11)
		i_attack3++;
	///spawn dan
	if(timer->getTicks()-attack3_time<7000)
	if (cooldown(spawn_time, 2000, timer))
	{
		{
			bullet3.push_back({ (pos.x + pos.w / 2 - 20) , (pos.y + pos.h / 2), 40, 40 });
			spawn_time = timer->getTicks();
		}
	}
	int i = 0;
	double angle;
	while (i < bullet3.size()) {
		angle = get_angle({ bullet3[i].x+10, bullet3[i].y });
		bullet3[i].x += cos(angle) * 15+delta_c_pos; bullet3[i].y += sin(angle) * 15;
		SDL_RenderCopy(render, animation[69], NULL, &bullet3[i]);
		i++;
	}
	if (!bullet3.size()&&timer->getTicks() - attack3_time > 7000)
	{
			attacking3 = 0;
			i_attack3 = 0;
			time = timer->getTicks();
	}
}
void boss::get_delta_c_pos() {
	delta_c_pos = pre_c_pos.x - get_c_pos.x;
	pre_c_pos = get_c_pos;
}

double boss::get_angle(SDL_Point pos) {
	if (get_c_pos.x > 570 && get_c_pos.x < map_w - 630)
	{
		return (atan2(-pos.y + get_c_pos.y + 20, -pos.x + 600));
	}
	else if (get_c_pos.x <= 570)
		return (atan2(-pos.y + (get_c_pos.y + 20), -pos.x + (get_c_pos.x + 10)));
	else
		return (atan2(-pos.y + get_c_pos.y, -pos.x + get_c_pos.x - (map_w - 1200)));
}
bool boss::is_right() {
	if (get_c_pos.x > 570 && get_c_pos.x < map_w - 630) {
		return (pos.x + pos.w / 2 > window_w / 2);
	}
	else if (get_c_pos.x <= 570)
		return (pos.x + pos.w / 2 > get_c_pos.x);
	else
		return pos.x + pos.w / 2 > get_c_pos.x - (map_w - 1200);
}
void boss::draw_hp(SDL_Renderer*render) {
	SDL_Rect tmp = { pos.x + pos.w / 2-100,pos.y + 50,HP *200 / default_HP,30 };
	SDL_SetRenderDrawColor(render, 255, 0, 0, 0);
	SDL_RenderFillRect(render,&tmp);
}

void boss::reset() {
	i_fly = 0, i_attack1 = 0, i_attack2 = 0, i_attack3 = 0, i_idle = 0, i_death = 0;
	bullet1.clear();
	angle1.clear();
	r.clear();
	bullet2.clear();
	angle2.clear();
	angle_attack2.clear();
	bullet3.clear();
	HP = default_HP;
	attacking3 = 0;
	attack3_time = 0;
	spawn_time = 0;
	is_death = 0;
	attacking2 = 0;
	attack2_time = 0;
	attacking1 = 0;
	attack1_time = 0;
	time = 10000;
}