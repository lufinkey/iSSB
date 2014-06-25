
#include "../../GameEngine/GameEngine.h"

#pragma once

namespace SmashBros
{
	class WinnerScreen : public Screen
	{
	public:
		WinnerScreen(const String&name);
		virtual ~WinnerScreen();

		virtual void Initialize();
		virtual void LoadContent();
		virtual void UnloadContent();
		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);

	private:
		boolean addFile(String fileName);

		class CharStat
		{
		public:
			float x,y;
			int pNum,cNum,team,place,teamplace,score,ko,death;

			CharStat(WinnerScreen*screen, int pNum, int team, int place, int teamplace, int score, int ko, int death);
			~CharStat();

			void Update(long gameTime);
			void Draw(Graphics2D&g, long gameTime);
			String getTeamString(int teamNum);
			String getPlaceString(int placeNum);
			String toString();
			operator String();

		private:
			class CharStatPlayer : public Actor
			{
			public:
				CharStatPlayer(float x1, float y1);
				~CharStatPlayer();
				virtual void onAnimationFinish(const String&name);
			};

			CharStatPlayer*playr;
			TextActor*description;
		};

		class FinishButton : public Actor
		{
		public:
			FinishButton(float x1, float y1);
			~FinishButton();

			virtual void onMouseEnter();
			virtual void onMouseLeave();
			virtual void onRelease();
		};

		ArrayList<CharStat*> stats;
		ArrayList<String> files;

		FinishButton*button_finish;
	};
}