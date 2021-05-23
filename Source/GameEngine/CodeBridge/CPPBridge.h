
#pragma once

#include <SDL.h>
#include <string>
#include "iCadeControllerReceiver.h"

extern void openURL(const char*url, SDL_Window* window=NULL);
extern void writeEmail(SDL_Window* window, const char* recipient, const char* subject, const char* body);

extern std::string getDeviceModel();
extern std::string getDeviceName();

extern void iCade_enable(bool toggle, SDL_Window*window);
extern bool iCade_enabled();
extern void iCade_setStateChangedCallback(iCadeEventCallback callback);
extern void iCade_setButtonDownCallback(iCadeEventCallback callback);
extern void iCade_setButtonUpCallback(iCadeEventCallback callback);

extern void GameEngine_Log(const char* text);
extern void GameEngine_loadLibs();

extern long getUptimeMillis(void);

extern void updateAppEvents(void);
extern void showMessage(const char* title, const char* message);

extern void GameEngine_setDLLDirectory(const char* dir);
