
#ifndef _P2P_H
#define _P2P_H

#include "SDL.h"

#include "begin_code.h"
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C"
{
#endif
	
	typedef struct P2P_Session P2P_Session;
	
	typedef enum
	{
		P2P_PEERCONNECTED = 1,
		P2P_PEERDISCONNECTED = 2,
		P2P_PEERREQUESTEDCONNECTION = 3,
		P2P_PICKERDIDCANCEL = 4,
		P2P_RECIEVEDDATA = 5
	} P2P_EventType;
	
	struct P2P_PeerInfo
	{
		char*peerID;
		char*peerDisplayName;
	};
	
	struct P2P_DataInfo
	{
		void*data;
		unsigned int size;
	};
	
	typedef struct
	{
		P2P_EventType type;
		struct P2P_PeerInfo peer;
		struct P2P_DataInfo data;
	} P2P_Event;
	
	typedef void (*P2P_EventHandler)(P2P_Event*);
	
	typedef enum
	{
		P2P_SENDDATA_RELIABLE,
		P2P_SENDDATA_UNRELIABLE
	} P2P_SendDataMode;
	
	extern DECLSPEC P2P_Session* SDLCALL P2P_createSession();
	extern DECLSPEC void SDLCALL P2P_destroySession(P2P_Session* session);
	
	extern DECLSPEC void SDLCALL P2P_searchForPeers(P2P_Session* session, const char*sessionID);
	extern DECLSPEC void SDLCALL P2P_searchForClients(P2P_Session* session, const char*sessionID);
	extern DECLSPEC void SDLCALL P2P_searchForServer(P2P_Session* session, const char*sessionID);
	
	extern DECLSPEC void SDLCALL P2P_setEventHandler(P2P_Session*session, P2P_EventHandler callback);
	
	extern DECLSPEC SDL_bool SDLCALL P2P_isConnected(P2P_Session*session);
	extern DECLSPEC SDL_bool SDLCALL P2P_isConnectedToPeer(P2P_Session*session, const char*peerID);
	
	extern DECLSPEC SDL_bool SDLCALL P2P_acceptConnectionRequest(P2P_Session*session, const char*peerID);
	extern DECLSPEC void SDLCALL P2P_denyConnectionRequest(P2P_Session*session, const char*peerID);
	
	extern DECLSPEC void SDLCALL P2P_getPeerDisplayName(P2P_Session*session, const char*peerID, char*dispName);
	extern DECLSPEC void SDLCALL P2P_getSelfDisplayName(P2P_Session*session, char*dispName);
	extern DECLSPEC void SDLCALL P2P_getSelfID(P2P_Session*session, char*selfID);
	extern DECLSPEC void SDLCALL P2P_getSessionID(P2P_Session*session, char*sessionID);
	
	extern DECLSPEC void SDLCALL P2P_sendData(P2P_Session*session, void*data, unsigned int size, P2P_SendDataMode mode);
	extern DECLSPEC void SDLCALL P2P_sendDataToPeers(P2P_Session*session, char**peers, unsigned int numPeers, void*data, unsigned int size, P2P_SendDataMode mode);
	
	extern DECLSPEC void SDLCALL P2P_disconnectPeer(P2P_Session*session, const char*peerID);
	extern DECLSPEC void SDLCALL P2P_endSession(P2P_Session*session);
	
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif
#include "close_code.h"

#endif /* _P2P_H */
