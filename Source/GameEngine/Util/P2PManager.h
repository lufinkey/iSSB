
#include "String.h"
#include "ArrayList.h"
#include "../Graphics/Graphics2D.h"
#include "Bitset.h"
#include <SDL_p2p.h>
#include <mutex>

#pragma once

namespace GameEngine
{
	class DataVoid
	{
		Byte*dataBytes;
		unsigned int total;
	public:
		DataVoid();
		DataVoid(unsigned int size);
		DataVoid(void*data, unsigned int size);
		DataVoid(const DataVoid&data);
		virtual ~DataVoid();
		
		void*getData();
		unsigned int length();
		
		void resize(unsigned int size);
		void clear();
		DataVoid copy(unsigned int byteIndex, unsigned int size);
		void setData(void*data, unsigned int size);
		
		void add(const void*data, unsigned int size);
		void add(unsigned int byteIndex, const void* data, unsigned int size);
		void remove(unsigned int byteIndex, unsigned int size);
		void set(unsigned int byteIndex, const void* data, unsigned int size);
		void*get(unsigned int byteIndex);
		
		void add(const DataVoid&data);
		void add(unsigned int byteIndex, const DataVoid&data);
		void set(unsigned int byteIndex, const DataVoid&data);
		
		void addByte(Byte dataByte);
		void addByte(unsigned int byteIndex, Byte dataByte);
		void removeByte(unsigned int byteIndex);
		void setByte(unsigned int byteIndex, Byte dataByte);
		Byte getByte(unsigned int byteIndex);
		
		static int toInt(void*data);
		static bool toBool(void*data);
		static long toLong(void*data);
		static float toFloat(void*data);
		static double toDouble(void*data);
	};
	
	class P2PRequest
	{
		friend void P2PManager_EventHandler(P2P_Event*event);
	private:
		String peerID;
		bool handled;
		bool connected;
		
		P2PRequest(const String&peerID);
		~P2PRequest();
		
	public:
		String getPeerID();
		bool accept();
		void deny();
	};
	
	class P2PEventListener
	{
	public:
		P2PEventListener();
		virtual ~P2PEventListener();
		virtual void peerDidConnect(String peerID);
		virtual void peerDidDisconnect(String peerID);
		virtual void peerDidRequestConnection(P2PRequest*request);
		virtual void pickerDidCancel();
		virtual void didRecieveData(String peerID, void*data, unsigned int size);
	};
	
	class P2PManager
	{
		friend void P2PManager_EventHandler(P2P_Event*event);
		friend int P2PManager_SendDataHandler(void*data);
		friend class P2PRequest;
	private:
		typedef struct
		{
			String id;
			String name;
		} Peer;
		
		static Peer selfInfo;
		static ArrayList<Peer> peers;
		static std::mutex peers_mutex;
		static String sessionID;
		static P2PEventListener*eventListener;
		static P2P_Session*session;
		
		static bool pickerIsOpen;
		
		static bool copyingPacket;
		static bool sendingData;
		
	public:
		static const unsigned char SENDDATA_RELIABLE = 0;
		static const unsigned char SENDDATA_UNRELIABLE = 1;
		
		static void Update(long gameTime);
		static void Draw(Graphics2D&g, long gameTime);
		
		static void setSessionID(const String&sessionID);
		static String getSessionID();
		
		static bool searchForPeers();
		static bool searchForClients();
		static bool searchForServer();
		
		static bool isConnected();
		static bool isConnectedToPeer(const String&peerID);
		
		static void disconnectPeer(const String&peerID);
		static void endSession();
		
		static ArrayList<String> getPeers();
		static String getID();
		static String getDisplayName();
		static String getPeerDisplayName(const String&peerID);
		
		static void setEventListener(P2PEventListener*listener);
		
		static void sendData(void*data, unsigned int size, unsigned char sendDataMode = SENDDATA_RELIABLE);
		static void sendDataToPeers(const ArrayList<String>&peers, void*data, unsigned int size, unsigned char sendDataMode = SENDDATA_RELIABLE);
	};
}