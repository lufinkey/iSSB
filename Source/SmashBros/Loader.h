
#include "Global.h"

#ifndef SMASHBROS_SCRIPT_DISABLE
#include "../ScriptModule/ScriptEntity.h"
#endif //SMASHBROS_SCRIPT_DISABLE

#if defined(__APPLE__)
	#include "TargetConditionals.h"
#endif

#pragma once

namespace SmashBros
{
	class CharacterLoader
	{
	private:
		static String getMenuFilename(int charNo);
		
	public:
		static String getFolder(int charNo);
		static String getName(int charNo);
		
		static String getIconPath(int charNo);
		static String getPreviewPath(int charNo);
		
		static Player* createPlayer(float x1, float y1, byte playerNo, byte team,int charNum);
		
		static ArrayList<Animation*> getWinnersScreenAnimations(int charNo);
	};
	
	class StageLoader
	{
	private:
	private:
#ifndef SMASHBROS_SCRIPT_DISABLE
		static ArrayList<ScriptModule::ScriptEntityInfo*> scriptEntities;
		static ArrayList<int> disabledScriptEntities;
#endif //SMASHBROS_SCRIPT_DISABLE
		
		static String getMenuFilename(int stageNo);
		
	public:
#ifndef SMASHBROS_SCRIPT_DISABLE
	#if defined(__APPLE__) && (TARGET_OS_IPHONE == 1 || TARGET_IPHONE_SIMULATOR == 1 || TARGET_OS_MAC == 1)
		static void loadScriptEntities(const String&path = (String)getenv("HOME")+"/Library/iSSB/addons/stages");
	#elif defined(__ANDROID__)
		// TODO change for android
		static void loadScriptEntities(const String&path = (String)getenv("HOME")+"/Library/iSSB/addons/stages");
	#else
		static void loadScriptEntities(const String&path = "addons/stages");
	#endif
		static void unloadScriptEntities();
		
		static void setDisabledScriptEntities(const ArrayList<int>& disabled);
		static ArrayList<ScriptModule::ScriptEntityInfo*> getScriptEntities();
#endif //SMASHBROS_SCRIPT_DISABLE
		
		static String getIconPath(int stageNo);
		
		static Stage* createStage(float x1, float y1, int stageNum);
	};
}
