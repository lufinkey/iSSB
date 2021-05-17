
#define _CRT_SECURE_NO_WARNINGS

#include "PrefManager.h"
#include "../GlobalDefs.h"
#include "SDL_rwops.h"
#include "../Output/Console.h"

#if defined(__APPLE__)
	#include "TargetConditionals.h"
#endif

namespace GameEngine
{
	PrefManager::PrefManager()
	{
#if defined(__APPLE__) && (TARGET_OS_IPHONE == 1 || TARGET_IPHONE_SIMULATOR == 1 || TARGET_OS_MAC == 1)
		char*path = getenv("HOME");
		if(path==NULL)
		{
			Console::WriteLine("Error getting home directory");
		}
		else
		{
			prefPath = path;
			prefPath += "/Library/Preferences/";
		}
#elif defined (__ANDROID__)
		// TODO change for android
		prefPath = "";
#else
		prefPath = "";
#endif
	}
	
	PrefManager::~PrefManager()
	{
		prefs.clear();
	}
	
	void PrefManager::load(const String&fileName, bool dynamic)
	{
		ArrayList<String> lines;
		
		SDL_RWops*file = SDL_RWFromFile(prefPath + fileName, "rb");
		if(file==NULL)
		{
			Console::WriteLine((String)"error opening file " + prefPath + fileName);
			return;
		}
		else
		{
			SDL_RWseek(file,0,RW_SEEK_END);
			int total = (int)SDL_RWtell(file);
			SDL_RWseek(file,0,RW_SEEK_SET);
			char*fileText = new char[total+1];
			fileText[total] = '\0';
			SDL_RWread(file,fileText,1,total+1);
			String currentLine = "";
			for(int i=0; i<total; i++)
			{
				char c = fileText[i];
				if(c!='\0' && ((int)c)>=0)
				{
					currentLine+=c;
				}
				if(c=='\n' || c=='\r' || c=='\0' || ((int)c)<0 || i==(total-1))
				{
					if(currentLine.length()>1)
					{
						lines.add(currentLine);
					}
					currentLine.clear();
				}
			}
			delete[] fileText;
		}
		
		for(int i=0; i<lines.size(); i++)
		{
			String line = lines.get(i);
			
			String name;
			String value;
			
			bool leftSide = true;
			
			int j=0;
			
			for(j=0; j<line.length(); j++)
			{
				char c = line.charAt(j);
				if(leftSide)
				{
					if(c=='=')
					{
						leftSide = false;
					}
					else
					{
						name+=c;
					}
				}
				else
				{
					if(c=='=')
					{
						leftSide = true;
						j = line.length();
					}
					else if(c!='\n' && c!='\r')
					{
						value+=c;
					}
				}
			}
			
			if(!leftSide)
			{
				name = name.trim();
				value = value.trim();
				
				if(name.charAt(0)=='\"' && name.charAt(name.length()-1)=='\"')
				{
					name = name.substring(1,name.length()-1);
				}
				if(value.charAt(0)=='\"' && value.charAt(name.length()-1)=='\"')
				{
					value = value.substring(1,name.length()-1);
				}
				
				if (dynamic)
				{
					addValue(name, value);
				}
				else
				{
					setValue(name,value);
				}
			}
		}
		
		if(file!=NULL)
		{
			SDL_RWclose(file);
		}
	}
	
	void PrefManager::save(const String&fileName)
	{
		SDL_RWops*file = SDL_RWFromFile(prefPath + fileName, "w");
		
		for(int i=0; i<prefs.size(); i++)
		{
			Pref&pref = prefs.get(i);
			String buf = pref.name + '=' + pref.value + '\n';
			if(SDL_RWwrite(file,(char*)buf,1,buf.length())<(unsigned int)buf.length())
			{
				Console::WriteLine(SDL_GetError());
			}
		}
		
        SDL_RWclose(file);
	}
	
	void PrefManager::addValue(const String&name, const String&value)
	{
		for(int i=0; i<prefs.size(); i++)
		{
			Pref&pref = prefs.get(i);
			if(pref.name.equals(name))
			{
				pref.value = value;
				return;
			}
		}
		Pref pref = {name, value};
		prefs.add(pref);
	}
	
	void PrefManager::setValue(const String&name, const String&value)
	{
		for(int i=0; i<prefs.size(); i++)
		{
			Pref&pref = prefs.get(i);
			if(pref.name.equals(name))
			{
				pref.value = value;
				return;
			}
		}
	}
	
	bool PrefManager::getBooleanValue(const String&name) const
	{
		return String::asBool(getStringValue(name));
	}
	
	int PrefManager::getIntValue(const String&name) const
	{
		return String::asInt(getStringValue(name));
	}
	
	float PrefManager::getFloatValue(const String&name) const
	{
		return String::asFloat(getStringValue(name));
	}
	
	long PrefManager::getLongValue(const String&name) const
	{
		return String::asLong(getStringValue(name));
	}
	
	double PrefManager::getDoubleValue(const String&name) const
	{
		return String::asDouble(getStringValue(name));
	}
	
	String PrefManager::getStringValue(const String&name) const
	{
		for(int i=0; i<prefs.size(); i++)
		{
			const Pref&pref = prefs.get(i);
			if(pref.name.equals(name))
			{
				return pref.value;
			}
		}
		
		return "";
	}
	
	ArrayList<String> PrefManager::getKeys()
	{
		ArrayList<String> keys;
		for (int i = 0; i < prefs.size(); i++)
		{
			keys.add(prefs.get(i).name);
		}
		return keys;
	}
}
