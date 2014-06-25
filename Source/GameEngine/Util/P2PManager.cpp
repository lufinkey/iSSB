
#include "P2PManager.h"
#include "../Application.h"
#include "CPPBridge.h"
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
		for(int i=0; i<size; i++)
		{
			buffer[i] = copy[i];
		}
		int r = *((int*)buffer);
		delete[] buffer;
		return r;
	}
	
	long DataVoid::toLong(void*data)
	{
		unsigned int size = sizeof(long);
		unsigned char*buffer = new unsigned char[size];
		unsigned char*copy = (unsigned char*)data;
		for(int i=0; i<size; i++)
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
		for(int i=0; i<size; i++)
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
		for(int i=0; i<size; i++)
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
	
	int P2P_SendDataHandler(void*data)
	{
		GameEngine_DataPacket*packet = (GameEngine_DataPacket*)data;
		
		if(packet->peers.size()>0) //specific peers
		{
			char**peerList = new char*[packet->peers.size()];
			for(unsigned int i=0; i<packet->peers.size(); i++)
			{
				peerList[i] = (char*)packet->peers.get(i);
			}
			if(packet->mode == P2PManager::SENDDATA_RELIABLE)
			{
				SDL_P2P_sendDataToPeers(Application::getWindow(), peerList, packet->peers.size(), packet->data.getData(), packet->data.length(), SDL_P2P_SENDDATA_RELIABLE);
			}
			else if(packet->mode == P2PManager::SENDDATA_UNRELIABLE)
			{
				SDL_P2P_sendDataToPeers(Application::getWindow(), peerList, packet->peers.size(), packet->data.getData(), packet->data.length(), SDL_P2P_SENDDATA_UNRELIABLE);
			}
			delete[] peerList;
		}
		else //all peers
		{
			if(packet->mode == P2PManager::SENDDATA_RELIABLE)
			{
				SDL_P2P_sendData(Application::getWindow(), packet->data.getData(), packet->data.length(), SDL_P2P_SENDDATA_RELIABLE);
			}
			else if(packet->mode == P2PManager::SENDDATA_UNRELIABLE)
			{
				SDL_P2P_sendData(Application::getWindow(), packet->data.getData(), packet->data.length(), SDL_P2P_SENDDATA_UNRELIABLE);
			}
			P2PManager::sendingData = false;
		}
		delete packet;
		return 0;
	}
	
	void P2P_EventHandler(SDL_P2P_Event*event)
	{
		if(P2PManager::eventListener != NULL)
		{
			switch(event->type)
			{
				case SDL_P2P_PEERCONNECTED:
				{
					char buffer[40];
					SDL_P2P_getSelfID(Application::getWindow(), buffer);
					P2PManager::selfInfo.id = buffer;
					SDL_P2P_getSelfDisplayName(Application::getWindow(), buffer);
					P2PManager::selfInfo.name = buffer;
					P2PManager::Peer peer = {event->peer.peerID, event->peer.peerDisplayName};
					while(P2PManager::lockPeerList);
					P2PManager::lockPeerList = true;
					P2PManager::peers.add(peer);
					P2PManager::lockPeerList = false;
					P2PManager::eventListener->peerDidConnect(event->peer.peerID);
					P2PManager::pickerIsOpen = false;
				}
				break;
				
				case SDL_P2P_PEERDISCONNECTED:
				{
					String peerID = event->peer.peerID;
					while(P2PManager::lockPeerList);
					P2PManager::lockPeerList = true;
					for(int i=0; i<P2PManager::peers.size(); i++)
					{
						if(P2PManager::peers.get(i).id.equals(peerID))
						{
							P2PManager::peers.remove(i);
							i = P2PManager::peers.size();
						}
					}
					P2PManager::lockPeerList = false;
					P2PManager::eventListener->peerDidDisconnect(peerID);
				}
				break;
				
				case SDL_P2P_PEERREQUESTEDCONNECTION:
				{
					P2PRequest*request = new P2PRequest(event->peer.peerID);
					P2PManager::eventListener->peerDidRequestConnection(request);
					delete request;
				}
				break;
				
				case SDL_P2P_PICKERDIDCANCEL:
				{
					P2PManager::eventListener->pickerDidCancel();
					P2PManager::pickerIsOpen = false;
				}
				break;
				
				case SDL_P2P_RECIEVEDDATA:
				{
					P2PManager::eventListener->didRecieveData(event->peer.peerID, event->data.data, event->data.size);
				}
				break;
			}
		}
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
		if(!handled)
		{
			SDL_bool success = SDL_P2P_acceptConnectionRequest(Application::getWindow(), peerID);
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
	}
	
	void P2PRequest::deny()
	{
		if(!handled)
		{
			SDL_P2P_denyConnectionRequest(Application::getWindow(), peerID);
			handled = true;
			connected = false;
		}
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
	
	bool P2PManager::lockPeerList = false;
	P2PManager::Peer P2PManager::selfInfo = {"",""};
	ArrayList<P2PManager::Peer> P2PManager::peers = ArrayList<P2PManager::Peer>();
	P2PEventListener*P2PManager::eventListener = NULL;
	String P2PManager::sessionID = "com.yourcompany.gameengine";
	bool P2PManager::pickerIsOpen = false;
	bool P2PManager::copyingPacket = false;
	bool P2PManager::sendingData = false;
	
	void P2PManager::Update(long gameTime)
	{
		if(SDL_P2P_isConnected(Application::getWindow()))
		{
			updateAppEvents();
		}
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
		SDL_P2P_setEventHandler(P2P_EventHandler);
		if(!SDL_P2P_isConnected(Application::getWindow()) && !pickerIsOpen)
		{
			pickerIsOpen = true;
			SDL_P2P_searchForPeersBluetooth(Application::getWindow(), sessionID);
			while(pickerIsOpen)
			{
				SDL_Delay(30);
				updateAppEvents();
			}
			if(SDL_P2P_isConnected(Application::getWindow()))
			{
				return true;
			}
		}
		return false;
	}
	
	bool P2PManager::isConnected()
	{
		if(SDL_P2P_isConnected(Application::getWindow()))
		{
			return true;
		}
		return false;
	}
	
	bool P2PManager::isConnectedToPeer(const String&peerID)
	{
		if(SDL_P2P_isConnectedToPeer(Application::getWindow(), peerID))
		{
			return true;
		}
		return false;
	}
	
	void P2PManager::disconnectPeer(const String&peerID)
	{
		if(SDL_P2P_isConnectedToPeer(Application::getWindow(), peerID))
		{
			SDL_P2P_disconnectPeer(Application::getWindow(), peerID);
		}
	}
	
	void P2PManager::endSession()
	{
		SDL_P2P_endSession(Application::getWindow());
	}
	
	ArrayList<String> P2PManager::getPeers()
	{
		while(lockPeerList);
		lockPeerList = true;
		ArrayList<String> peerList;
		for(int i=0; i<peers.size(); i++)
		{
			peerList.add(peers.get(i).id);
		}
		lockPeerList = false;
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
		while(lockPeerList);
		lockPeerList = true;
		for(unsigned int i=0; i<peers.size(); i++)
		{
			Peer&peer = peers.get(i);
			if(peer.id.equals(peerID))
			{
				String displayName = peer.name;
				lockPeerList = false;
				return displayName;
			}
		}
		lockPeerList = false;
		char buffer[40];
		SDL_P2P_getPeerDisplayName(Application::getWindow(), (char*)peerID, buffer);
		String displayName = buffer;
		return displayName;
	}
	
	void P2PManager::setEventListener(P2PEventListener*listener)
	{
		eventListener = listener;
	}
	
	void P2PManager::sendData(void*data, unsigned int size, Byte sendDataMode)
	{
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
			SDL_P2P_sendData(Application::getWindow(), data, size, SDL_P2P_SENDDATA_RELIABLE);
		}
		else if(sendDataMode == SENDDATA_UNRELIABLE)
		{
			GameEngine_DataPacket*packet = new GameEngine_DataPacket();
			packet->data.setData(data,size);
			packet->mode = sendDataMode;
			
			SDL_CreateThread(&P2P_SendDataHandler, "SendData", (void*)packet);
		}
	}
	
	void P2PManager::sendDataToPeers(const ArrayList<String>&peers, void*data, unsigned int size, Byte sendDataMode)
	{
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
			for(unsigned int i=0; i<peers.size(); i++)
			{
				peerList[i] = (char*)peers.get(i);
			}
			SDL_P2P_sendDataToPeers(Application::getWindow(), peerList, peers.size(), data, size, SDL_P2P_SENDDATA_RELIABLE);
		}
		else if(sendDataMode == SENDDATA_UNRELIABLE)
		{
			GameEngine_DataPacket*packet = new GameEngine_DataPacket();
			packet->data.setData(data,size);
			packet->peers = peers;
			packet->mode = sendDataMode;
			
			SDL_CreateThread(&P2P_SendDataHandler, "SendData", (void*)(packet));
		}
	}
}