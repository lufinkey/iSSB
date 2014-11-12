
#ifdef _WIN32
#include <Windows.h>
#endif

void GameEngine_setDLLDirectory(const char* dir)
{
#ifdef _WIN32
	SetDllDirectoryA(dir);
#endif
}