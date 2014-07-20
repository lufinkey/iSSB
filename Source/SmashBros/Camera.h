
#include "Global.h"

#pragma once

namespace SmashBros
{
	class Camera
	{
		friend class P2PDataManager;
	private:
		/*typedef struct
		{
			bool firstTime;
			float View_x;
			float View_y;
			float x;
			float y;
			float Zoom;
		} PrevP2PData;
		
		static PrevP2PData prevP2PData;*/
		
		static float prevCenterX;
		static float prevCenterY;

		static boolean firstUpdate;
		static boolean firstFocus;

		static byte mode;
		
		static const int offset = 50;
		static const int bottomOffset = 60;

		static RectangleF getFocusRect(ArrayList<int> players = ArrayList<int>());
		
		//static void handleAddP2PData(DataVoid&data);
		//static void handleSetP2PData(byte*&data);
		
	public:
		static float x;
		static float y;
		static float Zoom;

		static const int moveSpeed = 8;
		static const double zoomOutSpeed;
		static const double zoomInSpeed;

		static const byte MODE_FIXED = 0;
		static const byte MODE_FOLLOW = 1;
		static const byte MODE_ZOOM = 2;

		static void reset();
		static void Update();
		static void setMode(byte camera_mode);
		
		static int Width();
		static int Height();
	};
}