#ifndef SYS_HPP
#define SYS_HPP

#include "SoundEngine.hpp"

#define SE_APPLE "audio/apple.wav"
#define SE_BGM "audio/bgm.wav"
#define SE_GAMEOVER "audio/gameover.wav"
#define SE_WIN "audio/win.wav"
#define SE_MENU "audio/Switch1.wav"
#define PATHLIBA "lib/renderA.dylib"
#define PATHLIBB "lib/renderB.dylib"
#define PATHLIBC "lib/renderC.dylib"

#define WINDOW_MAX_HEIGHT 40 
#define WINDOW_MIN_HEIGHT 24 
#define WINDOW_MAX_WIDTH 50 
#define WINDOW_MIN_WIDTH 32
#define WIN_POINT 10

extern int          g_gameMode;
extern int          g_windowRows;
extern int          g_windowCols;
extern SoundEngine *g_soundEngine;
#endif