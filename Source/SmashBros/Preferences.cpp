
#include "Preferences.h"
#include "Game.h"
#include "Controls.h"

namespace SmashBros
{
	bool Preferences::menuMusic = true;
	bool Preferences::menuSoundFx = true;
	bool Preferences::ingameMusic = true;
	
	bool Preferences::highfps = false;
	
	const String Preferences::version = "2.2";
	
	bool Preferences::newVersion = false;
	
	bool Preferences::debuglog = false;
	
	String Preferences::versionMessage = (String)"Welcome to iSSB v2.2! I apologize sincerely for the lack of updates. I have been incredibly "
												+"busy over the past few months. To make up for it, I have added Pikachu as a new character! Please "
												+"consider donating by going to \"Options\", selecting \"Other\", and then selecting \"Donate\". Thank you!";
	
	PrefManager Preferences::prefMgr = PrefManager();
	
	void Preferences::init()
	{
		prefMgr.addValue("version",0);
		prefMgr.addValue("debuglog",debuglog);
		prefMgr.addValue("menuMusic",menuMusic);
		prefMgr.addValue("menuSoundFx",menuSoundFx);
		prefMgr.addValue("ingameMusic",ingameMusic);
		prefMgr.addValue("highfps",highfps);
		
		prefMgr.addValue("controls_joystick",    Controls::joystickEnabled);
		
		prefMgr.addValue("controls_pause",       Controls::controls[0][Controls::BUTTON_PAUSE]);
		
		prefMgr.addValue("controls_p1_up",       Controls::controls[1][Controls::BUTTON_UP]);
		prefMgr.addValue("controls_p1_down",     Controls::controls[1][Controls::BUTTON_DOWN]);
		prefMgr.addValue("controls_p1_left",     Controls::controls[1][Controls::BUTTON_LEFT]);
		prefMgr.addValue("controls_p1_right",    Controls::controls[1][Controls::BUTTON_RIGHT]);
		prefMgr.addValue("controls_p1_jump",     Controls::controls[1][Controls::BUTTON_JUMP]);
		prefMgr.addValue("controls_p1_standard", Controls::controls[1][Controls::BUTTON_STANDARD]);
		prefMgr.addValue("controls_p1_special",  Controls::controls[1][Controls::BUTTON_SPECIAL]);
		prefMgr.addValue("controls_p1_grab",     Controls::controls[1][Controls::BUTTON_GRAB]);
		
		prefMgr.addValue("controls_p2_up",       Controls::controls[2][Controls::BUTTON_UP]);
		prefMgr.addValue("controls_p2_down",     Controls::controls[2][Controls::BUTTON_DOWN]);
		prefMgr.addValue("controls_p2_left",     Controls::controls[2][Controls::BUTTON_LEFT]);
		prefMgr.addValue("controls_p2_right",    Controls::controls[2][Controls::BUTTON_RIGHT]);
		prefMgr.addValue("controls_p2_jump",     Controls::controls[2][Controls::BUTTON_JUMP]);
		prefMgr.addValue("controls_p2_standard", Controls::controls[2][Controls::BUTTON_STANDARD]);
		prefMgr.addValue("controls_p2_special",  Controls::controls[2][Controls::BUTTON_SPECIAL]);
		prefMgr.addValue("controls_p2_grab",     Controls::controls[2][Controls::BUTTON_GRAB]);
		
		prefMgr.addValue("controls_p3_up",       Controls::controls[3][Controls::BUTTON_UP]);
		prefMgr.addValue("controls_p3_down",     Controls::controls[3][Controls::BUTTON_DOWN]);
		prefMgr.addValue("controls_p3_left",     Controls::controls[3][Controls::BUTTON_LEFT]);
		prefMgr.addValue("controls_p3_right",    Controls::controls[3][Controls::BUTTON_RIGHT]);
		prefMgr.addValue("controls_p3_jump",     Controls::controls[3][Controls::BUTTON_JUMP]);
		prefMgr.addValue("controls_p3_standard", Controls::controls[3][Controls::BUTTON_STANDARD]);
		prefMgr.addValue("controls_p3_special",  Controls::controls[3][Controls::BUTTON_SPECIAL]);
		prefMgr.addValue("controls_p3_grab",     Controls::controls[3][Controls::BUTTON_GRAB]);
		
		prefMgr.addValue("controls_p4_up",       Controls::controls[4][Controls::BUTTON_UP]);
		prefMgr.addValue("controls_p4_down",     Controls::controls[4][Controls::BUTTON_DOWN]);
		prefMgr.addValue("controls_p4_left",     Controls::controls[4][Controls::BUTTON_LEFT]);
		prefMgr.addValue("controls_p4_right",    Controls::controls[4][Controls::BUTTON_RIGHT]);
		prefMgr.addValue("controls_p4_jump",     Controls::controls[4][Controls::BUTTON_JUMP]);
		prefMgr.addValue("controls_p4_standard", Controls::controls[4][Controls::BUTTON_STANDARD]);
		prefMgr.addValue("controls_p4_special",  Controls::controls[4][Controls::BUTTON_SPECIAL]);
		prefMgr.addValue("controls_p4_grab",     Controls::controls[4][Controls::BUTTON_GRAB]);
		
		for(int i=0; i<Global::totalItems; i++)
		{
			prefMgr.addValue((String)"items[" + i + "]", true);
		}
	}
	
	void Preferences::load()
	{
		prefMgr.load("com.brokenphysics.iSSB.prefs");
		
		debuglog = prefMgr.getBooleanValue("debuglog");
		menuMusic = prefMgr.getBooleanValue("menuMusic");
		menuSoundFx = prefMgr.getBooleanValue("menuSoundFx");
		ingameMusic = prefMgr.getBooleanValue("ingameMusic");
		highfps = prefMgr.getBooleanValue("highfps");
		
		Controls::joystickEnabled = prefMgr.getBooleanValue("controls_joystick");
		
		Controls::controls[0][Controls::BUTTON_PAUSE]    = prefMgr.getIntValue("controls_pause");
		
		Controls::controls[1][Controls::BUTTON_UP]       = prefMgr.getIntValue("controls_p1_up");
		Controls::controls[1][Controls::BUTTON_DOWN]     = prefMgr.getIntValue("controls_p1_down");
		Controls::controls[1][Controls::BUTTON_LEFT]     = prefMgr.getIntValue("controls_p1_left");
		Controls::controls[1][Controls::BUTTON_RIGHT]    = prefMgr.getIntValue("controls_p1_right");
		Controls::controls[1][Controls::BUTTON_JUMP]     = prefMgr.getIntValue("controls_p1_jump");
		Controls::controls[1][Controls::BUTTON_STANDARD] = prefMgr.getIntValue("controls_p1_standard");
		Controls::controls[1][Controls::BUTTON_SPECIAL]  = prefMgr.getIntValue("controls_p1_special");
		Controls::controls[1][Controls::BUTTON_GRAB]     = prefMgr.getIntValue("controls_p1_grab");
		
		Controls::controls[2][Controls::BUTTON_UP]       = prefMgr.getIntValue("controls_p2_up");
		Controls::controls[2][Controls::BUTTON_DOWN]     = prefMgr.getIntValue("controls_p2_down");
		Controls::controls[2][Controls::BUTTON_LEFT]     = prefMgr.getIntValue("controls_p2_left");
		Controls::controls[2][Controls::BUTTON_RIGHT]    = prefMgr.getIntValue("controls_p2_right");
		Controls::controls[2][Controls::BUTTON_JUMP]     = prefMgr.getIntValue("controls_p2_jump");
		Controls::controls[2][Controls::BUTTON_STANDARD] = prefMgr.getIntValue("controls_p2_standard");
		Controls::controls[2][Controls::BUTTON_SPECIAL]  = prefMgr.getIntValue("controls_p2_special");
		Controls::controls[2][Controls::BUTTON_GRAB]     = prefMgr.getIntValue("controls_p2_grab");
		
		Controls::controls[3][Controls::BUTTON_UP]       = prefMgr.getIntValue("controls_p3_up");
		Controls::controls[3][Controls::BUTTON_DOWN]     = prefMgr.getIntValue("controls_p3_down");
		Controls::controls[3][Controls::BUTTON_LEFT]     = prefMgr.getIntValue("controls_p3_left");
		Controls::controls[3][Controls::BUTTON_RIGHT]    = prefMgr.getIntValue("controls_p3_right");
		Controls::controls[3][Controls::BUTTON_JUMP]     = prefMgr.getIntValue("controls_p3_jump");
		Controls::controls[3][Controls::BUTTON_STANDARD] = prefMgr.getIntValue("controls_p3_standard");
		Controls::controls[3][Controls::BUTTON_SPECIAL]  = prefMgr.getIntValue("controls_p3_special");
		Controls::controls[3][Controls::BUTTON_GRAB]     = prefMgr.getIntValue("controls_p3_grab");
		
		Controls::controls[4][Controls::BUTTON_UP]       = prefMgr.getIntValue("controls_p4_up");
		Controls::controls[4][Controls::BUTTON_DOWN]     = prefMgr.getIntValue("controls_p4_down");
		Controls::controls[4][Controls::BUTTON_LEFT]     = prefMgr.getIntValue("controls_p4_left");
		Controls::controls[4][Controls::BUTTON_RIGHT]    = prefMgr.getIntValue("controls_p4_right");
		Controls::controls[4][Controls::BUTTON_JUMP]     = prefMgr.getIntValue("controls_p4_jump");
		Controls::controls[4][Controls::BUTTON_STANDARD] = prefMgr.getIntValue("controls_p4_standard");
		Controls::controls[4][Controls::BUTTON_SPECIAL]  = prefMgr.getIntValue("controls_p4_special");
		Controls::controls[4][Controls::BUTTON_GRAB]     = prefMgr.getIntValue("controls_p4_grab");
		
		for(int i=0; i<Global::totalItems; i++)
		{
			Global::itemsOn[i] = prefMgr.getBooleanValue((String)"items[" + i + "]");
		}
		
		String vers = prefMgr.getStringValue("version");
		if(!vers.equals(version))
		{
			newVersion = true;
			Console::WriteLine((String)"upgraded from version " + vers + " to version " + version);
			prefMgr.setValue("version", version);
			prefMgr.save("com.brokenphysics.iSSB.prefs");
		}
	}
	
	void Preferences::save()
	{
		prefMgr.setValue("debuglog",debuglog);
		prefMgr.setValue("menuMusic",menuMusic);
		prefMgr.setValue("menuSoundFx",menuSoundFx);
		prefMgr.setValue("ingameMusic",ingameMusic);
		prefMgr.setValue("highfps",highfps);
		
		prefMgr.setValue("controls_joystick",    Controls::joystickEnabled);
		
		prefMgr.setValue("controls_pause",       Controls::controls[0][Controls::BUTTON_PAUSE]);
		
		prefMgr.setValue("controls_p1_up",       Controls::controls[1][Controls::BUTTON_UP]);
		prefMgr.setValue("controls_p1_down",     Controls::controls[1][Controls::BUTTON_DOWN]);
		prefMgr.setValue("controls_p1_left",     Controls::controls[1][Controls::BUTTON_LEFT]);
		prefMgr.setValue("controls_p1_right",    Controls::controls[1][Controls::BUTTON_RIGHT]);
		prefMgr.setValue("controls_p1_jump",     Controls::controls[1][Controls::BUTTON_JUMP]);
		prefMgr.setValue("controls_p1_standard", Controls::controls[1][Controls::BUTTON_STANDARD]);
		prefMgr.setValue("controls_p1_special",  Controls::controls[1][Controls::BUTTON_SPECIAL]);
		prefMgr.setValue("controls_p1_grab",     Controls::controls[1][Controls::BUTTON_GRAB]);
		
		prefMgr.setValue("controls_p2_up",       Controls::controls[2][Controls::BUTTON_UP]);
		prefMgr.setValue("controls_p2_down",     Controls::controls[2][Controls::BUTTON_DOWN]);
		prefMgr.setValue("controls_p2_left",     Controls::controls[2][Controls::BUTTON_LEFT]);
		prefMgr.setValue("controls_p2_right",    Controls::controls[2][Controls::BUTTON_RIGHT]);
		prefMgr.setValue("controls_p2_jump",     Controls::controls[2][Controls::BUTTON_JUMP]);
		prefMgr.setValue("controls_p2_standard", Controls::controls[2][Controls::BUTTON_STANDARD]);
		prefMgr.setValue("controls_p2_special",  Controls::controls[2][Controls::BUTTON_SPECIAL]);
		prefMgr.setValue("controls_p2_grab",     Controls::controls[2][Controls::BUTTON_GRAB]);
		
		prefMgr.setValue("controls_p3_up",       Controls::controls[3][Controls::BUTTON_UP]);
		prefMgr.setValue("controls_p3_down",     Controls::controls[3][Controls::BUTTON_DOWN]);
		prefMgr.setValue("controls_p3_left",     Controls::controls[3][Controls::BUTTON_LEFT]);
		prefMgr.setValue("controls_p3_right",    Controls::controls[3][Controls::BUTTON_RIGHT]);
		prefMgr.setValue("controls_p3_jump",     Controls::controls[3][Controls::BUTTON_JUMP]);
		prefMgr.setValue("controls_p3_standard", Controls::controls[3][Controls::BUTTON_STANDARD]);
		prefMgr.setValue("controls_p3_special",  Controls::controls[3][Controls::BUTTON_SPECIAL]);
		prefMgr.setValue("controls_p3_grab",     Controls::controls[3][Controls::BUTTON_GRAB]);
		
		prefMgr.setValue("controls_p4_up",       Controls::controls[4][Controls::BUTTON_UP]);
		prefMgr.setValue("controls_p4_down",     Controls::controls[4][Controls::BUTTON_DOWN]);
		prefMgr.setValue("controls_p4_left",     Controls::controls[4][Controls::BUTTON_LEFT]);
		prefMgr.setValue("controls_p4_right",    Controls::controls[4][Controls::BUTTON_RIGHT]);
		prefMgr.setValue("controls_p4_jump",     Controls::controls[4][Controls::BUTTON_JUMP]);
		prefMgr.setValue("controls_p4_standard", Controls::controls[4][Controls::BUTTON_STANDARD]);
		prefMgr.setValue("controls_p4_special",  Controls::controls[4][Controls::BUTTON_SPECIAL]);
		prefMgr.setValue("controls_p4_grab",     Controls::controls[4][Controls::BUTTON_GRAB]);
		
		for(int i=0; i<Global::totalItems; i++)
		{
			prefMgr.addValue((String)"items[" + i + "]", Global::itemsOn[i]);
		}
		
		prefMgr.save("com.brokenphysics.iSSB.prefs");
	}

	void Preferences::toggleMenuMusic(bool toggle)
	{
		menuMusic = toggle;
	}
	
	void Preferences::toggleMenuSoundFX(bool toggle)
	{
		menuSoundFx = toggle;
	}
	
	void Preferences::toggleInGameMusic(bool toggle)
	{
		ingameMusic = toggle;
	}
	
	void Preferences::setHighFPS(bool toggle)
	{
		highfps = toggle;
		if(highfps)
		{
			Game::setFPS(60);
			Game::setUpdatesPerFrame(1);
		}
		else
		{
			Game::setFPS(30);
			Game::setUpdatesPerFrame(2);
		}
	}
	
	bool Preferences::menuMusicOn()
	{
		return menuMusic;
	}
	
	bool Preferences::menuSoundFXOn()
	{
		return menuSoundFx;
	}
	
	bool Preferences::ingameMusicOn()
	{
		return ingameMusic;
	}
	
	bool Preferences::highFPS()
	{
		return highfps;
	}
}