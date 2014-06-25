
#include "../GameEngine/GameEngine.h"
#include "SmashForwards.h"

namespace SmashBros
{
	class P2PDataManager
	{
		friend class Menus;
		friend class BluetoothMenu;
		friend class GameScreen;
	private:
		class P2PEvents : public P2PEventListener
		{
		public:
			P2PEvents();
			virtual ~P2PEvents();
			virtual void peerDidConnect(String peerID);
			virtual void peerDidDisconnect(String peerID);
			virtual void peerDidRequestConnection(P2PRequest*request);
			virtual void pickerDidCancel();
			virtual void didRecieveData(String peerID, void*data, unsigned int size);
		};
		
		static boolean needInfo;
		
		static boolean server;
		static String peerID;
		static String peerDevice;
		
		static boolean lockDataList;
		static ArrayList<DataVoid*> dataQueue;
		static P2PEvents*listener;
		
		static boolean enabled;
		
		static boolean reliable;
		static boolean errorstate;
		
		static long lastRecieveTime;
		
	public:
		static const byte DATA_INITIAL = 1;
		static const byte DATA_CHARSELECT = 2;
		static const byte DATA_RULES = 3;
		static const byte DATA_STARTGAME = 4;
		static const byte DATA_SELECTSTAGE = 5;
		static const byte DATA_LOADED = 6;
		static const byte DATA_READYGO = 7;
		static const byte DATA_GAMEDATA = 8;
		static const byte DATA_JOYSTICK = 9;
		static const byte DATA_UPDATESCORE = 10;
		
		static const byte RULES_ITEM = 0;
		static const byte RULES_TIMELIMIT = 1;
		static const byte RULES_STOCK = 2;
		static const byte RULES_MODE = 3;
		
		static const byte READYGO_GO = 0;
		static const byte READYGO_GAME = 1;
		
		static boolean connectToPeers();
		static boolean pollDataQueue(DataVoid*data);
		
		static String getPeerDevice();
		static String getPeerID();
		
		static boolean isServer();
		static boolean isEnabled();
		
		static void setReliable();
		static void setErrorState();
		
		static void toggleSetting(const String&setting, int value1);
		
		static void sendInitial();
		static void updateGame(long gameTime);
		
		static void sendScore(Player*playr, bool finished);
		
		static void serverHandleStart();
		static void handleLoaded();
		static void sendGameData();
	};
}