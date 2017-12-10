
#pragma once

#include "SDL_thread.h"

namespace GameEngine
{
	class Thread
	{
		friend int ThreadHandler(void*);
	private:
		SDL_Thread*thread;
		bool alive;
		
	public:
		Thread();
		virtual ~Thread();
		
		virtual void run();
		
		void start();
		void join();
		
		bool isAlive();
		
		static void sleep(long millis);
	};
}
