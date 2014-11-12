
#include "../forwards.h"
#include "PrimitiveActor.h"
#include "../Graphics/Graphics2D.h"
#include "../Util/String.h"
#include "../Util/Font.h"

#pragma once

namespace GameEngine
{
	class TextActor : public PrimitiveActor
	{
		friend class PrimitiveActor;
	private:
		Color wireframeColor;
		
		double Rotation;
		float Alpha;
		float Scale;
		
		Color color;
		Font*font;
		String text;

		unsigned int fontSize;
		int fontStyle;
		
		String originalText;
		
		int charWidth;
		int charHeight;
		
		unsigned int lineSpace;
		
		unsigned char alignment;
		bool mouseover;
		bool prevMouseover;
		long touchId;
		long currentTouchId;
		bool showwire;
		
		bool relative;
		
		bool clicked;
		bool prevclicked;
		
		bool antialiasing;
		
		void drawString(Graphics2D& g, const String& text, float x1, float y1);
		
		void updateSize();
		
		bool checkHover(float x1, float y1);
		
		float getCenterX();
		float getCenterY();
		
		Rectangle getRect();
		
	protected:
		void drawActor(Graphics2D& g, long gameTime, bool relativeToScreen);
		
	public:
		static const unsigned char ALIGN_BOTTOMLEFT = 0;
		static const unsigned char ALIGN_BOTTOMRIGHT = 1;
		static const unsigned char ALIGN_CENTER = 2;
		static const unsigned char ALIGN_TOPLEFT = 3;
		static const unsigned char ALIGN_TOPRIGHT = 4;
		
		TextActor(const String& s, Font*f, const Color&c);
		TextActor(float x1, float y1, const String& s, Font*f, const Color&c);
		virtual ~TextActor();
		
		const String& toString();
		
		void formatToBox(int width, int height);
		
		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D& g, long gameTime);
		
		virtual bool isOnScreen();
		
		void showWireframe(bool toggle);
		void setWireframeColor(const Color&c);
		
		void setText(const String& s);
		const String& getText();
		
		void setFont(Font*f);
		Font*getFont();
		
		void setSize(unsigned int size);
		int getSize();
		
		void setStyle(int style);
		int getStyle();
		
		void setColor(const Color&c);
		const Color& getColor();
		
		void setAlignment(unsigned char align);
		unsigned char getAlignment();
		
		void setLineSpacing(unsigned int space);
		
		void setRelativeToView(bool toggle);
		bool isRelativeToView();
		
		virtual void onMouseEnter();
		virtual void onMouseLeave();
		virtual void onClick();
		virtual void onRelease();
		
		bool mouseOver();
		
		bool isClicked();
		bool wasClicked();
		
		long getTouchId();
		
		void setAntiAliasing(bool toggle);
		bool getAntiAliasing();
		
		void setRotation(double degrees);
		double getRotation();
		
		void setAlpha(float alpha);
		float getAlpha();
		
		void setScale(float scale);
		float getScale();
	};
}