#include "Actor.h"
#include "Animation.h"
#include "Application.h"
#include "ApplicationEventListener.h"
#include "ArrayList.h"
#include "AssetManager.h"
#include "BatchLoader.h"
#include "Bitset.h"
#include "BufferedImage.h"
#include "Color.h"
#include "Console.h"
#include "Font.h"
#include "GlobalDefs.h"
#include "Graphics2D.h"
#include "Image.h"
#include "Keys.h"
#include "MenuScreen.h"
#include "Music.h"
#include "P2PManager.h"
#include "PixelIterator.h"
#include "PrefManager.h"
#include "PrimitiveActor.h"
#include "Screen.h"
#include "ScreenManager.h"
#include "Sound.h"
#include "String.h"
#include "TextActor.h"
#include "Thread.h"
#include "TouchPoint.h"
#include "Vector2.h"
#include "View.h"
#include "WireframeActor.h"

#include "ObjCBridge.h"

#pragma once

namespace GameEngine
{
	static double random()
	{
		return (double)rand()/RAND_MAX;
	}
}

using namespace GameEngine;

typedef unsigned char byte;
typedef bool boolean;