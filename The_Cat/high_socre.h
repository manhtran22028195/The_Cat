#pragma once
#include "mainfunction.h"

class HighScore {
public:
    HighScore();

    void addScore(pair <int, int> a);

    void printScores(SDL_Renderer* render,TTF_Font*font);
private:
    const int MAX_SCORES = 10;
    vector<pair<int,int>> scores;
    string s;
    SDL_Texture* high_score;
    SDL_Rect high = { 0,0,0,30 };

    void saveScores() {
        std::ofstream file("highscores.txt");
        if (file.is_open()) {
            for (int i = 0; i < scores.size(); i++) {
                file << scores[i].first<< " "<< scores[i].second << "\n";
            }
            file.close();
        }
    }
};