
#include "../Game.h"
#include "SmashForwards.h"
#include "Player.h"
#include "Stage.h"
#include "HUD.h"

#pragma once

namespace SmashBros
{
	class Global
	{
		friend class Game;
		friend class GameScreen;
	public:
		static const int possPlayers = 4;
		static const int possTeams = 4;
		
		static long worldTime;
		
		static int*players;
		
		static Player**characters;
		static byte*currentTeams;
		static int*scores;
		static int*KOs;
		static int*deaths;
		static int*winners;
		static int*teamWinners;
		static Stage*currentStage;

		static HUD*hud;

		static int charAmount;

		static int*selectedChar;
		static int selectedStage;
		
		static ArrayList<int> stageVotes;
		static boolean peerReadyToPlay;
		static boolean selfReadyToPlay;
		static boolean peerLoaded;
		static boolean selfLoaded;
		static String P2PMessage;

		static boolean gamePlaying;
		static boolean gameFinished;

		static boolean suddenDeath;
		static ArrayList<int> suddenDeathPlayers;

		static boolean smashBallOnField;
		static boolean playerHasSmashBall;

		static boolean*CPU;
		static int timeLimit;
		static int stockAmount;
		static int gameMode;
		static int gameType;
		static boolean teamBattle;
		static long timeAmount;

		static boolean*itemsOn;
		static ArrayList<int> itemsActive;

		static int maxLives;
		static int minLives;

		static int maxTime;
		static int minTime;
		
		static const int TYPE_TRAINING = 0;
		static const int TYPE_GROUPBRAWL = 1;
		
		static const int MODE_FREEFORALL = 0;
		static const int MODE_TIME_LIMIT = 1;
		static const int MODE_STOCK = 2;
		
		static const byte TEAM_RED = 1;
		static const byte TEAM_BLUE = 2;
		static const byte TEAM_GREEN = 3;
		static const byte TEAM_YELLOW = 4;
		
		static const int totalCharacters = 6;
		static const int totalItems = 6;
		static const int totalStages = 6;
		
		//CHARACTER CONSTANTS
		static const int CHAR_MARIO = 1;
		static const int CHAR_ICHIGO = 2;
		static const int CHAR_SONIC = 3;
		static const int CHAR_FOX = 4;
		static const int CHAR_PIKACHU = 5;
		static const int CHAR_LINK = 6;
		
		//STAGE CONSTANTS
		static const int STAGE_FRACTALSTAGE = 0;
		static const int STAGE_HILLSIDEBATTLEGROUND = 1;
		static const int STAGE_BATTLEFIELDBRAWL = 2;
		static const int STAGE_FINALDESTINATION = 3;
		static const int STAGE_HYRULETEMPLE = 4;
		static const int STAGE_CORNERIA = 5;
		static const int STAGE_WHOMPFORTRESS = 6;
		
		//ITEM CONSTANTS
		static const int ITEM_CUSTOM = 0;
		static const int ITEM_SMASHBALL = 1;
		static const int ITEM_RAYGUN = 2;
		static const int ITEM_HEARTCONTAINER = 3;
		static const int ITEM_BEAMSWORD = 4;
		static const int ITEM_SUPERMUSHROOM = 5;
		static const int ITEM_POISONMUSHROOM = 6;
		
		static void onReturnToMenu();
		
		static String getDirText(byte dir);
		static String getAddonsFolder();
		
		static long getWorldTime();
		
		static void Update(long gameTime);
		
		static String getPlayerName(int playerNo);
		
		static boolean isInSuddenDeath(byte playerNo);
		
		static void scorePoint(byte pNum);
		
		static void UnloadGame();
		static void LoadGame();
		
		static Player*getPlayerActor(int pNum);
		static String getItemName(int itemNo);
		
		static boolean checkWinners(byte pNum);
		
		static void finishBrawl();
		
		static void finishGame();
		static void finishGameSoloTraining();
		static void finishGameSuddenDeath();
		
	private:
		static void init();
		
		static void createHUD();
		
		static void createPlayers();
		
		static boolean checkWinnersFreeForAll(byte pNum);
		static boolean checkWinnersSuddenDeath(byte pNum);
		
		static void finishGameFreeForAll();
		static void finishGameTeam();
	};
}

