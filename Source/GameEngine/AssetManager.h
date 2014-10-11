
#include "Util/ArrayList.h"
#include "Util/String.h"
#include "Util/Font.h"
#include "Util/BufferedImage.h"

#pragma once

namespace GameEngine
{
	class AssetManager
	{
	private:
		static ArrayList<BufferedImage*> Images;
		static ArrayList<String> ImageNames;
		
		static ArrayList<Font*> Fonts;
		static ArrayList<String> FontNames;
		
		static bool alreadyStoredImage(const String&imgName);
		static bool alreadyStoredFont(const String&fontName);
		
	public:
		static bool loadStringFromFile(const String& fileName, String&str);
		
		static bool loadImage(const String&imgName);
		static BufferedImage* getImage(const String&imgName);
		static void unloadImage(const String&imgName);
		
		static bool loadFont(const String&fontName, int style = Font::PLAIN, unsigned int size = 1);
		static Font* getFont(const String&fontName);
		static Font* getFont(const String&fontName, int style, unsigned int size);
		static void unloadFont(const String&fontName);
	};
}