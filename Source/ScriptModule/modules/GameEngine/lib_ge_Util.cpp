
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_GameEngine.h"

#include "../../ScriptOperatorOverloads.h"
#include "lib_ge_ArrayList.h"
#include "lib_ge_Thread.h"
#include "lib_ge_Vector2.h"

#undef TRANSPARENT

namespace GameEngine
{
	//BufferedImage

	BufferedImage* new_BufferedImage()
	{
		return new BufferedImage();
	}

	BufferedImage* new_BufferedImage(const BufferedImage& img)
	{
		return new BufferedImage(img);
	}

	BufferedImage* new_BufferedImage(unsigned int width, unsigned int height)
	{
		return new BufferedImage(width, height);
	}

	BufferedImage* new_BufferedImage(unsigned int width, unsigned int height, const Color&color)
	{
		return new BufferedImage(width, height, color);
	}

	BufferedImage* new_BufferedImage(const sf::Image&img)
	{
		return new BufferedImage(img);
	}

	void delete_BufferedImage(BufferedImage*img)
	{
		delete img;
	}



	//Image

	sf::Image* new_Image()
	{
		return new sf::Image();
	}

	sf::Image* new_Image(const sf::Image&img)
	{
		return new sf::Image(img);
	}

	sf::Image* new_Image(unsigned int width, unsigned int height)
	{
		sf::Image* img = new sf::Image();
		img->create(width, height);
		return img;
	}

	sf::Image* new_Image(unsigned int width, unsigned int height, const Color&color)
	{
		sf::Image* img = new sf::Image();
		img->create(width, height, color);
		return img;
	}

	sf::Image* new_Image(const BufferedImage& img)
	{
		return new sf::Image(img.getTexture()->copyToImage());
	}

	void delete_Image(sf::Image*img)
	{
		delete img;
	}



	//Font

	Font* new_Font(sf::Font*derive)
	{
		return new Font(derive);
	}

	Font* new_Font(sf::Font*derive, int style)
	{
		return new Font(derive, style);
	}

	Font* new_Font(sf::Font*derive, int style, unsigned int size)
	{
		return new Font(derive, style, size);
	}

	void delete_Font(Font* font)
	{
		delete font;
	}



	//Thread

	ScriptThread::ScriptThread(chaiscript::Boxed_Value& data, std::function<void(chaiscript::Boxed_Value&)>& runCallback)
	{
		this->data = data;
		this->runCallback = runCallback;
	}

	ScriptThread::ScriptThread(chaiscript::Boxed_Value& data, std::function<void(chaiscript::Boxed_Value&)>& runCallback, std::function<void(chaiscript::Boxed_Value&)>& finishCallback)
	{
		this->data = data;
		this->runCallback = runCallback;
		this->finishCallback = finishCallback;
	}

	ScriptThread::~ScriptThread()
	{
		//
	}

	void ScriptThread::run()
	{
		if (runCallback)
		{
			runCallback(data);
		}
	}

	void ScriptThread::finish()
	{
		if (finishCallback)
		{
			finishCallback(data);
		}
	}

	ScriptThread* new_ScriptThread(chaiscript::Boxed_Value& data, std::function<void(chaiscript::Boxed_Value&)>& runCallback)
	{
		return new ScriptThread(data, runCallback);
	}

	ScriptThread* new_ScriptThread(chaiscript::Boxed_Value& data, std::function<void(chaiscript::Boxed_Value&)>& runCallback, std::function<void(chaiscript::Boxed_Value&)>& finishCallback)
	{
		return new ScriptThread(data, runCallback, finishCallback);
	}

	void delete_ScriptThread(ScriptThread* thread)
	{
		delete thread;
	}

	
	chaiscript::ModulePtr load_module_GameEngine_Util()
	{
		chaiscript::Module* m_gameengine_util = new chaiscript::Module();

		//ArrayList
		load_module_GameEngine_ArrayList<chaiscript::Boxed_Value>(m_gameengine_util, "List");
		//load_module_GameEngine_ArrayList<void*>(m_gameengine_util, "VoidList");
		load_module_GameEngine_ArrayList<bool>(m_gameengine_util, "BoolList");
		load_module_GameEngine_ArrayList<boolean>(m_gameengine_util, "BooleanList");
		load_module_GameEngine_ArrayList<byte>(m_gameengine_util, "ByteList");
		load_module_GameEngine_ArrayList<char>(m_gameengine_util, "CharList");
		load_module_GameEngine_ArrayList<short>(m_gameengine_util, "ShortList");
		load_module_GameEngine_ArrayList<int>(m_gameengine_util, "IntList");
		load_module_GameEngine_ArrayList<int*>(m_gameengine_util, "IntPtrList");
		load_module_GameEngine_ArrayList<unsigned int>(m_gameengine_util, "UnsignedIntList");
		load_module_GameEngine_ArrayList<float>(m_gameengine_util, "FloatList");
		load_module_GameEngine_ArrayList<double>(m_gameengine_util, "DoubleList");
		load_module_GameEngine_ArrayList<long>(m_gameengine_util, "LongList");
		load_module_GameEngine_ArrayList<unsigned long>(m_gameengine_util, "UnsignedLongList");
		load_module_GameEngine_ArrayList<long long>(m_gameengine_util, "LongLongList");
		load_module_GameEngine_ArrayList<unsigned long long>(m_gameengine_util, "UnsignedLongLongList");
		load_module_GameEngine_ArrayList<long double>(m_gameengine_util, "LongDoubleList");
		load_module_GameEngine_ArrayList<GameEngine::Actor*>(m_gameengine_util, "ActorList");
		load_module_GameEngine_ArrayList<GameEngine::Animation*>(m_gameengine_util, "AnimationList");
		load_module_GameEngine_ArrayList<GameEngine::TextActor*>(m_gameengine_util, "TextActorList");
		load_module_GameEngine_ArrayList<GameEngine::WireframeActor*>(m_gameengine_util, "WireframeActorList");
		load_module_GameEngine_ArrayList<GameEngine::String>(m_gameengine_util, "StringList");
		load_module_GameEngine_ArrayList<GameEngine::Vector2<chaiscript::Boxed_Value>>(m_gameengine_util, "Vector2List");
		load_module_GameEngine_ArrayList<GameEngine::Vector2i>(m_gameengine_util, "Vector2iList");
		load_module_GameEngine_ArrayList<GameEngine::Vector2f>(m_gameengine_util, "Vector2fList");
		load_module_GameEngine_ArrayList<GameEngine::Vector2d>(m_gameengine_util, "Vector2dList");
		load_module_GameEngine_ArrayList<GameEngine::BufferedImage*>(m_gameengine_util, "BufferedImageList");
		load_module_GameEngine_ArrayList<GameEngine::Font*>(m_gameengine_util, "FontList");



		//BufferedImage
		m_gameengine_util->add(chaiscript::fun((GameEngine::BufferedImage*(*)()) &GameEngine::new_BufferedImage), "new_BufferedImage");
		m_gameengine_util->add(chaiscript::fun((GameEngine::BufferedImage*(*)(const GameEngine::BufferedImage&)) &GameEngine::new_BufferedImage), "new_BufferedImage");
		m_gameengine_util->add(chaiscript::fun((GameEngine::BufferedImage*(*)(unsigned int,unsigned int)) &GameEngine::new_BufferedImage), "new_BufferedImage");
		m_gameengine_util->add(chaiscript::fun((GameEngine::BufferedImage*(*)(unsigned int,unsigned int,const Color&)) &GameEngine::new_BufferedImage), "new_BufferedImage");
		m_gameengine_util->add(chaiscript::fun((GameEngine::BufferedImage*(*)(const sf::Image&)) &GameEngine::new_BufferedImage), "new_BufferedImage");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::delete_BufferedImage), "delete_BufferedImage");

		m_gameengine_util->add(chaiscript::fun(&GameEngine::BufferedImage::loadFromFile), "loadFromFile");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::BufferedImage::update), "update");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::BufferedImage::getWidth), "getWidth");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::BufferedImage::getHeight), "getHeight");
		m_gameengine_util->add(chaiscript::fun((bool(GameEngine::BufferedImage::*)(int)const) &GameEngine::BufferedImage::pixelAtPoint), "pixelAtPoint");
		m_gameengine_util->add(chaiscript::fun((bool(GameEngine::BufferedImage::*)(int,int)const) &GameEngine::BufferedImage::pixelAtPoint), "pixelAtPoint");



		//Image
		m_gameengine_util->add(chaiscript::fun((sf::Image*(*)()) &GameEngine::new_Image), "new_Image");
		m_gameengine_util->add(chaiscript::fun((sf::Image*(*)(const sf::Image&)) &GameEngine::new_Image), "new_Image");
		m_gameengine_util->add(chaiscript::fun((sf::Image*(*)(unsigned int,unsigned int)) &GameEngine::new_Image), "new_Image");
		m_gameengine_util->add(chaiscript::fun((sf::Image*(*)(unsigned int,unsigned int,const Color&)) &GameEngine::new_Image), "new_Image");
		m_gameengine_util->add(chaiscript::fun((sf::Image*(*)(const GameEngine::BufferedImage&)) &GameEngine::new_Image), "new_Image");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::delete_Image), "delete_Image");

		m_gameengine_util->add(chaiscript::fun(&sf::Image::loadFromFile), "loadFromFile");
		m_gameengine_util->add(chaiscript::fun(&sf::Image::saveToFile), "saveToFile");
		m_gameengine_util->add(chaiscript::fun(&sf::Image::getSize), "getSize");
		m_gameengine_util->add(chaiscript::fun(&sf::Image::setPixel), "setPixel");
		m_gameengine_util->add(chaiscript::fun(&sf::Image::getPixel), "getPixel");

	

		//Color
		m_gameengine_util->add(chaiscript::constructor<GameEngine::Color()>(), "Color");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::Color(const Color&)>(), "Color");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::Color(const sf::Color&)>(), "Color");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::Color(int)>(), "Color");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::Color(int,bool)>(), "Color");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::Color(unsigned char,unsigned char,unsigned char)>(), "Color");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::Color(unsigned char,unsigned char,unsigned char,unsigned int)>(), "Color");

		m_gameengine_util->add_global_const(chaiscript::const_var(GameEngine::Color::BLACK), "COLOR_BLACK");
		m_gameengine_util->add_global_const(chaiscript::const_var(GameEngine::Color::BLUE), "COLOR_BLUE");
		m_gameengine_util->add_global_const(chaiscript::const_var(GameEngine::Color::CYAN), "COLOR_CYAN");
		m_gameengine_util->add_global_const(chaiscript::const_var(GameEngine::Color::DARKGRAY), "COLOR_DARKGRAY");
		m_gameengine_util->add_global_const(chaiscript::const_var(GameEngine::Color::GRAY), "COLOR_GRAY");
		m_gameengine_util->add_global_const(chaiscript::const_var(GameEngine::Color::LIGHTGRAY), "COLOR_LIGHTGRAY");
		m_gameengine_util->add_global_const(chaiscript::const_var(GameEngine::Color::GREEN), "COLOR_GREEN");
		m_gameengine_util->add_global_const(chaiscript::const_var(GameEngine::Color::MAGENTA), "COLOR_MAGENTA");
		m_gameengine_util->add_global_const(chaiscript::const_var(GameEngine::Color::ORANGE), "COLOR_ORANGE");
		m_gameengine_util->add_global_const(chaiscript::const_var(GameEngine::Color::PINK), "COLOR_PINK");
		m_gameengine_util->add_global_const(chaiscript::const_var(GameEngine::Color::RED), "COLOR_RED");
		m_gameengine_util->add_global_const(chaiscript::const_var(GameEngine::Color::WHITE), "COLOR_WHITE");
		m_gameengine_util->add_global_const(chaiscript::const_var(GameEngine::Color::YELLOW), "COLOR_YELLOW");
		m_gameengine_util->add_global_const(chaiscript::const_var(GameEngine::Color::TRANSPARENT), "COLOR_TRANSPARENT");

		m_gameengine_util->add(chaiscript::fun(&GameEngine::Color::r), "r");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::Color::g), "g");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::Color::b), "b");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::Color::a), "a");
		m_gameengine_util->add(chaiscript::fun((bool(GameEngine::Color::*)(const GameEngine::Color&)const) &GameEngine::Color::equals), "equals");
		m_gameengine_util->add(chaiscript::fun((bool(GameEngine::Color::*)(const sf::Color&)const) &GameEngine::Color::equals), "equals");
		m_gameengine_util->add(chaiscript::fun((bool(GameEngine::Color::*)(const GameEngine::Color&)const) &GameEngine::Color::operator==), "==");
		m_gameengine_util->add(chaiscript::fun((bool(GameEngine::Color::*)(const sf::Color&)const) &GameEngine::Color::operator==), "==");



		//Font
		m_gameengine_util->add(chaiscript::fun((Font*(*)(sf::Font*)) &GameEngine::new_Font), "new_Font");
		m_gameengine_util->add(chaiscript::fun((Font*(*)(sf::Font*,int)) &GameEngine::new_Font), "new_Font");
		m_gameengine_util->add(chaiscript::fun((Font*(*)(sf::Font*,int,unsigned int)) &GameEngine::new_Font), "new_Font");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::delete_Font), "delete_Font");

		m_gameengine_util->add_global_const(chaiscript::const_var(GameEngine::Font::PLAIN), "FONT_PLAIN");
		m_gameengine_util->add_global_const(chaiscript::const_var(GameEngine::Font::BOLD), "FONT_BOLD");
		m_gameengine_util->add_global_const(chaiscript::const_var(GameEngine::Font::ITALIC), "FONT_ITALIC");

		m_gameengine_util->add(chaiscript::fun(&GameEngine::Font::getFont), "getFont");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::Font::getStyle), "getStyle");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::Font::getSize), "getSize");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::Font::setStyle), "setStyle");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::Font::setSize), "setSize");



		//PixelIterator
		m_gameengine_util->add(chaiscript::constructor<GameEngine::PixelIterator(GameEngine::Actor*)>(), "PixelIterator");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::PixelIterator::reset), "reset");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::PixelIterator::checkNextPixel), "checkNextPixel");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::PixelIterator::getCurrentPoint), "getCurrentPoint");



		//PrefManager
		m_gameengine_util->add(chaiscript::constructor<GameEngine::PrefManager()>(), "PrefManager");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::PrefManager::load), "load");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::PrefManager::save), "save");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::PrefManager::addValue), "addValue");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::PrefManager::setValue), "setValue");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::PrefManager::getBooleanValue), "getBooleanValue");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::PrefManager::getIntValue), "getIntValue");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::PrefManager::getFloatValue), "getFloatValue");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::PrefManager::getLongValue), "getLongValue");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::PrefManager::getDoubleValue), "getDoubleValue");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::PrefManager::getStringValue), "getStringValue");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::PrefManager::getKeys), "getKeys");



		//String
		m_gameengine_util->add(chaiscript::constructor<GameEngine::String()>(), "String");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::String(const GameEngine::String&)>(), "String");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::String(const std::string&)>(), "String");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::String(const char*)>(), "String");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::String(const wchar_t*)>(), "String");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::String(const std::wstring&)>(), "String");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::String(const char)>(), "String");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::String(const unsigned char)>(), "String");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::String(const bool)>(), "String");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::String(const int)>(), "String");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::String(const unsigned int)>(), "String");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::String(const float)>(), "String");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::String(const double)>(), "String");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::String(const long)>(), "String");

		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::asBool), "String_asBool");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::asInt), "String_asInt");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::asLong), "String_asLong");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::asShort), "String_asShort");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::asFloat), "String_asFloat");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::asDouble), "String_asDouble");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::asLongLong), "String_asLongLong");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::asUInt), "String_asUInt");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::asUChar), "String_asUChar");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::asULong), "String_asULong");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::asUShort), "String_asUShort");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::asULongLong), "String_asULongLong");

		m_gameengine_util->add(chaiscript::fun((GameEngine::String(GameEngine::String::*)(const GameEngine::String&)const) &GameEngine::String::operator+), "+");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String(GameEngine::String::*)(const std::string&)const) &GameEngine::String::operator+), "+");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String(GameEngine::String::*)(const char*)const) &GameEngine::String::operator+), "+");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String(GameEngine::String::*)(const wchar_t*)const) &GameEngine::String::operator+), "+");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String(GameEngine::String::*)(const std::wstring&)const) &GameEngine::String::operator+), "+");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String(GameEngine::String::*)(const char)const) &GameEngine::String::operator+), "+");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String(GameEngine::String::*)(const unsigned char)const) &GameEngine::String::operator+), "+");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String(GameEngine::String::*)(const bool)const) &GameEngine::String::operator+), "+");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String(GameEngine::String::*)(const int)const) &GameEngine::String::operator+), "+");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String(GameEngine::String::*)(const unsigned int)const) &GameEngine::String::operator+), "+");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String(GameEngine::String::*)(const float)const) &GameEngine::String::operator+), "+");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String(GameEngine::String::*)(const double)const) &GameEngine::String::operator+), "+");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String(GameEngine::String::*)(const long)const) &GameEngine::String::operator+), "+");

		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const GameEngine::String&)) &GameEngine::String::operator+=), "+=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const std::string&)) &GameEngine::String::operator+=), "+=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const char*)) &GameEngine::String::operator+=), "+=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const wchar_t*)) &GameEngine::String::operator+=), "+=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const std::wstring&)) &GameEngine::String::operator+=), "+=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const char)) &GameEngine::String::operator+=), "+=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const unsigned char)) &GameEngine::String::operator+=), "+=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const bool)) &GameEngine::String::operator+=), "+=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const int)) &GameEngine::String::operator+=), "+=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const unsigned int)) &GameEngine::String::operator+=), "+=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const float)) &GameEngine::String::operator+=), "+=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const double)) &GameEngine::String::operator+=), "+=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const long)) &GameEngine::String::operator+=), "+=");

		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const GameEngine::String&)) &GameEngine::String::operator=), "=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const std::string&)) &GameEngine::String::operator=), "=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const char*)) &GameEngine::String::operator=), "=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const wchar_t*)) &GameEngine::String::operator=), "=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const std::wstring&)) &GameEngine::String::operator=), "=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const char)) &GameEngine::String::operator=), "=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const unsigned char)) &GameEngine::String::operator=), "=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const bool)) &GameEngine::String::operator=), "=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const int)) &GameEngine::String::operator=), "=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const unsigned int)) &GameEngine::String::operator=), "=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const float)) &GameEngine::String::operator=), "=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const double)) &GameEngine::String::operator=), "=");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String&(GameEngine::String::*)(const long)) &GameEngine::String::operator=), "=");

		m_gameengine_util->add(chaiscript::fun((bool(GameEngine::String::*)(const GameEngine::String&)const) &GameEngine::String::operator==), "==");
		m_gameengine_util->add(chaiscript::fun((bool(GameEngine::String::*)(const char*)const) &GameEngine::String::operator==), "==");

		m_gameengine_util->add(chaiscript::fun((bool(GameEngine::String::*)(const GameEngine::String&)const) &GameEngine::String::equals), "equals");
		m_gameengine_util->add(chaiscript::fun((bool(GameEngine::String::*)(const char*)const) &GameEngine::String::equals), "equals");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::compare), "compare");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::clear), "clear");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::length), "length");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::charAt), "charAt");
		m_gameengine_util->add(chaiscript::fun((void(GameEngine::String::*)(const String&,const String&))&GameEngine::String::replace), "replace");
		m_gameengine_util->add(chaiscript::fun((void(GameEngine::String::*)(char,char))&GameEngine::String::replace), "replace");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String(GameEngine::String::*)(int)const) &GameEngine::String::substring), "substring");
		m_gameengine_util->add(chaiscript::fun((GameEngine::String(GameEngine::String::*)(int,int)const) &GameEngine::String::substring), "substring");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::trim), "trim");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::indexOf), "indexOf");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::lastIndexOf), "lastIndexOf");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::toLowerCase), "toLowerCase");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::String::toUpperCase), "toUpperCase");



		//Thread
		m_gameengine_util->add(chaiscript::fun((GameEngine::ScriptThread*(*)(chaiscript::Boxed_Value&,std::function<void(chaiscript::Boxed_Value&)>&,std::function<void(chaiscript::Boxed_Value&)>&)) &GameEngine::new_ScriptThread), "new_Thread");
		m_gameengine_util->add(chaiscript::fun((GameEngine::ScriptThread*(*)(chaiscript::Boxed_Value&,std::function<void(chaiscript::Boxed_Value&)>&)) &GameEngine::new_ScriptThread), "new_Thread");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::delete_ScriptThread), "delete_Thread");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::ScriptThread(chaiscript::Boxed_Value&, std::function<void(chaiscript::Boxed_Value&)>&, std::function<void(chaiscript::Boxed_Value&)>&)>(), "Thread");
		m_gameengine_util->add(chaiscript::constructor<GameEngine::ScriptThread(chaiscript::Boxed_Value&, std::function<void(chaiscript::Boxed_Value&)>&)>(), "Thread");

		m_gameengine_util->add(chaiscript::fun(&GameEngine::ScriptThread::start), "start");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::ScriptThread::stop), "stop");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::ScriptThread::join), "wait");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::ScriptThread::isAlive), "isAlive");
		m_gameengine_util->add(chaiscript::fun(&GameEngine::ScriptThread::sleep), "Thread_sleep");



		//Vector2
		load_module_GameEngine_Vector2<chaiscript::Boxed_Value>(m_gameengine_util, "Vector2");
		load_module_GameEngine_Vector2<byte>(m_gameengine_util, "Vector2b");
		load_module_GameEngine_Vector2<char>(m_gameengine_util, "Vector2c");
		load_module_GameEngine_Vector2<int>(m_gameengine_util, "Vector2i");
		load_module_GameEngine_Vector2<unsigned int>(m_gameengine_util, "Vector2u");
		load_module_GameEngine_Vector2<float>(m_gameengine_util, "Vector2f");
		load_module_GameEngine_Vector2<double>(m_gameengine_util, "Vector2d");
		load_module_GameEngine_Vector2<long>(m_gameengine_util, "Vector2l");



		//sf::Vector2
		load_module_GameEngine_sfVector2<chaiscript::Boxed_Value>(m_gameengine_util, "sfVector2");
		load_module_GameEngine_sfVector2<byte>(m_gameengine_util, "sfVector2b");
		load_module_GameEngine_sfVector2<char>(m_gameengine_util, "sfVector2c");
		load_module_GameEngine_sfVector2<int>(m_gameengine_util, "sfVector2i");
		load_module_GameEngine_sfVector2<unsigned int>(m_gameengine_util, "sfVector2u");
		load_module_GameEngine_sfVector2<float>(m_gameengine_util, "sfVector2f");
		load_module_GameEngine_sfVector2<double>(m_gameengine_util, "sfVector2d");
		load_module_GameEngine_sfVector2<long>(m_gameengine_util, "sfVector2l");

		return chaiscript::ModulePtr(m_gameengine_util);
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
