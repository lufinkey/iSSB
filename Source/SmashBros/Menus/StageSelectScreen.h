
#include "MenuPieces/ActorGrid.h"

#pragma once

namespace SmashBros
{
	class StageSelectScreen : public Screen
	{
	private:
		ActorGrid*stageGrid;
		byte queueLoad;
		boolean drawnOnce;
		Actor*loadScreen;

		class StageIcon : public Actor
		{
		private:
			int num;
			StageSelectScreen*screen;

		public:
			StageIcon(StageSelectScreen*screen, float x1, float y1, int num);
			virtual ~StageIcon();

			virtual void onMouseEnter();
			virtual void onMouseLeave();
			virtual void onRelease();
		};
		
#ifndef SMASHBROS_SCRIPT_DISABLE
		ArrayList<Actor*> scriptStageIcons;
		
	protected:
		void unloadScriptedStages();
		void reloadScriptedStages();
#endif //SMASHBROS_SCRIPT_DISABLE
		
	public:
		StageSelectScreen(const String&name);
		virtual ~StageSelectScreen();

		virtual void onLoad();
		virtual void onSelect(int stageNo);
		virtual void onGoToGame();
		
		virtual void LoadContent();
		virtual void UnloadContent();
		
		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
	};
}