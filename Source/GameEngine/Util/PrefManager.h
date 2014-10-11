
#include "ArrayList.h"
#include "String.h"

#pragma once

namespace GameEngine
{
	class PrefManager
	{
	private:
		String prefPath;
		
		typedef struct
		{
			String name;
			String value;
		} Pref;
		
		ArrayList<Pref> prefs;
		
	public:
		PrefManager();
		~PrefManager();
		
		void load(const String&fileName, bool dynamic=false);
		void save(const String&fileName);
		
		void addValue(const String&name, const String&value);
		void setValue(const String&name, const String&value);
		
		bool getBooleanValue(const String&name) const;
		int getIntValue(const String&name) const;
		float getFloatValue(const String&name) const;
		long getLongValue(const String&name) const;
		double getDoubleValue(const String&name) const;
		String getStringValue(const String&name) const;
		
		ArrayList<String> getKeys();
	};
}