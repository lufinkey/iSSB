
#include "SDL.h"
#include "iCadeControllerReceiver.h"

#pragma once

extern void GameEngine_init();

extern void openURL(const char*url, SDL_Window*window=NULL);
extern void writeEmail(SDL_Window*window, const char*recipient, const char*subject, const char*body);

extern void getDeviceModel(char*deviceString);
extern void getDeviceName(char*nameString);

extern void iCade_enable(bool toggle, SDL_Window*window);
extern bool iCade_enabled();
extern void iCade_setStateChangedCallback(iCadeEventCallback callback);
extern void iCade_setButtonDownCallback(iCadeEventCallback callback);
extern void iCade_setButtonUpCallback(iCadeEventCallback callback);

extern void SDL_ShowSimpleMessageBoxFixed(const char*title, const char*message);
extern int SDL_ShowMessageBoxFixed(const char*title, const char*message, const char**options, int numOptions);

extern void GameEngine_Log(char*text);

extern long getUptimeMillis(void);
