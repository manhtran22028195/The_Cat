#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <iterator>
#include <cctype>
#include <cstdlib>
#include <time.h>
#include <iomanip>
#include <math.h>
#include <SDL.h>
#include <stdlib.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "timer.h"
using namespace std;
struct newrect
{
	float x, y, w, h;
};

static const int  step = 10, ground = 420, background_h = 700, background_w = 934, window_w = 1200, window_h = 700, maxh = 270, map_w = 4670, v_bullet = 10, max_bats = 10, button_w = 44, button_h = 48
,meo_HP=100,meo_skill_1_dame=10, meo_skill_2_dame = 60, meo_skill_3_dame = 80,skeleton_HP=400,skeleton_dame=10,bat_dame=10,boss_hp=4000,boss_dame=20;

static SDL_Event e;

static Timer* timer = new Timer;

static SDL_Color white = { 255,255,255 }, black = { 0,0,0 }, brown = { 140,78,0 };

static SDL_Window* window;

static TTF_Font* font;

static SDL_Renderer* render;
