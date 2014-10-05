
#include "Util/String.h"
#include "Util/ArrayList.h"
#include "Util/Thread.h"
#include "forwards.h"

#pragma once

namespace GameEngine
{
	class BatchLoader
	{
	private:
		static ArrayList<String> Images;
		static ArrayList<String> Fonts;
		
		static int totalAmount;
		
	public:
		static void addImage(String n);
		
		static void addFont(String n);
		
		static void loadAll();
	};
	
	class LoadThread : public Thread
	{
	private:
		Application*app;
		
	public:
		LoadThread(Application*app);
		~LoadThread();
		
		virtual void run();
	};
}