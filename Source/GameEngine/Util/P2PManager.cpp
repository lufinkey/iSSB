
#include "P2PManager.h"
#include "../Application.h"
#include "../CodeBridge/CPPBridge.h"
#include "../Output/Console.h"

namespace GameEngine
{
	DataVoid::DataVoid()
	{
		dataBytes = NULL;
		total = 0;
	}
	
	DataVoid::DataVoid(unsigned int size)
	{
		dataBytes = (Byte*)malloc(size);
		for(unsigned int i=0; i<size; i++)
		{
			dataBytes[i] = 0;
		}
		total = size;
	}
	
	DataVoid::DataVoid(void*data, unsigned int size)
	{
		if(size>0)
		{
			dataBytes = (Byte*)malloc(size);
			Byte*copyBytes = (Byte*)data;
			for(unsigned int i=0; i<size; i++)
			{
				dataBytes[i] = copyBytes[i];
			}
			total = size;
		}
		else
		{
			dataBytes = NULL;
			total = 0;
		}
	}
	
	DataVoid::DataVoid(const DataVoid&data)
	{
		if(data.dataBytes == NULL)
		{
			dataBytes = NULL;
			total = 0;
		}
		else
		{
			dataBytes = (Byte*)malloc(data.total);
			for(unsigned int i=0; i<data.total; i++)
			{
				dataBytes[i] = data.dataBytes[i];
			}
			total = data.total;
		}
	}
	
	DataVoid::~DataVoid()
	{
		if(dataBytes!=NULL)
		{
			free(dataBytes);
			dataBytes = NULL;
			total = 0;
		}
	}
	
	void*DataVoid::getData()
	{
		return (void*)dataBytes;
	}
	
	unsigned int DataVoid::length()
	{
		return total;
	}
	
	void DataVoid::resize(unsigned int size)
	{
		if(size > 0)
		{
			if(dataBytes==NULL)
			{
				dataBytes = (Byte*)malloc(size);
				for(unsigned int i=0; i<size; i++)
				{
					dataBytes[i] = 0;
				}
				total = size;
			}
			else
			{
				dataBytes = (Byte*)realloc(dataBytes, size);
				if(size>total)
				{
					for(unsigned int i=total; i<size; i++)
					{
						dataBytes[i] = 0;
					}
				}
				total = size;
			}
		}
		else
		{
			if(dataBytes!=NULL)
			{
				free(dataBytes);
				dataBytes = NULL;
				total = 0;
			}
		}
	}
	
	void DataVoid::clear()
	{
		if(dataBytes!=NULL)
		{
			free(dataBytes);
			dataBytes = NULL;
			total = 0;
		}
	}
	
	void DataVoid::add(void*data, unsigned int size)
	{
		if(dataBytes == NULL)
		{
			dataBytes = (Byte*)malloc(size);
			Byte*copyBytes = (Byte*)data;
			for(unsigned int i=0; i<size; i++)
			{
				dataBytes[i] = copyBytes[i];
			}
			total = size;
		}
		else
		{
			unsigned int total2 = total + size;
			dataBytes = (Byte*)realloc(dataBytes, total2);
			Byte*copyBytes = (Byte*)data;
			unsigned int counter = 0;
			for(unsigned int i=total; i<total2; i++)
			{
				dataBytes[i] = copyBytes[counter];
				counter++;
			}
			total = total2;
		}
	}
	
	void DataVoid::add(unsigned int ByteIndex, void*data, unsigned int size)
	{
		if(dataBytes == NULL)
		{
			if(ByteIndex == 0)
			{
				dataBytes = (Byte*)malloc(size);
				Byte*copyBytes = (Byte*)data;
				for(unsigned int i=0; i<size; i++)
				{
					dataBytes[i] = copyBytes[i];
				}
				total = size;
			}
			else
			{
				//error
				throw ((char*)((String)"ByteIndex " + ByteIndex + " out of bounds. DataVoid length is 0"));
			}
		}
		else if(ByteIndex <= total)
		{
			unsigned int total2 = total+size;
			dataBytes = (Byte*)realloc(dataBytes, total2);
			Byte*copyBytes = (Byte*)data;
			unsigned int counter = ByteIndex;
			for(unsigned int i=(total2-1); i>ByteIndex; i--)
			{
				dataBytes[i] = dataBytes[i-1];
			}
			counter = ByteIndex;
			for(unsigned int i=0; i<size; i++)
			{
				dataBytes[ByteIndex] = copyBytes[i];
				counter++;
			}
			total = total2;
		}
		else
		{
			//error
			throw ((char*)((String)"ByteIndex " + ByteIndex + " out of bounds. DataVoid length is " + total));
		}
	}
	
	void DataVoid::add(const DataVoid&data)
	{
		if(dataBytes == NULL)
		{
			dataBytes = (Byte*)malloc(data.total);
			for(unsigned int i=0; i<data.total; i++)
			{
				dataBytes[i] = data.dataBytes[i];
			}
			total = data.total;
		}
		else
		{
			unsigned int total2 = total + data.total;
			dataBytes = (Byte*)realloc(dataBytes, total2);
			unsigned int counter = 0;
			for(unsigned int i=total; i<total2; i++)
			{
				dataBytes[i] = data.dataBytes[counter];
				counter++;
			}
			total = total2;
		}
	}
	
	void DataVoid::add(unsigned int ByteIndex, const DataVoid&data)
	{
		if(dataBytes == NULL)
		{
			if(ByteIndex == 0)
			{
				dataBytes = (Byte*)malloc(data.total);
				for(unsigned int i=0; i<data.total; i++)
				{
					dataBytes[i] = data.dataBytes[i];
				}
				total = data.total;
			}
			else
			{
				//error
				throw ((char*)((String)"ByteIndex " + ByteIndex + " out of bounds. DataVoid length is 0"));
			}
		}
		else if(ByteIndex <= total)
		{
			unsigned int total2 = total+data.total;
			dataBytes = (Byte*)realloc(dataBytes, total2);
			unsigned int counter = ByteIndex;
			for(unsigned int i=(total2-1); i>ByteIndex; i--)
			{
				dataBytes[i] = dataBytes[i-1];
			}
			counter = ByteIndex;
			for(unsigned int i=0; i<data.total; i++)
			{
				dataBytes[ByteIndex] = data.dataBytes[i];
				counter++;
			}
			total = total2;
		}
		else
		{
			//error
			throw ((char*)((String)"ByteIndex " + ByteIndex + " out of bounds. DataVoid length is " + total));
		}
	}
	
	void DataVoid::addByte(Byte dataByte)
	{
		if(dataBytes == NULL)
		{
			dataBytes = (Byte*)malloc(1);
			dataBytes[0] = dataByte;
			total = 1;
		}
		else
		{
			dataBytes = (Byte*)realloc(dataBytes, total+1);
			dataBytes[total] = dataByte;
			total += 1;
		}
	}
	
	void DataVoid::addByte(unsigned int ByteIndex, Byte dataByte)
	{
		if(dataBytes == NULL)
		{
			if(ByteIndex == 0)
			{
				dataBytes = (Byte*)malloc(1);
				dataBytes[0] = dataByte;
				total = 1;
			}
			else
			{
				//error
				throw ((char*)((String)"ByteIndex " + ByteIndex + " out of bounds. DataVoid length is 0"));
			}
		}
		else if(ByteIndex <= total)
		{
			unsigned int total2 = total+1;
			dataBytes = (Byte*)realloc(dataBytes, total2);
			for(unsigned int i=(total2-1); i>ByteIndex; i--)
			{
				dataBytes[i] = dataBytes[i-1];
			}
			dataBytes[ByteIndex] = dataByte;
			total = total2;
		}
		else
		{
			//error
			throw ((char*)((String)"ByteIndex " + ByteIndex + " out of bounds. DataVoid length is " + total));
		}
	}
	
	void DataVoid::remove(unsigned int ByteIndex, unsigned int size)
	{
		if(dataBytes==NULL)
		{
			throw ((char*)((String)"ByteIndex " + ByteIndex + " and size " + size + " out of bounds. DataVoid length is 0"));
		}
		else if(ByteIndex<total && (ByteIndex+size)<=total)
		{
			unsigned int endOfRemove = ByteIndex+size;
			unsigned int counter = ByteIndex;
			for(unsigned int i=endOfRemove; i<total; i++)
			{
				dataBytes[counter] = dataBytes[i];
				counter++;
			}
			unsigned int total2 = total - size;
			dataBytes = (Byte*)realloc(dataBytes, total2);
			total = total2;
		}
		else
		{
			throw ((char*)((String)"ByteIndex " + ByteIndex + " and size " + size + " out of bounds. DataVoid length is " + total));
		}
	}
	
	void DataVoid::removeByte(unsigned int ByteIndex)
	{
		if(dataBytes == NULL)
		{
			throw ((char*)((String)"ByteIndex " + ByteIndex + " out of bounds. DataVoid length is 0"));
		}
		else if(ByteIndex<total)
		{
			unsigned int endOfRemove = ByteIndex+1;
			unsigned int counter = ByteIndex;
			for(unsigned int i=endOfRemove; i<total; i++)
			{
				dataBytes[counter] = dataBytes[i];
				counter++;
			}
			unsigned int total2 = total - 1;
			dataBytes = (Byte*)realloc(dataBytes, total2);
			total = total2;
		}
		else
		{
			throw ((char*)((String)"ByteIndex " + ByteIndex + " out of bounds. DataVoid length is " + total));
		}
	}
	
	void DataVoid::set(unsigned int ByteIndex, void*data, unsigned int size)
	{
		if(dataBytes == NULL)
		{
			throw ((char*)((String)"ByteIndex " + ByteIndex + " and size " + size + " out of bounds. DataVoid length is 0"));
		}
		else if(ByteIndex<total && (ByteIndex+size)<=total)
		{
			Byte*copyBytes = (Byte*)data;
			unsigned int counter = ByteIndex;
			for(unsigned int i=0; i<size; i++)
			{
				dataBytes[counter] = copyBytes[i];
			}
		}
		else
		{
			throw ((char*)((String)"ByteIndex " + ByteIndex + " and size " + size + " out of bounds. DataVoid length is " + total));
		}
	}
	
	void DataVoid::set(unsigned int ByteIndex, const DataVoid&data)
	{
		if(dataBytes == NULL)
		{
			throw ((char*)((String)"ByteIndex " + ByteIndex + " and data size " + data.total + " out of bounds. DataVoid length is 0"));
		}
		else if(ByteIndex<total && (ByteIndex+data.total)<=total)
		{
			unsigned int counter = ByteIndex;
			for(unsigned int i=0; i<data.total; i++)
			{
				dataBytes[counter] = data.dataBytes[i];
				counter++;
			}
		}
		else
		{
			throw ((char*)((String)"ByteIndex " + ByteIndex + " and data size " + data.total + " out of bounds. DataVoid length is " + total));
		}
	}
	
	void DataVoid::setByte(unsigned int ByteIndex, Byte dataByte)
	{
		if(dataBytes == NULL)
		{
			throw ((char*)((String)"ByteIndex " + ByteIndex + " out of bounds. DataVoid length is 0"));
		}
		else if(ByteIndex<total)
		{
			dataBytes[ByteIndex] = dataByte;
		}
		else
		{
			throw ((char*)((String)"ByteIndex " + ByteIndex + " out of bounds. DataVoid length is " + total));
		}
	}
	
	void*DataVoid::get(unsigned int ByteIndex)
	{
		if(dataBytes==NULL)
		{
			return NULL;
		}
		else
		{
			return (void*)(dataBytes + ByteIndex);
		}
	}
	
	Byte DataVoid::getByte(unsigned int ByteIndex)
	{
		if(dataBytes==NULL)
		{
			return 0;
		}
		else
		{
			return dataBytes[ByteIndex];
		}
	}
	
	DataVoid DataVoid::copy(unsigned int ByteIndex, unsigned int size)
	{
		if(dataBytes == NULL)
		{
			throw ((char*)((String)"ByteIndex " + ByteIndex + " and size " + size + " out of bounds. DataVoid length is 0"));
		}
		else if(ByteIndex<total && (ByteIndex+size)<=total)
		{
			return DataVoid((void*)(dataBytes + ByteIndex), size);
		}
		else
		{
			throw ((char*)((String)"ByteIndex " + ByteIndex + " and size " + size + " out of bounds. DataVoid length is " + total));
		}
		return DataVoid();
	}
	
	void DataVoid::setData(void*data, unsigned int size)
	{
		if(dataBytes!=NULL)
		{
			free(dataBytes);
			dataBytes = NULL;
			total = 0;
		}
		dataBytes = (Byte*)malloc(size);
		Byte*copyBytes = (Byte*)data;
		for(unsigned int i=0; i<size; i++)
		{
			dataBytes[i] = copyBytes[i];
		}
		total = size;
	}
	
	int DataVoid::toInt(void*data)
	{
		unsigned int size = sizeof(int);
		unsigned char*buffer = new unsigned char[size];
		unsigned char*copy = (unsigned char*)data;
		for(unsigned int i=0; i<size; i++)
		{
			buffer[i] = copy[i];
		}
		int r = *((int*)buffer);
		delete[] buffer;
		return r;
	}

	bool DataVoid::toBool(void*data)
	{
		bool*buffer = (bool*)data;
		return buffer[0];
	}
	
	long DataVoid::toLong(void*data)
	{
		unsigned int size = sizeof(long);
		unsigned char*buffer = new unsigned char[size];
		unsigned char*copy = (unsigned char*)data;
		for(unsigned int i=0; i<size; i++)
		{
			buffer[i] = copy[i];
		}
		long r = *((long*)buffer);
		delete[] buffer;
		return r;
	}
	
	float DataVoid::toFloat(void*data)
	{
		unsigned int size = sizeof(float);
		unsigned char*buffer = new unsigned char[size];
		unsigned char*copy = (unsigned char*)data;
		for(unsigned int i=0; i<size; i++)
		{
			buffer[i] = copy[i];
		}
		float r = *((float*)buffer);
		delete[] buffer;
		return r;
	}
	
	double DataVoid::toDouble(void*data)
	{
		unsigned int size = sizeof(double);
		unsigned char*buffer = new unsigned char[size];
		unsigned char*copy = (unsigned char*)data;
		for(unsigned int i=0; i<size; i++)
		{
			buffer[i] = copy[i];
		}
		double r = *((double*)buffer);
		delete[] buffer;
		return r;
	}
	
	typedef struct
	{
		DataVoid data;
		ArrayList<String> peers;
		Byte mode;
	} GameEngine_DataPacket;
	
	int P2PManager_SendDataHandler(void*data)
	{
#if defined(SMASHBROS_P2P_DISABLE)
		return -1;
#else
		GameEngine_DataPacket*packet = (GameEngine_DataPacket*)data;
		
		if(packet->peers.size()>0) //specific peers
		{
			char**peerList = new char*[packet->peers.size()];
			for(int i=0; i<packet->peers.size(); i++)
			{
				peerList[i] = (char*)packet->peers.get(i);
			}
			if(packet->mode == P2PManager::SENDDATA_RELIABLE)
			{
				P2P_sendDataToPeers(P2PManager::session, peerList, packet->peers.size(), packet->data.getData(), packet->data.length(), P2P_SENDDATA_RELIABLE);
			}
			else if(packet->mode == P2PManager::SENDDATA_UNRELIABLE)
			{
				P2P_sendDataToPeers(P2PManager::session, peerList, packet->peers.size(), packet->data.getData(), packet->data.length(), P2P_SENDDATA_UNRELIABLE);
			}
			delete[] peerList;
		}
		else //all peers
		{
			if(packet->mode == P2PManager::SENDDATA_RELIABLE)
			{
				P2P_sendData(P2PManager::session, packet->data.getData(), packet->data.length(), P2P_SENDDATA_RELIABLE);
			}
			else if(packet->mode == P2PManager::SENDDATA_UNRELIABLE)
			{
				P2P_sendData(P2PManager::session, packet->data.getData(), packet->data.length(), P2P_SENDDATA_UNRELIABLE);
			}
			P2PManager::sendingData = false;
		}
		delete packet;
		return 0;
#endif
	}
	
	void P2PManager_EventHandler(P2P_Event*event)
	{
#ifndef SMASHBROS_P2P_DISABLE
		if(P2PManager::eventListener != NULL)
		{
			switch(event->type)
			{
				case P2P_PEERCONNECTED:
				{
					char buffer[40];
					P2P_getSelfID(P2PManager::session, buffer);
					P2PManager::selfInfo.id = buffer;
					P2P_getSelfDisplayName(P2PManager::session, buffer);
					P2PManager::selfInfo.name = buffer;
					P2PManager::Peer peer = {event->peer.peerID, event->peer.peerDisplayName};
					P2PManager::peers_mutex.lock();
					P2PManager::peers.add(peer);
					P2PManager::peers_mutex.unlock();
					P2PManager::eventListener->peerDidConnect(event->peer.peerID);
					P2PManager::pickerIsOpen = false;
				}
				break;
				
				case P2P_PEERDISCONNECTED:
				{
					String peerID = event->peer.peerID;
					P2PManager::peers_mutex.lock();
					for(int i=0; i<P2PManager::peers.size(); i++)
					{
						if(P2PManager::peers.get(i).id.equals(peerID))
						{
							P2PManager::peers.remove(i);
							i = P2PManager::peers.size();
						}
					}
					P2PManager::peers_mutex.unlock();
					P2PManager::eventListener->peerDidDisconnect(peerID);
				}
				break;
				
				case P2P_PEERREQUESTEDCONNECTION:
				{
					P2PRequest*request = new P2PRequest(event->peer.peerID);
					P2PManager::eventListener->peerDidRequestConnection(request);
					delete request;
				}
				break;
				
				case P2P_PICKERDIDCANCEL:
				{
					P2PManager::eventListener->pickerDidCancel();
					P2PManager::pickerIsOpen = false;
				}
				break;
				
				case P2P_RECIEVEDDATA:
				{
					P2PManager::eventListener->didRecieveData(event->peer.peerID, event->data.data, event->data.size);
				}
				break;
			}
		}
#endif
	}
	
	P2PRequest::P2PRequest(const String&peerID)
	{
		this->peerID = peerID;
		handled = false;
		connected = false;
	}
	
	P2PRequest::~P2PRequest()
	{
		//
	}
	
	String P2PRequest::getPeerID()
	{
		return peerID;
	}
	
	bool P2PRequest::accept()
	{
#if defined(SMASHBROS_P2P_DISABLE)
		return false;
#else
		if(!handled)
		{
			SDL_bool success = P2P_acceptConnectionRequest(P2PManager::session, peerID);
			if(success)
			{
				handled = true;
				connected = true;
				return true;
			}
			connected = false;
			return false;
		}
		return connected;
#endif
	}
	
	void P2PRequest::deny()
	{
#ifndef SMASHBROS_P2P_DISABLE
		if(!handled)
		{
			P2P_denyConnectionRequest(P2PManager::session, peerID);
			handled = true;
			connected = false;
		}
#endif
	}
	
	P2PEventListener::P2PEventListener()
	{
		//Open for implementation
	}
	
	P2PEventListener::~P2PEventListener()
	{
		//Open for implementation
	}
	
	void P2PEventListener::peerDidConnect(String peerID)
	{
		//Open for implementation
	}
	
	void P2PEventListener::peerDidDisconnect(String peerID)
	{
		//Open for implementation
	}
	
	void P2PEventListener::peerDidRequestConnection(P2PRequest*request)
	{
		//Open for implementation
	}
	
	void P2PEventListener::pickerDidCancel()
	{
		//Open for implementation
	}
	
	void P2PEventListener::didRecieveData(String peerID, void*data, unsigned int size)
	{
		//Open for implementation
	}
	
	P2PManager::Peer P2PManager::selfInfo = {"",""};
	ArrayList<P2PManager::Peer> P2PManager::peers = ArrayList<P2PManager::Peer>();
	std::mutex P2PManager::peers_mutex;
	P2PEventListener*P2PManager::eventListener = NULL;
	String P2PManager::sessionID = "com.yourcompany.gameengine";
	P2P_Session* P2PManager::session = NULL;
	bool P2PManager::pickerIsOpen = false;
	bool P2PManager::copyingPacket = false;
	bool P2PManager::sendingData = false;
	
	void P2PManager::Update(long gameTime)
	{
#ifndef SMASHBROS_P2P_DISABLE
		if(session!=NULL && P2P_isConnected(session))
		{
			updateAppEvents();
		}
#endif
	}
	
	void P2PManager::Draw(Graphics2D&g, long gameTime)
	{
		//possibly draw bluetooth symbol
	}
	
	void P2PManager::setSessionID(const String&sessionID)
	{
		P2PManager::sessionID = sessionID;
	}
	
	String P2PManager::getSessionID()
	{
		return sessionID;
	}
	
	bool P2PManager::searchForPeers()
	{
#if defined(SMASHBROS_P2P_DISABLE)
		return false;
#else
		if(session==NULL)
		{
			session = P2P_createSession();
			P2P_setEventHandler(session, P2PManager_EventHandler);
			pickerIsOpen = true;
			P2P_searchForPeers(session, sessionID);
			while(pickerIsOpen)
			{
				SDL_Delay(30);
				updateAppEvents();
			}
			if(P2P_isConnected(session))
			{
				return true;
			}
		}
		return false;
#endif
	}
	
	bool P2PManager::isConnected()
	{
#if defined(SMASHBROS_P2P_DISABLE)
		return false;
#else
		if(session!=NULL && P2P_isConnected(session))
		{
			return true;
		}
		return false;
#endif
	}
	
	bool P2PManager::isConnectedToPeer(const String&peerID)
	{
#if defined(SMASHBROS_P2P_DISABLE)
		return false;
#else
		if(session!=NULL && P2P_isConnectedToPeer(session, peerID))
		{
			return true;
		}
		return false;
#endif
	}
	
	void P2PManager::disconnectPeer(const String&peerID)
	{
#ifndef SMASHBROS_P2P_DISABLE
		if(session!=NULL && P2P_isConnectedToPeer(session, peerID))
		{
			P2P_disconnectPeer(session, peerID);
		}
#endif
	}
	
	void P2PManager::endSession()
	{
#ifndef SMASHBROS_P2P_DISABLE
		if(session!=NULL)
		{
			P2P_endSession(session);
			P2P_destroySession(session);
			session = NULL;
		}
#endif
	}
	
	ArrayList<String> P2PManager::getPeers()
	{
		peers_mutex.lock();
		ArrayList<String> peerList;
		for(int i=0; i<peers.size(); i++)
		{
			peerList.add(peers.get(i).id);
		}
		peers_mutex.unlock();
		return peerList;
	}
	
	String P2PManager::getID()
	{
		return selfInfo.id;
	}
	
	String P2PManager::getDisplayName()
	{
		return selfInfo.name;
	}
	
	String P2PManager::getPeerDisplayName(const String&peerID)
	{
#if defined(SMASHBROS_P2P_DISABLE)
		return "Unknown";
#else
		peers_mutex.lock();
		for(int i=0; i<peers.size(); i++)
		{
			Peer&peer = peers.get(i);
			if(peer.id.equals(peerID))
			{
				String displayName = peer.name;
				peers_mutex.unlock();
				return displayName;
			}
		}
		peers_mutex.unlock();
		char buffer[40];
		P2P_getPeerDisplayName(session, (char*)peerID, buffer);
		String displayName = buffer;
		return displayName;
#endif
	}
	
	void P2PManager::setEventListener(P2PEventListener*listener)
	{
		eventListener = listener;
	}
	
	void P2PManager::sendData(void*data, unsigned int size, Byte sendDataMode)
	{
#ifndef SMASHBROS_P2P_DISABLE
		/*if(sendDataMode == SENDDATA_RELIABLE)
		{
			SDL_P2P_sendData(Application::getWindow(), data, size, SDL_P2P_SENDDATA_RELIABLE);
		}
		else if(sendDataMode == SENDDATA_UNRELIABLE)
		{
			SDL_P2P_sendData(Application::getWindow(), data, size, SDL_P2P_SENDDATA_UNRELIABLE);
		}*/
		
		if(sendDataMode == SENDDATA_RELIABLE)
		{
			P2P_sendData(session, data, size, P2P_SENDDATA_RELIABLE);
		}
		else if(sendDataMode == SENDDATA_UNRELIABLE)
		{
			GameEngine_DataPacket*packet = new GameEngine_DataPacket();
			packet->data.setData(data,size);
			packet->mode = sendDataMode;
			
			SDL_CreateThread(&P2PManager_SendDataHandler, "SendData", (void*)packet);
		}
#endif
	}
	
	void P2PManager::sendDataToPeers(const ArrayList<String>&peers, void*data, unsigned int size, Byte sendDataMode)
	{
#ifndef SMASHBROS_P2P_DISABLE
		/*char** peerList = new char*[peers.size()];
		for(unsigned int i=0; i<peers.size(); i++)
		{
			peerList[i] = (char*)peers.get(i);
		}
		if(sendDataMode == SENDDATA_RELIABLE)
		{
			SDL_P2P_sendDataToPeers(Application::getWindow(), peerList, peers.size(), data, size, SDL_P2P_SENDDATA_RELIABLE);
		}
		else if(sendDataMode == SENDDATA_UNRELIABLE)
		{
			SDL_P2P_sendDataToPeers(Application::getWindow(), peerList, peers.size(), data, size, SDL_P2P_SENDDATA_UNRELIABLE);
		}
		delete[] peerList;*/
		
		if(sendDataMode == SENDDATA_RELIABLE)
		{
			char** peerList = new char*[peers.size()];
			for(int i=0; i<peers.size(); i++)
			{
				peerList[i] = (char*)peers.get(i);
			}
			P2P_sendDataToPeers(session, peerList, peers.size(), data, size, P2P_SENDDATA_RELIABLE);
		}
		else if(sendDataMode == SENDDATA_UNRELIABLE)
		{
			GameEngine_DataPacket*packet = new GameEngine_DataPacket();
			packet->data.setData(data,size);
			packet->peers = peers;
			packet->mode = sendDataMode;
			
			SDL_CreateThread(&P2PManager_SendDataHandler, "SendData", (void*)(packet));
		}
#endif
	}
}