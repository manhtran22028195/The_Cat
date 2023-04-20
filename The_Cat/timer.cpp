#include "timer.h"
Uint32 Timer::startTicks = 0;
Uint32 Timer::pausedTicks = 0;
bool Timer::paused = false;
bool Timer::started = false;
Timer::Timer() {
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}
void Timer::start() {
        started = true;
        paused = false;
        startTicks = SDL_GetTicks();
}
void Timer::stop() {
    started = false;
    paused = false;
}

void Timer::pause() {
    if (started && !paused) {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause() {
    if (paused) {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

Uint32 Timer::getTicks() {
    Uint32 time = 0;
    if (started) {
        if (paused) {
            time = pausedTicks;
        }
        else {
            time = SDL_GetTicks() - startTicks;
        }
    }
    return time;
}

bool Timer::isStarted() {
    return started;
}

bool Timer::isPaused() {
    return paused;
}