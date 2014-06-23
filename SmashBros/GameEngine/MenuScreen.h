
#include "forwards.h"
#include "Actor.h"
#include "TextActor.h"
#include "Screen.h"
#include "Sound.h"

#pragma once

namespace GameEngine
{
	class MenuScreen : public Screen
	{
	private:

		static const unsigned char TEXT = 0;
		static const unsigned char IMAGE = 1;

		class TextMenuItem : TextActor
		{
			friend class MenuScreen;
			private:
				MenuScreen*menu;

				unsigned char type;
				
				Color normColor;
				Color hoverColor;
				Color clickColor;
				
				String target;
				
				bool selected;
			public:
				TextMenuItem(MenuScreen*menu, float x1, float y1, String s, Font*f, const Color&normC, const Color&hoverC, String target);
				TextMenuItem(MenuScreen*menu, float x1, float y1, String s, Font*f, const Color&normC, const Color&hoverC, const Color&clickC, String target);
				virtual ~TextMenuItem();

				void OnRelease();
				virtual void Draw(Graphics2D& g, long gameTime);

		};

		class ImageMenuItem : Actor
		{
			friend class MenuScreen;
			private:
				MenuScreen*menu;
				
				unsigned char type;
				
				String target;
				Color hover,click,normal;
				bool selected;
				
			public:
				ImageMenuItem(MenuScreen*menu, float x1, float y1,Animation*normAnim, Animation*hoverAnim, String target);
				ImageMenuItem(MenuScreen*menu, float x1, float y1,Animation*normAnim, Animation*hoverAnim, Animation*clickAnim, String target);
				ImageMenuItem(MenuScreen*menu, float x1, float y1,Animation*anim, const Color&hoverColor, String target);
				ImageMenuItem(MenuScreen*menu, float x1, float y1,Animation*anim, const Color&hoverColor, const Color&clickColor, String target);
				virtual ~ImageMenuItem();

				void OnRelease();
				virtual void Draw(Graphics2D& g, long gameTime);
		};
		
		class MenuItem
		{
			friend class MenuScreen;
			private:
				TextMenuItem*textItem;
				ImageMenuItem*imageItem;
			
				unsigned char itemType;
				
				Sound*sound;
				
				MenuScreen*menuScreen;
				
			public:
				MenuItem(MenuScreen*menuScreen, TextMenuItem*textItem);
				MenuItem(MenuScreen*menuScreen, ImageMenuItem*imageItem);
				virtual ~MenuItem();

				void Update(long gameTime);
				void Draw(Graphics2D& g, long gameTime);

				bool MouseOver();
				void OnRelease();
				void setSelected(bool toggle);
				long getTouchId();
				bool selected();
				void setScale(float scale);
				void setRotation(float rotation);
				void setColor(const Color&color);
		};

		ArrayList<MenuItem*> Items;
		
	protected:
		int selectedIndex;
		bool selecting;
		bool soundEnabled;

	public:
		MenuScreen(String n);
		virtual ~MenuScreen();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D& g, long gameTime);

		//ImageMenuItem
		void addItem(float x1, float y1,Animation*normAnim, Animation*hoverAnim, String target);
		void addItem(float x1, float y1,Animation*normAnim, Animation*hoverAnim, Animation*clickAnim, String target);
		void addItem(float x1, float y1,Animation*anim, const Color&hoverColor, String target);
		void addItem(float x1, float y1,Animation*anim, const Color&hoverColor, const Color&clickColor, String target);
		void addItem(float x1, float y1,String normAnim, String hoverAnim, String target);
		void addItem(float x1, float y1,String normAnim, String hoverAnim, String clickAnim, String target);
		void addItem(float x1, float y1,String anim, const Color&hoverColor, String target);
		void addItem(float x1, float y1,String anim, const Color&hoverColor, const Color&clickColor, String target);

		//TextMenuItem
		void addItem(float x1, float y1, String s, Font*f, const Color&normC, const Color&hoverC, String target);
		void addItem(float x1, float y1, String s, Font*f, const Color&normC, const Color&hoverC, const Color&clickC, String target);

		void setItemScale(int index, float scale);
		void setItemRotation(int index, float degrees);
		void setItemColor(int index, const Color&c);
		void setItemSound(int index, Sound*sound);
		
		void enableSound(bool toggle);
	};
}