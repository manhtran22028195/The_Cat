#include "game_event.h"

void spawn(vector <bat> &v_bat,bat &bat,vector <skeleton> &v_skeleton,skeleton &skeleton) {
	if (float(rand()%100)+float(timer->getTicks()/10000) > 40)
	{
        bat.set_pos({ rand() % 2 * 1500 - rand() % 200 - 50,400-20+rand()%10,70,70});
		v_bat.push_back(bat);
	}
    if (float(rand() % 100) + float(timer->getTicks() / 10000) > 40)
    {
        skeleton.set_pos({ rand() % 2* 1500 - rand() % 200-50,513,150,100 });
        v_skeleton.push_back(skeleton);
    }
}
void bat_impact(vector <bat>& v_bat, meo& meo,SDL_Renderer*render) {
    auto it = v_bat.begin();
    while (it!=v_bat.end()) {
        it->get_c_pos = meo.getpos();
        int j = 0;
        while (j < it->bullet.size()) {
            if (check_bullet_collision(meo.get_real_pos(),it->bullet[j], cos(it->angle[j]) * v_bullet, sin(it->angle[j]) * v_bullet))
            {
                if (cooldown(meo.get_time_take_dame(), 1000,timer))
                meo.take_damed(it->get_dame());
                it->bullet.erase(it->bullet.begin() + j);
                it->angle.erase(it->angle.begin() + j);
            }
            else if (check_bullet_collision(meo.getrange(), it->bullet[j], cos(it->angle[j]) * v_bullet, sin(it->angle[j]) * v_bullet))
            {
                it->bullet.erase(it->bullet.begin() + j);
                it->angle.erase(it->angle.begin() + j);
            }
            else
            j++;
        }
        it->move(render);
        if (check_skill_collision(it->getpos(), meo)) {
            it->take_dame();
        }
        if (it->get_i_death() == 30)
        {
            it=v_bat.erase(it);
            meo.score += 10;
            cout << meo.score << endl;
        }
        else {
            it++;
        }
    }
}

void skeleton_impact(vector <skeleton>& v_skeleton, meo& meo, SDL_Renderer*& render) {
    auto it = v_skeleton.begin();
    while(it!=v_skeleton.end())
    {
        it->get_c_pos = meo.getpos();
        it->move(render);
        if (check_collision(meo.get_real_pos(), it->get_range()))
            if (cooldown(meo.get_time_take_dame(), 1000, timer))
                meo.take_damed(it->get_dame());
        int dame = 0;
        dame = check_skill_collision(it->get_real_pos(), meo);
        if (dame)
            it->take_dame(dame);
        if (it->get_i_death() == 15)
        {
            it = v_skeleton.erase(it);
        }
        else
        it++;
    }
}

void boss_impact(boss& boss, meo& meo, SDL_Renderer* render) {
    int i = 0;

    boss.get_c_pos = meo.getpos();

    boss.move(render);

    while (i < boss.bullet1.size()) {
        if (check_skill_collision(boss.bullet1[i], meo)) {
            boss.remove_bullet1(i);
            continue;
        }
        if (check_collision(boss.bullet1[i], meo.get_real_pos())) {
            if (cooldown(meo.get_time_take_dame(), 1000, timer)) {
                meo.take_damed(boss.get_dame());
            }
            boss.remove_bullet1(i);
        }
        i++;
    }
    
    i = 0;
    while (i < boss.bullet2.size()) {
        if (check_skill_collision(boss.bullet2[i], meo)) {
            boss.remove_bullet2(i);
            continue;
        }
        if (check_collision(boss.bullet2[i], meo.get_real_pos())) {
            if (cooldown(meo.get_time_take_dame(), 1000, timer)) {
                meo.take_damed(boss.get_dame());
            }
            boss.remove_bullet2(i);
        }
        i++;
    }

    i = 0;
    while (i < boss.bullet3.size()) {
        if (check_skill_collision(boss.bullet3[i], meo)) {
            boss.bullet3.erase(boss.bullet3.begin() + i);
            continue;
        }
        if (check_collision(boss.bullet3[i], meo.get_real_pos())) {
            if (cooldown(meo.get_time_take_dame(), 1000, timer)) {
                meo.take_damed(boss.get_dame());
            }
            boss.bullet3.erase(boss.bullet3.begin() + i);
        }
        i++;
    }
    boss.take_dame(check_skill_collision(boss.getpos(), meo));
}

int check_skill_collision(SDL_Rect e_pos, meo& meo) {
    if (check_collision(*meo.skill_1.get_range(), e_pos)) {
        return meo.get_skill_1_dame();
    }
    else if (check_collision(*meo.skill_3.get_range(), e_pos)) {
        return meo.get_skill_3_dame();
    }
    if (check_bullet_collision(*meo.skill_2.get_range(), e_pos, 20, 0))
    {
        return meo.get_skill_2_dame();
    }
    return 0;
}