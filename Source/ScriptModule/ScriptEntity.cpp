
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "ScriptEntity.h"
#include <Plist.hpp>

namespace ScriptModule
{
	ScriptEntityInfo::ScriptEntityInfo()
	{
		//
	}

	ScriptEntityInfo::ScriptEntityInfo(const ScriptEntityInfo&info)
	{
		path = info.path;
		creator = info.creator;
		version = info.version;
		icon = info.icon;
		mainScript = info.mainScript;
		otherScripts = info.otherScripts;
	}

	ScriptEntityInfo::~ScriptEntityInfo()
	{
		//
	}

	ScriptEntityInfo& ScriptEntityInfo::operator=(const ScriptEntityInfo&info)
	{
		path = info.path;
		creator = info.creator;
		version = info.version;
		icon = info.icon;
		mainScript = info.mainScript;
		otherScripts = info.otherScripts;

		return *this;
	}

	bool ScriptEntityInfo::loadFromFile(const String& path, String& error)
	{
		clear();

		std::map<std::string, boost::any> dict;
		try
		{
			Plist::readPlist(path + "/Info.plist", dict);
		}
		catch (Plist::Error&e)
		{
			error = e.what();
			return false;
		}

		//creator

		boost::any value = dict["creator"];
		if (value.empty())
		{
			clear();
			error = (String)"\"creator\" property not defined";
			return false;
		}
		String str = boost::any_cast<std::string>(value);
		creator = str;

		//version

		value = dict["version"];
		if (value.empty())
		{
			clear();
			error = (String)"\"version\" property not defined";
			return false;
		}
		str = boost::any_cast<std::string>(value);
		version = str;

		//icon

		value = dict["icon"];
		if (!value.empty())
		{
			str = boost::any_cast<std::string>(value);
			icon = str;
		}

		//name

		value = dict["name"];
		if (value.empty())
		{
			clear();
			error = (String)"\"name\" property not defined";
			return false;
		}
		str = boost::any_cast<std::string>(value);
		bool validName = checkClassName(str);
		if(!validName)
		{
			clear();
			error = (String)"invalid class name \"" + str + "\". \"name\" field can only contain letters, numbers, and underscores";
			return false;
		}
		mainScript.name = str;

		//mainScript

		value = dict["mainScript"];
		if (value.empty())
		{
			clear();
			error = (String)"\"mainScript\" property not defined";
			return false;
		}
		str = boost::any_cast<std::string>(value);
		mainScript.script = str;

		//type

		value = dict["type"];
		if(value.empty())
		{
			clear();
			error = (String)"\"type\" property not defined";
			return false;
		}
		str = boost::any_cast<std::string>(value);
		validName = checkClassType(str);
		if(!validName)
		{
			clear();
			error = (String)"invalid class type \"" + str + "\". \"type\" field can only contain letters, numbers, and underscores, and must be a valid class type";
			return false;
		}
		mainScript.type = str;

		//otherScripts

		value = dict["otherScripts"];
		if(!value.empty())
		{
			std::vector<boost::any> otherScripts = boost::any_cast<std::vector<boost::any>>(value);
			for (unsigned int i=0; i<otherScripts.size(); i++)
			{
				std::map<std::string, boost::any> scriptInfoDict = boost::any_cast<std::map<std::string, boost::any>>(otherScripts[i]);

				//otherScripts > name

				value = scriptInfoDict["name"];
				if(value.empty())
				{
					clear();
					error = (String)"\"name\" property not defined for script at index " + i + " in \"otherScripts\"";
					return false;
				}
				String className = boost::any_cast<std::string>(value);
				validName = checkClassName(className);
				if(!validName)
				{
					clear();
					error = (String)"invalid class name \"" + className + "\" in otherScripts at index " + i + ". \"name\" field can only contain letters, numbers, and underscores";
					return false;
				}
				if(className.equals(mainScript.name))
				{
					clear();
					error = (String)"duplicate name \"" + className + "\" for script at index " + i + "in \"otherScripts\"";
					return false;
				}
				for(int j=0; j<this->otherScripts.size(); j++)
				{
					if(this->otherScripts.get(j).name.equals(className))
					{
						clear();
						error = (String)"duplicate name \"" + className + "\" for script at index " + i + "in \"otherScripts\"";
						return false;
					}
				}

				//otherScripts > mainScript

				value = scriptInfoDict["mainScript"];
				if (value.empty())
				{
					clear();
					error = (String)"\"mainScript\" property not defined for script " + className + " in \"otherScripts\"";
					return false;
				}
				String mainScript = boost::any_cast<std::string>(value);

				//otherScripts > type

				value = scriptInfoDict["type"];
				if (value.empty())
				{
					clear();
					error = (String)"\"type\" property not defined for script " + className + " in \"otherScripts\"";
					return false;
				}
				String type = boost::any_cast<std::string>(value);
				validName = checkClassType(type);
				if(!validName)
				{
					clear();
					error = (String)"invalid class type \"" + type + "\" in otherScripts at index " + i + ". \"type\" field can only contain letters, numbers, and underscores, and must be a valid class type";
					return false;
				}
				
				addScript(className, mainScript, type);
			}
		}

		this->path = path;

		return true;
	}

	void ScriptEntityInfo::setPath(const String& path)
	{
		this->path = path;
	}

	void ScriptEntityInfo::setCreator(const String& creator)
	{
		this->creator = creator;
	}

	void ScriptEntityInfo::setVersion(const String& version)
	{
		this->version = version;
	}

	void ScriptEntityInfo::setIcon(const String& icon)
	{
		this->icon = icon;
	}

	void ScriptEntityInfo::setMainScript(const ScriptEntityInfo::ScriptInfo& script)
	{
		mainScript = script;
	}

	void ScriptEntityInfo::setMainScript(const String& name, const String& script, const String& type)
	{
		mainScript.name = name;
		mainScript.script = script;
		mainScript.type = type;
	}

	void ScriptEntityInfo::addScript(const String& name, const String& script, const String& type)
	{
		ScriptInfo info;
		info.name = name;
		info.script = script;
		info.type = type;
		otherScripts.add(info);
	}

	const String& ScriptEntityInfo::getPath() const
	{
		return path;
	}

	const String& ScriptEntityInfo::getCreator() const
	{
		return creator;
	}

	const String& ScriptEntityInfo::getVersion() const
	{
		return version;
	}

	const String& ScriptEntityInfo::getIcon() const
	{
		return icon;
	}

	const ScriptEntityInfo::ScriptInfo& ScriptEntityInfo::getMainScript() const
	{
		return mainScript;
	}

	const ArrayList<ScriptEntityInfo::ScriptInfo>& ScriptEntityInfo::getScripts() const
	{
		return otherScripts;
	}

	void ScriptEntityInfo::clear()
	{
		path = "";
		mainScript.name = "";
		mainScript.script = "";
		mainScript.type = "";
		otherScripts.clear();
	}

	bool ScriptEntityInfo::checkClassName(const String& className)
	{
		if(className.length() == 0)
		{
			return false;
		}
		for(int i=0; i<className.length(); i++)
		{
			char c = className.charAt(i);
			if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_'))
			{
				return false;
			}
		}
		return true;
	}

	bool ScriptEntityInfo::checkClassType(const String& classType)
	{
		return checkClassName(classType);
	}



	ScriptData::ScriptData(const ScriptEntityInfo& entityInfo)
	{
		this->entityInfo = ((ScriptEntityInfo*)&entityInfo);
	}

	ScriptData::ScriptData(const ScriptData&data)
	{
		entityInfo = data.entityInfo;
		filePath = data.filePath;
		contents = data.contents;
	}

	ScriptData::~ScriptData()
	{
		//
	}

	ScriptData& ScriptData::operator=(const ScriptData&data)
	{
		entityInfo = data.entityInfo;
		filePath = data.filePath;
		contents = data.contents;
		return *this;
	}

	bool ScriptData::loadFromFile(const String& path, String& error)
	{
		bool success = AssetManager::loadStringFromFile(path, contents);
		if(!success)
		{
			filePath = "";
			contents = "";
			error = (String)"unable to load";
			return false;
		}
		filePath = path;
		contents.replace('\r', '\n');
		return true;
	}

	ScriptEntityInfo* ScriptData::getScriptEntityInfo() const
	{
		return entityInfo;
	}

	ScriptEntityInfo::ScriptInfo* ScriptData::getScriptInfo() const
	{
		const String& entityPath = entityInfo->getPath() + '/';
		const ScriptEntityInfo::ScriptInfo& mainScript = entityInfo->getMainScript();
		if(filePath.equals(entityPath + mainScript.script))
		{
			return ((ScriptEntityInfo::ScriptInfo*)&mainScript);
		}

		const ArrayList<ScriptEntityInfo::ScriptInfo>& otherScripts = entityInfo->getScripts();
		for(int i=0; i<otherScripts.size(); i++)
		{
			const ScriptEntityInfo::ScriptInfo& scriptInfo = otherScripts.get(i);
			if(filePath.equals(entityPath + scriptInfo.script))
			{
				return (ScriptEntityInfo::ScriptInfo*)&scriptInfo;
			}
		}

		return NULL;
	}

	const String& ScriptData::getFilePath() const
	{
		return filePath;
	}

	const String& ScriptData::getContents() const
	{
		return contents;
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
