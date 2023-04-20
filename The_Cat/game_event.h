#pragma once
#include "meo.h"
#include "bat.h"
#include "skeleton.h"
#include "boss.h"
void spawn(vector <bat> &v_bat ,bat &bat,vector<skeleton> &v_skeleton, skeleton &skeleton);

void bat_impact(vector <bat>& v_bat,meo &meo,SDL_Renderer*render);

void skeleton_impact(vector <skeleton>& v_skeleton, meo& meo, SDL_Renderer*& render);

void boss_impact(boss& boss, meo& meo,SDL_Renderer*render);

int check_skill_collision(SDL_Rect e_pos,meo &meo);