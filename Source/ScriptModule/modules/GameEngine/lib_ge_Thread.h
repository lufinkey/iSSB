
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_GameEngine.h"

#pragma once

namespace GameEngine
{
	class ScriptThread : public Thread
	{
	private:
		std::function<void(chaiscript::Boxed_Value&)> runCallback;
		std::function<void(chaiscript::Boxed_Value&)> finishCallback;
		chaiscript::Boxed_Value data;

	public:
		ScriptThread(chaiscript::Boxed_Value& data, std::function<void(chaiscript::Boxed_Value&)>& runCallback);
		ScriptThread(chaiscript::Boxed_Value& data, std::function<void(chaiscript::Boxed_Value&)>& runCallback, std::function<void(chaiscript::Boxed_Value&)>& finishCallback);
		virtual ~ScriptThread();

		virtual void run();
		virtual void finish();
	};
}

#endif //SMASHBROS_SCRIPT_DISABLE
