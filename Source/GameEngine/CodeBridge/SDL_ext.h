
#pragma once

#include <SDL.h>

extern void SDL_ShowSimpleMessageBoxFixed(const char*title, const char*message);
extern int SDL_ShowMessageBoxFixed(const char*title, const char*message, const char**options, int numOptions);
