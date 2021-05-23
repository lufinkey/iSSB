
#define _CRT_SECURE_NO_WARNINGS

#include "AssetManager.h"
#include "Output/Console.h"
#include <cstdio>

namespace GameEngine
{
	ArrayList<BufferedImage*> AssetManager::Images = ArrayList<BufferedImage*>();
	ArrayList<String> AssetManager::ImageNames = ArrayList<String>();
	
	ArrayList<Font*> AssetManager::Fonts = ArrayList<Font*>();
	ArrayList<String> AssetManager::FontNames = ArrayList<String>();
	
	bool AssetManager::loadStringFromFile(const String& fileName, String&str)
	{
		FILE*file = std::fopen(fileName, "r");
		if (file == NULL)
		{
			return false;
		}
		
		std::fseek(file, 0, SEEK_END);
		int total = ftell(file);
		std::fseek(file, 0, SEEK_SET);
		
		char*fileText = new char[total + 1];
		fileText[total] = '\0';
		
		std::fread(fileText, 1, total + 1, file);
		str = fileText;
		
		fclose(file);
		delete[] fileText;
		return true;
	}
	
	bool AssetManager::loadImage(const String& imgName)
	{
		if(!alreadyStoredImage(imgName))
		{
			Console::WriteLine((String)"Loading image " + imgName);
			BufferedImage*img = new BufferedImage();
			bool success = img->loadFromFile(imgName);
			if(success)
			{
				Images.add(img);
				ImageNames.add(imgName);
				return true;
			}
			Console::WriteLine((String)"Error loading image " + imgName);
			delete img;
			return false;
		}
		return true;
	}
	
	BufferedImage* AssetManager::getImage(const String&imgName)
	{
		int total = ImageNames.size();
		for(int i=0; i<total; i++)
		{
			if(imgName.equals(ImageNames.get(i)))
			{
				return Images.get(i);
			}
		}
		Console::WriteLine((String)"Error: image " + imgName + " does not exist!");
		return NULL;
	}
	
	void AssetManager::unloadImage(const String&imgName)
	{
		int total = ImageNames.size();
		for(int i=0; i<total; i++)
		{
			if(imgName.equals(ImageNames.get(i)))
			{
				delete Images[i];
				Images.remove(i);
				ImageNames.remove(i);
				return;
			}
		}
	}
	
	bool AssetManager::alreadyStoredImage(const String&imgName)
	{
		int total = ImageNames.size();
		for(int i=0; i<total; i++)
		{
			if(imgName.equals(ImageNames.get(i)))
			{
				return true;
			}
		}
		return false;
	}
	
	bool AssetManager::loadFont(const String&fontName, int style, unsigned int size)
	{
		if(!alreadyStoredFont(fontName))
		{
			Console::WriteLine((String)"Loading font " + fontName);
			Font*font = new Font(fontName,style,size);
			if(font->getTTF()!=NULL)
			{
				Fonts.add(font);
				FontNames.add(fontName);
				return true;
			}
			Console::WriteLine((String)"Error loading font " + fontName);
			delete font;
			return false;
		}
		return true;
	}
	
	Font*AssetManager::getFont(const String&fontName)
	{
		int total = FontNames.size();
		for(int i=0; i<total; i++)
		{
			if(fontName.equals(FontNames.get(i)))
			{
				return Fonts.get(i);
			}
		}
		Console::WriteLine((String)"Error: font " + fontName + (String)" does not exist!");
		return NULL;
	}
	
	Font*AssetManager::getFont(const String&fontName, int style, unsigned int size)
	{
		int total = FontNames.size();
		for(int i=0; i<total; i++)
		{
			if(fontName.equals(FontNames.get(i)))
			{
				Font*font = Fonts.get(i);
				font->setStyle(style);
				font->setSize(size);
				return font;
			}
		}
		Console::WriteLine((String)"Error: font " + fontName + (String)" does not exist!");
		return NULL;
	}
	
	void AssetManager::unloadFont(const String&fontName)
	{
		int total = FontNames.size();
		for(int i=0; i<total; i++)
		{
			if(fontName.equals(FontNames.get(i)))
			{
				delete Fonts[i];
				Fonts.remove(i);
				FontNames.remove(i);
				return;
			}
		}
	}
	
	bool AssetManager::alreadyStoredFont(const String&fontName)
	{
		int total = FontNames.size();
		for(int i=0; i<total; i++)
		{
			if(fontName.equals(FontNames.get(i)))
			{
				return true;
			}
		}
		return false;
	}
}