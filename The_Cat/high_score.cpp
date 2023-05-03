#include "high_socre.h"
HighScore::HighScore() {
    std::ifstream file("highscores.txt");
    if (file.is_open()) {
        int hard, time;
        while (file >> hard, file >> time) {
            scores.push_back(make_pair(hard, time));
        }
        file.close();
    }
}

void HighScore::addScore(pair <int, int> a) {
    scores.push_back(a);
    sort(scores.begin(), scores.end(), std::greater<pair<int, int>>());
    for (int i = 1; i < scores.size(); i++) {
        if (scores[i].first == scores[i - 1].first) {
            int j = i - 1;
            while (i < scores.size() && scores[i].first == scores[i - 1].first) {
                i++;
            }
            sort(scores.begin() + j, scores.begin() + i);
        }
    }
    if (scores.size() > MAX_SCORES) {
        scores.pop_back();
    }
    saveScores();
}

void HighScore::printScores(SDL_Renderer* render,TTF_Font*font) {
    if (!scores.size()) {
            high.x = 355;
            loadtext(font, high_score, render, "No record found.Start playing to set your first!", brown);
            high.w = (49) * 10;
            SDL_RenderCopy(render, high_score, NULL, &high);
            high.x = 420;
        }
        else {
            high.y -= high.h;
            high.w = (11) * 10;
            loadtext(font, high_score, render,"Hard Level", brown);
            SDL_RenderCopy(render, high_score, NULL, &high);
            high.x += 300;
            high.w = (9) * 10;
            loadtext(font, high_score, render, "Time (s)", brown);
            SDL_RenderCopy(render, high_score, NULL, &high);
            high.y += high.h;
            high.x -= 300;

            for (auto it : scores) {
                s = to_string(it.first);
                loadtext(font, high_score, render, s, brown);
                high.w = (s.size()) * 10;
                SDL_RenderCopy(render, high_score, NULL, &high);
                high.x += 300;
                s = to_string(it.second);
                high.w = (s.size()) * 10;
                loadtext(font, high_score, render, s, brown);
                SDL_RenderCopy(render, high_score, NULL, &high);
                high.y += high.h;
                high.x -= 300;
            }
        }
    cout << scores.size() << endl;
        high = { 420,200,0,30 };
}