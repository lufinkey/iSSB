#include "Application.h"
#include "ApplicationEventListener.h"
#include "AssetManager.h"
#include "BatchLoader.h"
#include "GlobalDefs.h"
#include "View.h"

#include "Actor/Actor.h"
#include "Actor/Animation.h"
#include "Actor/PrimitiveActor.h"
#include "Actor/TextActor.h"
#include "Actor/WireframeActor.h"

#include "Graphics/Graphics2D.h"

#include "Input/Keys.h"
#include "Input/TouchPoint.h"

#include "CodeBridge/CPPBridge.h"

#include "Output/Console.h"

#include "ScreenManager/MenuScreen.h"
#include "ScreenManager/Screen.h"
#include "ScreenManager/ScreenManager.h"

#include "Sound/Music.h"
#include "Sound/Sound.h"

#include "Util/ArrayList.h"
#include "Util/Bitset.h"
#include "Util/BufferedImage.h"
#include "Util/Color.h"
#include "Util/Font.h"
#include "Util/HapticFeedback.h"
#include "Util/Image.h"
#include "Util/P2PManager.h"
#include "Util/PixelIterator.h"
#include "Util/PrefManager.h"
#include "Util/String.h"
#include "Util/Thread.h"
#include "Util/Vector2.h"

#pragma once

namespace GameEngine
{
	double random();
	bool isOnPlatform(const char* platform);
}

using namespace GameEngine;

typedef unsigned char byte;
#ifndef boolean
typedef bool boolean;
#endif

#ifdef TRANSPARENT
#undef TRANSPARENT
#endif



#ifndef _COMMA
#define _COMMA ,
#endif

#ifndef _CONCAT_TOKENS_X
#define _CONCAT_TOKENS_X(token1, token2) token1##token2
#endif

#ifndef _CONCAT_TOKENS
#define _CONCAT_TOKENS(token1, token2) _CONCAT_TOKENS_X(token1, token2)
#endif

#ifndef _STRINGIZEX
#define _STRINGIZEX(x) #x
#endif

#ifndef _STRINGIZE
#define _STRINGIZE(x) _STRINGIZEX(x)
#endif
