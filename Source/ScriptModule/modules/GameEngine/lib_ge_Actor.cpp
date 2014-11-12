
#ifndef SMASHBROS_SCRIPT_DISABLE

#include "lib_GameEngine.h"

namespace GameEngine
{
	//PrimitiveActor

	void delete_PrimitiveActor(PrimitiveActor*actor)
	{
		delete actor;
	}



	//Actor

	Actor* new_Actor()
	{
		return new Actor();
	}

	Actor* new_Actor(const Actor&actor)
	{
		return new Actor(actor);
	}

	Actor* new_Actor(float x, float y)
	{
		return new Actor(x, y);
	}

	void delete_Actor(Actor*actor)
	{
		delete actor;
	}



	//Animation

	Animation* new_Animation(const Animation& anim)
	{
		return new Animation(anim);
	}

	Animation* new_Animation(const String&name, int speed)
	{
		return new Animation(name, speed);
	}

	Animation* new_Animation(const String&name, int speed, const String&frame)
	{
		return new Animation(name, speed, frame);
	}

	Animation* new_Animation(const String&name, int speed, int rows, int cols)
	{
		return new Animation(name, speed, rows, cols);
	}

	Animation* new_Animation(const String&name, int speed, int rows, int cols, const ArrayList<int>& seq)
	{
		return new Animation(name, speed, rows, cols, seq);
	}

	void delete_Animation(Animation* animation)
	{
		delete animation;
	}



	//WireframeActor

	WireframeActor* new_WireframeActor()
	{
		return new WireframeActor();
	}

	WireframeActor* new_WireframeActor(const WireframeActor&actor)
	{
		return new WireframeActor(actor);
	}

	WireframeActor* new_WireframeActor(float x, float y)
	{
		return new WireframeActor(x, y);
	}

	WireframeActor* new_WireframeActor(float x, float y, int width, int height)
	{
		return new WireframeActor(x, y, width, height);
	}

	void delete_WireframeActor(WireframeActor*wireframeactor)
	{
		delete wireframeactor;
	}



	//TextActor

	TextActor* new_TextActor(const String&s, Font*f, const Color&c)
	{
		return new TextActor(s, f, c);
	}

	TextActor* new_TextActor(float x1, float y1, const String&s, Font*f, const Color&c)
	{
		return new TextActor(x1, y1, s, f, c);
	}

	void delete_TextActor(TextActor* textActor)
	{
		delete textActor;
	}


	chaiscript::ModulePtr load_module_GameEngine_Actor()
	{
		chaiscript::Module* m_gameengine_actor = new chaiscript::Module();

		//PrimitiveActor
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::delete_WireframeActor), "delete_WireframeActor");

		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::PrimitiveActor::ACTORTYPE_PRIMITIVE), "ACTORTYPE_PRIMITIVE");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::PrimitiveActor::ACTORTYPE_ACTOR), "ACTORTYPE_ACTOR");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::PrimitiveActor::ACTORTYPE_WIREFRAME), "ACTORTYPE_WIREFRAME");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::PrimitiveActor::ACTORTYPE_TEXT), "ACTORTYPE_TEXT");

		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::PrimitiveActor::DIR_UP), "DIR_UP");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::PrimitiveActor::DIR_UPRIGHT), "DIR_UPRIGHT");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::PrimitiveActor::DIR_RIGHT), "DIR_RIGHT");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::PrimitiveActor::DIR_DOWNRIGHT), "DIR_DOWNRIGHT");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::PrimitiveActor::DIR_DOWN), "DIR_DOWN");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::PrimitiveActor::DIR_DOWNLEFT), "DIR_DOWNLEFT");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::PrimitiveActor::DIR_LEFT), "DIR_LEFT");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::PrimitiveActor::DIR_UPLEFT), "DIR_UPLEFT");

		m_gameengine_actor->add(chaiscript::fun(&GameEngine::PrimitiveActor::x), "x");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::PrimitiveActor::y), "y");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::PrimitiveActor::width), "width");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::PrimitiveActor::height), "height");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::PrimitiveActor::getActorType), "getActorType");

		m_gameengine_actor->add(chaiscript::fun((unsigned char(*)(float,float,float,float)) &GameEngine::PrimitiveActor::getDir), "PrimitiveActor_getDir");
		m_gameengine_actor->add(chaiscript::fun((unsigned char(*)(float, float, float, float)) &GameEngine::PrimitiveActor::getDir2), "PrimitiveActor_getDir2");
		m_gameengine_actor->add(chaiscript::fun((unsigned char(*)(const GameEngine::Rectangle&,const GameEngine::Rectangle&)) &GameEngine::PrimitiveActor::getDir), "PrimitiveActor_getDir");
		m_gameengine_actor->add(chaiscript::fun((unsigned char(*)(const GameEngine::RectangleF&,const GameEngine::RectangleF&)) &GameEngine::PrimitiveActor::getDir), "PrimitiveActor_getDir");
		m_gameengine_actor->add(chaiscript::fun((unsigned char(*)(GameEngine::PrimitiveActor*, GameEngine::PrimitiveActor*)) &GameEngine::PrimitiveActor::getDir), "PrimitiveActor_getDir");



		//Actor
		m_gameengine_actor->add(chaiscript::fun((GameEngine::Actor*(*)()) &GameEngine::new_Actor), "new_Actor");
		m_gameengine_actor->add(chaiscript::fun((GameEngine::Actor*(*)(const GameEngine::Actor&)) &GameEngine::new_Actor), "new_Actor");
		m_gameengine_actor->add(chaiscript::fun((GameEngine::Actor*(*)(float, float)) &GameEngine::new_Actor), "new_Actor");
		m_gameengine_actor->add(chaiscript::fun(&delete_Actor), "delete_Actor");

		m_gameengine_actor->add_global_const(chaiscript::const_var(Actor::EVENT_MOUSECLICK), "ACTOR_EVENT_MOUSECLICK");
		m_gameengine_actor->add_global_const(chaiscript::const_var(Actor::EVENT_MOUSERELEASE), "ACTOR_EVENT_MOUSERELEASE");
		m_gameengine_actor->add_global_const(chaiscript::const_var(Actor::EVENT_MOUSEENTER), "ACTOR_EVENT_MOUSEENTER");
		m_gameengine_actor->add_global_const(chaiscript::const_var(Actor::EVENT_MOUSELEAVE), "ACTOR_EVENT_MOUSELEAVE");
		m_gameengine_actor->add_global_const(chaiscript::const_var(Actor::EVENT_ANIMATIONFINISH), "ACTOR_EVENT_ANIMATIONFINISH");
		m_gameengine_actor->add_global_const(chaiscript::const_var(Actor::EVENT_MOVEFINISH), "ACTOR_EVENT_MOVEFINISH");

		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::xvelocity), "xvelocity");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::yvelocity), "yvelocity");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::Scale), "Scale");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::Update), "Update");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::Draw), "Draw");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::mirror), "mirror");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::mirrorVertical), "mirrorVertical");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::isMirrored), "isMirrored");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::isMirroredVertical), "isMirroredVertical");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::isEventEnabled), "isEventEnabled");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::setEventEnabled), "setEventEnabled");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::changeAnimation), "changeAnimation");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::changeAnimationDirection), "changeAnimationDirection");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::onAnimationFinish), "onAnimationFinsh");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::addAnimation), "addAnimation");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::removeAnimation), "removeAnimation");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::hasAnimation), "hasAnimation");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::getAnimation), "getAnimation");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::getLastAnimation), "getLastAnimation");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::setRelativeToView), "setRelativeToView");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::isRelativeToView), "isRelativeToView");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::mouseOverUsesPixel), "mouseOverUsesPixel");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::mouseOver), "mouseOver");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::onMouseEnter), "onMouseEnter");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::onMouseLeave), "onMouseLeave");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::onClick), "onClick");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::onRelease), "onRelease");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::isClicked), "isClicked");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::wasClicked), "wasClicked");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::moveTo), "moveTo");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::onMoveFinish), "onMoveFinish");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::getAnimName), "getAnimName");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::getCurrentFrame), "getCurrentFrame");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::pixelAtPoint), "pixelAtPoint");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::isColliding), "isColliding");
		m_gameengine_actor->add(chaiscript::fun((bool(GameEngine::Actor::*)(GameEngine::Actor*)) &GameEngine::Actor::rectsColliding), "rectsColliding");
		m_gameengine_actor->add(chaiscript::fun((bool(GameEngine::Actor::*)(GameEngine::WireframeActor*)) &GameEngine::Actor::rectsColliding), "rectsColliding");
		m_gameengine_actor->add(chaiscript::fun((bool(GameEngine::Actor::*)(GameEngine::Actor*)) &GameEngine::Actor::circlesColliding), "circlesColliding");
		m_gameengine_actor->add(chaiscript::fun((bool(GameEngine::Actor::*)(GameEngine::WireframeActor*)) &GameEngine::Actor::circlesColliding), "circlesColliding");
		m_gameengine_actor->add(chaiscript::fun((bool(GameEngine::Actor::*)(GameEngine::Actor*,double)) &GameEngine::Actor::circlesColliding), "circlesColliding");
		m_gameengine_actor->add(chaiscript::fun((bool(GameEngine::Actor::*)(GameEngine::WireframeActor*,double)) &GameEngine::Actor::circlesColliding), "circlesColliding");
		m_gameengine_actor->add(chaiscript::fun((void(GameEngine::Actor::*)(GameEngine::Actor*)) &GameEngine::Actor::circleResponse), "circleResponse");
		m_gameengine_actor->add(chaiscript::fun((void(GameEngine::Actor::*)(GameEngine::WireframeActor*)) &GameEngine::Actor::circleResponse), "circleResponse");
		m_gameengine_actor->add(chaiscript::fun((void(GameEngine::Actor::*)(GameEngine::Actor*,unsigned char)) &GameEngine::Actor::rectResponse), "rectResponse");
		m_gameengine_actor->add(chaiscript::fun((void(GameEngine::Actor::*)(GameEngine::WireframeActor*, unsigned char)) &GameEngine::Actor::rectResponse), "rectResponse");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::isOnScreen), "isOnScreen");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::getOverlapArea), "getOverlapArea");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::showWireframe), "showWireframe");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::setWireframeColor), "setwWireframeColor");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::getXSpeed), "getXSpeed");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::getYSpeed), "getYSpeed");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::getXPrev), "getXPrev");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::getYPrev), "getYPrev");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::setColor), "setColor");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::getColor), "getColor");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::setRotation), "setRotation");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::getRotation), "getRotation");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::setAlpha), "setAlpha");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::getAlpha), "getAlpha");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Actor::setVisible), "setVisible");



		//Animation
		m_gameengine_actor->add(chaiscript::fun((GameEngine::Animation*(*)(const GameEngine::Animation&)) &GameEngine::new_Animation), "new_Animation");
		m_gameengine_actor->add(chaiscript::fun((GameEngine::Animation*(*)(const GameEngine::String&,int)) &GameEngine::new_Animation), "new_Animation");
		m_gameengine_actor->add(chaiscript::fun((GameEngine::Animation*(*)(const GameEngine::String&,int,const String&)) &GameEngine::new_Animation), "new_Animation");
		m_gameengine_actor->add(chaiscript::fun((GameEngine::Animation*(*)(const GameEngine::String&,int,int,int)) &GameEngine::new_Animation), "new_Animation");
		m_gameengine_actor->add(chaiscript::fun((GameEngine::Animation*(*)(const GameEngine::String&,int,int,int,const ArrayList<int>&)) &GameEngine::new_Animation), "new_Animation");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::delete_Animation), "delete_Animation");

		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::NO_CHANGE), "NO_CHANGE");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::FORWARD), "FORWARD");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::BACKWARD), "BACKWARD");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::STOPPED), "STOPPED");

		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::Animation::TYPE_MULTIFILE), "ANIMATION_TYPE_MULTIFILE");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::Animation::TYPE_SINGLEFILE), "ANIMATION_TYPE_SINGLEFILE");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::Animation::TYPE_SPECFRAME_SINGLEFILE), "ANIMATION_TYPE_SPECFRAME_SINGLEFILE");

		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::fps), "fps");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::name), "name");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::mirror), "mirror");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::mirrorVertical), "mirrorVertical");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::isMirrored), "isMirrored");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::isMirroredVertical), "isMirroredVertical");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::getWidth), "getWidth");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::getHeight), "getHeight");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::getSize), "getSize");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::addFrame), "addFrame");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::setFrame), "setFrame");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::getTotalFrames), "getTotalFrames");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::getCurrentImage), "getCurrentImage");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::getCols), "getCols");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::getRows), "getRows");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::getType), "getType");
		m_gameengine_actor->add(chaiscript::fun((void(GameEngine::Animation::*)(Actor*,Graphics2D&,float,float,double)) &GameEngine::Animation::drawFrame), "drawFrame");
		m_gameengine_actor->add(chaiscript::fun((void(GameEngine::Animation::*)(Actor*,Graphics2D&,int,float,float,double)) &GameEngine::Animation::drawFrame), "drawFrame");
		m_gameengine_actor->add(chaiscript::fun((void(GameEngine::Animation::*)(Actor*,Graphics2D&,int,float,float,double,bool)) &GameEngine::Animation::drawFrame), "drawFrame");
		m_gameengine_actor->add(chaiscript::fun((void(GameEngine::Animation::*)(Actor*,Graphics2D&,long,float,float,double)) &GameEngine::Animation::nextFrame), "nextFrame");
		m_gameengine_actor->add(chaiscript::fun((void(GameEngine::Animation::*)(Actor*,Graphics2D&,long,float,float,double,bool)) &GameEngine::Animation::nextFrame), "nextFrame");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::setCurrentFrame), "setCurrentFrame");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::getLastFrame), "getLastFrame");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::getCurrentFrame), "getCurrentFrame");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::getSequenceFrame), "getSequenceFrame");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::Animation::getAllFilenames), "getAllFilenames");



		//WireframeActor
		m_gameengine_actor->add(chaiscript::fun((GameEngine::WireframeActor*(*)()) &GameEngine::new_WireframeActor), "new_WireframeActor");
		m_gameengine_actor->add(chaiscript::fun((GameEngine::WireframeActor*(*)(const GameEngine::WireframeActor&)) &GameEngine::new_WireframeActor), "new_WireframeActor");
		m_gameengine_actor->add(chaiscript::fun((GameEngine::WireframeActor*(*)(float,float)) &GameEngine::new_WireframeActor), "new_WireframeActor");
		m_gameengine_actor->add(chaiscript::fun((GameEngine::WireframeActor*(*)(float,float,int,int)) &GameEngine::new_WireframeActor), "new_WireframeActor");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::delete_WireframeActor), "delete_WireframeActor");

		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::WireframeActor::EVENT_MOUSECLICK), "WIREFRAMEACTOR_EVENT_MOUSECLICK");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::WireframeActor::EVENT_MOUSERELEASE), "WIREFRAMEACTOR_EVENT_MOUSERELEASE");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::WireframeActor::EVENT_MOUSEENTER), "WIREFRAMEACTOR_EVENT_MOUSEENTER");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::WireframeActor::EVENT_MOUSELEAVE), "WIREFRAMEACTOR_EVENT_MOUSELEAVE");

		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::xvelocity), "xvelocity");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::yvelocity), "yvelocity");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::setVisible), "setVisible");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::isVisible), "isVisible");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::setFilled), "setFilled");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::isFilled), "isFilled");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::setColor), "setColor");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::getColor), "getColor");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::isColliding), "isColliding");
		m_gameengine_actor->add(chaiscript::fun((bool(GameEngine::WireframeActor::*)(GameEngine::Actor*)) &GameEngine::WireframeActor::rectsColliding), "rectsColliding");
		m_gameengine_actor->add(chaiscript::fun((bool(GameEngine::WireframeActor::*)(GameEngine::WireframeActor*)) &GameEngine::WireframeActor::rectsColliding), "rectsColliding");
		m_gameengine_actor->add(chaiscript::fun((bool(GameEngine::WireframeActor::*)(GameEngine::Actor*)) &GameEngine::WireframeActor::circlesColliding), "circlesColliding");
		m_gameengine_actor->add(chaiscript::fun((bool(GameEngine::WireframeActor::*)(GameEngine::WireframeActor*)) &GameEngine::WireframeActor::circlesColliding), "circlesColliding");
		m_gameengine_actor->add(chaiscript::fun((bool(GameEngine::WireframeActor::*)(GameEngine::Actor*,double)) &GameEngine::WireframeActor::circlesColliding), "circlesColliding");
		m_gameengine_actor->add(chaiscript::fun((bool(GameEngine::WireframeActor::*)(GameEngine::WireframeActor*,double)) &GameEngine::WireframeActor::circlesColliding), "circlesColliding");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::Update), "Update");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::Draw), "Draw");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::isEventEnabled), "isEventEnabled");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::setEventEnabled), "setEventEnabled");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::onMouseEnter), "onMouseEnter");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::onMouseLeave), "onMouseLeave");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::onClick), "onClick");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::onRelease), "onRelease");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::mouseOver), "mouseOver");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::isClicked), "isClicked");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::wasClicked), "wasClicked");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::isOnScreen), "isOnScreen");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::getXSpeed), "getXSpeed");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::getYSpeed), "getYSpeed");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::getXPrev), "getXPrev");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::WireframeActor::getXPrev), "getYPrev");



		//TextActor
		m_gameengine_actor->add(chaiscript::fun((GameEngine::TextActor*(*)(const String&,Font*,const Color&)) &GameEngine::new_TextActor), "new_TextActor");
		m_gameengine_actor->add(chaiscript::fun((GameEngine::TextActor*(*)(const String&, Font*, const Color&)) &GameEngine::new_TextActor), "new_TextActor");
		m_gameengine_actor->add(chaiscript::fun(&GameEngine::delete_TextActor), "delete_TextActor");

		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::TextActor::ALIGN_BOTTOMLEFT), "TEXTACTOR_ALIGN_BOTTOMLEFT");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::TextActor::ALIGN_BOTTOMRIGHT), "TEXTACTOR_ALIGN_BOTTOMRIGHT");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::TextActor::ALIGN_CENTER), "TEXTACTOR_ALIGN_CENTER");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::TextActor::ALIGN_TOPLEFT), "TEXTACTOR_ALIGN_TOPLEFT");
		m_gameengine_actor->add_global_const(chaiscript::const_var(GameEngine::TextActor::ALIGN_TOPRIGHT), "TEXTACTOR_ALIGN_TOPRIGHT");

		m_gameengine_actor->add(chaiscript::fun(&TextActor::Scale), "Scale");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::toString), "toString");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::formatToBox), "formatToBox");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::Update), "Update");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::Draw), "Draw");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::isOnScreen), "isOnScreen");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::showWireframe), "showWireframe");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::setWireframeColor), "setWireframeColor");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::setText), "setText");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::getText), "getText");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::setFont), "setFont");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::getFont), "getFont");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::setSize), "setSize");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::getSize), "getSize");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::setStyle), "setStyle");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::getStyle), "getStyle");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::setColor), "setColor");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::getColor), "getColor");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::setAlignment), "setAlignment");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::getAlignment), "getAlignment");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::setLineSpacing), "setLineSpacing");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::setRelativeToView), "setRelativeToView");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::isRelativeToView), "isRelativeToView");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::onMouseEnter), "onMouseEnter");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::onMouseLeave), "onMouseLeave");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::onClick), "onClick");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::onRelease), "onRelease");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::mouseOver), "mouseOver");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::isClicked), "isClicked");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::wasClicked), "wasClicked");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::setAntiAliasing), "setAntiAliasing");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::getAntiAliasing), "getAntiAliasing");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::setRotation), "setRotation");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::getRotation), "getRotation");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::setAlpha), "setAlpha");
		m_gameengine_actor->add(chaiscript::fun(&TextActor::getAlpha), "getAlpha");

		return chaiscript::ModulePtr(m_gameengine_actor);
	}
}

#endif //SMASHBROS_SCRIPT_DISABLE
