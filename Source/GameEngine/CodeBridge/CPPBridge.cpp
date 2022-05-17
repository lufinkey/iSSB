
#define _CRT_SECURE_NO_WARNINGS

#include "CPPBridge.h"
#include "../Application.h"
#include "SDL_ext.h"
#include <string>
#include <cstdlib>
#include <iostream>

#ifdef _WIN32
	#include <windows.h>
	#include <stdint.h>
#elif __APPLE__
	#include <sys/time.h>
#else
	#include <time.h>
#endif

#ifdef __ANDROID__
	#include <android/log.h>
#endif

namespace GameEngine
{
	void private_updateAppEvents(void)
	{
		GameEngine::Application::game->updateEvents();
	}
}

void updateAppEvents(void)
{
	GameEngine::private_updateAppEvents();
}

void showMessage(const char*title, const char*message)
{
	GameEngine::Application::showMessage(title,message);
}

#if defined(_WIN32)
	int gettimeofday(struct timeval * tp, struct timezone * tzp)
	{
		// Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
		static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

		SYSTEMTIME  system_time;
		FILETIME    file_time;
		uint64_t    time;

		GetSystemTime( &system_time );
		SystemTimeToFileTime( &system_time, &file_time );
		time =  ((uint64_t)file_time.dwLowDateTime )      ;
		time += ((uint64_t)file_time.dwHighDateTime) << 32;

		tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
		tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
		return 0;
	}
#endif

long getUptimeMillis(void)
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	//return (long)((long)((long)tv.tv_sec*1000) + (long)((long)tv.tv_usec/1000));
	long elapsed = (long)(tv.tv_sec)*1000 + (long)tv.tv_usec/1000;
	return elapsed;
}



std::string GameEngine_charToUrlEncoding(const char *s, const char *tb) {
	std::string enc;
	for (; *s; s++) {
		char out[10];
		if (tb[*s]) {
			sprintf(out, "%c", tb[*s]);
		}
		else {
			sprintf(out, "%%%02X", *s);
		}
		enc += out;
	}
	return enc;
}

std::string GameEngine_urlencode(const char* str) {
	int length = strlen(str)+1;
	char* enc = new char[length * 3];

	char rfc3986[256] = {0};
	char html5[256] = {0};

	int i;
	for (i = 0; i < 256; i++) {
		rfc3986[i] = isalnum(i)||i == '~'||i == '-'||i == '.'||i == '_'
					 ? i : 0;
		html5[i] = isalnum(i)||i == '*'||i == '-'||i == '.'||i == '_'
				   ? i : (i == ' ') ? '+' : 0;
	}

	return GameEngine_charToUrlEncoding(str, rfc3986);
}



#ifndef __APPLE__

void GameEngine_Log(const char* text)
{
	#ifdef __ANDROID__
		__android_log_print(ANDROID_LOG_INFO, "GameEngine", "%s", text);
	#else
		std::cout << text;
	#endif
}

#endif

#if !defined(__APPLE__) || (TARGET_OS_IPHONE != 1 && TARGET_IPHONE_SIMULATOR != 1)

void SDL_ShowSimpleMessageBoxFixed(const char*title, const char*message)
{
	SDL_Window *window = GameEngine::Application::getWindow();
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title, message, window);
}

int SDL_ShowMessageBoxFixed(const char*title, const char*message, const char**options, int numOptions)
{
	SDL_Window* window = GameEngine::Application::getWindow();
	SDL_MessageBoxButtonData*buttons = new SDL_MessageBoxButtonData[numOptions];
	for(int i=0; i<numOptions; i++)
	{
		SDL_MessageBoxButtonData button = {0, i, (char*)options[i]};
		buttons[i] = button;
	}
	SDL_MessageBoxData messageBoxData = {SDL_MESSAGEBOX_INFORMATION, window, (const char*)title, (const char*)message, numOptions, buttons, NULL};
	int buttonid = 0;
	SDL_ShowMessageBox(&messageBoxData, &buttonid);
	delete[] buttons;
	return buttonid;
}

void openURL(const char* url, SDL_Window* window)
{
	#ifdef __ANDROID__
		std::string command = (std::string)"./adb shell am start -a android.intent.action.VIEW -d \""+url+"\"";
		std::system(command.c_str());
	#else
		// TODO open a URL
	#endif
}

void writeEmail(SDL_Window*window, const char* recipient, const char* subject, const char* body)
{
	#ifdef __ANDROID__
		std::string url = (std::string)"mailto:" + recipient + "?subject=" + GameEngine_urlencode(subject) + "&body=" + GameEngine_urlencode(body);
		std::string command = (std::string)"./adb shell am start -a android.intent.action.VIEW -d " + url;
		std::system(command.c_str());
	#else
		// TODO open email window
	#endif
}

std::string getDeviceModel()
{
	// TODO find device model
	return "Unknown";
}

std::string getDeviceName()
{
	// TODO find device name
	return "Unknown";
}

// iCade stubs
void iCade_enable(bool toggle, SDL_Window* window) {}
bool iCade_enabled() { return false; }
void iCade_setStateChangedCallback(iCadeEventCallback callback) {}
void iCade_setButtonDownCallback(iCadeEventCallback callback) {}
void iCade_setButtonUpCallback(iCadeEventCallback callback) {}

#endif
