
#include "Thread.h"
#include "SDL_timer.h"

namespace GameEngine
{
	int ThreadHandler(void*data)
	{
		Thread*thread = (Thread*)data;
		thread->run();
		thread->alive = false;
		return 0;
	}
	
	Thread::Thread()
	{
		alive = false;
		thread = NULL;
	}
	
	Thread::~Thread()
	{
		if(thread!=NULL)
		{
			SDL_WaitThread(thread, NULL);
			thread = NULL;
		}
	}
	
	void Thread::run()
	{
		//Open for implementation
	}
	
	void Thread::start()
	{
		if(!alive)
		{
			if(thread!=NULL)
			{
				SDL_WaitThread(thread, NULL);
				thread = NULL;
			}
			
			alive = true;
			
			thread = SDL_CreateThread(ThreadHandler, "GameEngine::Thread", this);
		}
	}
	
	void Thread::join()
	{
		if(alive)
		{
			SDL_WaitThread(thread, NULL);
			thread = NULL;
		}
	}
	
	void Thread::sleep(long millis)
	{
		SDL_Delay(millis);
	}
	
	bool Thread::isAlive()
	{
		return alive;
	}
}