#ifndef SYS_HPP
#define SYS_HPP

#include "SoundEngine.hpp"

#define SE_APPLE "audio/apple.wav"
#define SE_BGM "audio/bgm.wav"
#define SE_GAMEOVER "audio/gameover.wav"
#define SE_WIN "audio/win.wav"
#define WINDOW_MAX_HEIGHT 100 // change it later
#define WINDOW_MIN_HEIGHT 10 // change it later
#define WINDOW_MAX_WIDTH 200 // change it later
#define WINDOW_MIN_WIDTH 10 // change it later'

extern int          g_gameMode;
extern int          g_windowHeight;
extern int          g_windowWidth;
extern SoundEngine *g_soundEngine;
#endif