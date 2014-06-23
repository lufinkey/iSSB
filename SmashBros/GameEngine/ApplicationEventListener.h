
#pragma once

namespace GameEngine
{
	class ApplicationEventListener
	{
	public:
		virtual void onAppWillEnterBackground();
		virtual void onAppDidEnterBackground();
		virtual void onAppWillEnterForeground();
		virtual void onAppDidEnterForeground();
		virtual void onAppTerminating();
		virtual void onLowMemory();
	};
}