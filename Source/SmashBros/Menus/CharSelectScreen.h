
#include "../../GameEngine/GameEngine.h"

#pragma once

namespace SmashBros
{
	class CharSelectScreen : public Screen
	{
	private:
		class CharCoin : public Actor
		{
			friend class CharSelectScreen;
		private:
			CharSelectScreen*screen;
			boolean drag;
			long dragId;

		public:
			CharCoin(CharSelectScreen*screen,int num);
			virtual ~CharCoin();

			virtual void onClick();
			virtual void onRelease();
			virtual void Update(long gameTime);
		};

		class CharIcon : public Actor
		{
		public:
			int num;
			CharIcon(int num, float x1, float y1, Animation*anim);
			virtual ~CharIcon();
		};

		class CharCard : public Actor
		{
		private:
			int type;
			int num;
			CharSelectScreen*screen;

			class TeamFlag : public Actor
			{
			private:
				int num;
			public:
				TeamFlag(float x1, float y1, int num);
				virtual ~TeamFlag();
				virtual void onRelease();
			};

			TeamFlag*teamFlag;
		public:
			CharCard(CharSelectScreen*screen,float x1,float y1, int pNum, int type);
			virtual ~CharCard();

			virtual void onRelease();
			virtual void Update(long gameTime);
			virtual void Draw(Graphics2D&g, long gameTime);
		};

		ArrayList<Actor*> charCards;
		ArrayList<CharIcon*> charIcons;
		ArrayList<WireframeActor*> charIconPoints;
		ArrayList<CharCoin*> charCoins;
		ArrayList<Actor*> charPreviews;
		ArrayList<TextActor*> charNames;
		
		ArrayList<int> hiddenCoins;
		ArrayList<int> disabledCards;

		boolean canGrabCoin;
		int selectedCoin;
		WireframeActor*charSelectArea;

		Vector2i*coinPoints;
		byte*cardTypes;
		boolean*cardAvailable;

		void clickCharCard(int num);
		void clickCharCardFirstCPU(int num);
		void clickCharCardOnlyCPU(int num);
		void clickCharCardOnlyHMU(int num);
		void setCardAnimation(int num);
		void addCardAnimations(int num);
		void addToGrid(Actor*a,int x1,int y1,int xAmount,int yAmount,int xspace,int yspace,int num);
		Actor*setUpCard(int num, int cType);
		
		boolean coinHidden(int num);

	protected:
		void loadCharPreviews(int num);
		void selectCharacter(int player, int character);
		void selectRandomCharacter(int player);
		boolean checkReadyToFight(int minPlayers);
		boolean coinsClicked();
		void setCardType(int card, byte type);
		void hideCoin(int num, boolean toggle);
		void disableCardChange(int card);
		void enableCardChange(int card);
		boolean cardChangeDisabled(int card);
		void setCardState(int card, bool cardOn, bool cpu);
		void createCharCoins(int num);
		void newCharIcon(int num, String anim);
		void resetCards(ArrayList<int> type);
		
	public:
		CharSelectScreen(const String&name);
		virtual ~CharSelectScreen();

		virtual void Initialize();
		virtual void LoadContent();
		virtual void UnloadContent();
		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
		
		virtual void onSelectCharacter(int player, int character);
		
		void createCharIcons();
		void createCards(ArrayList<int> type);
	};
}