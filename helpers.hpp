#ifndef HELPER_HPP
#define HELPER_HPP

#include <unistd.h>  
#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <regex>
#include <vector>
 
#define WINDOW_MAX_HEIGHT 100 // change it later
#define WINDOW_MIN_HEIGHT 10 // change it later
#define WINDOW_MAX_WIDTH 200 // change it later
#define WINDOW_MIN_WIDTH 10 // change it later

void        getArgs(int ac, char **av);
extern uint8_t     g_gameMode;
extern int         g_windowHeight;
extern int         g_windowWidth;
#endif 