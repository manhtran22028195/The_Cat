#pragma once
#include <SDL.h>
#include <iostream>
class Timer {
public:
    Timer();
    static void start();
    static void stop();
    static void pause();
    static void unpause();
    static Uint32 getTicks();
    static bool isStarted();
    static bool isPaused();
private:
    static Uint32 startTicks;
    static Uint32 pausedTicks;
    static bool paused;
    static bool started;
};