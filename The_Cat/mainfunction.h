#pragma once

#ifndef funtion
#define funtion
#include "resource.h"

void init(SDL_Window*& window, SDL_Renderer*& render,TTF_Font*& font);

void load_icon(SDL_Window* window, string path);

void loadtexture(SDL_Renderer* render, SDL_Texture*& texture, string path);

void loadtext(TTF_Font*font, SDL_Texture*& texture,SDL_Renderer*render, string s,SDL_Color color);

void quit(SDL_Window* window, SDL_Renderer* render);

bool check_collision(SDL_Rect a, SDL_Rect b);

bool check_bullet_collision(SDL_Rect k, SDL_Rect h,float step_x,float step_y);

bool cooldown(int previuos_time, unsigned int delay_time,Timer *&time);

void e_move(SDL_Rect get_c_pos,int delta_c_pos,SDL_Rect &e_pos,int vel_x,int distant);

void pause_screen(SDL_Renderer* render, SDL_Texture*& texture);
#endif // !funtion