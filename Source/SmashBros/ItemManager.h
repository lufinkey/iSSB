
#include "Item.h"

#pragma once

namespace SmashBros
{
	class ItemManager
	{
		friend class Item;
		friend class Global;
		friend class P2PDataManager;
	private:
		typedef struct
		{
			int itemID;
			int itemNo;
			float x;
			float y;
		} CreateItemInfo;
		
		static ArrayList<Item*> items;
		static long spawnTime;
		static ArrayList<String> files;
		static ArrayList<CreateItemInfo> createdItems;
		static ArrayList<int> destroyedItems;
		
		static Item*CreateItem(int itemNo, float x1, float y1);
		
		static void handleAddP2PData(DataVoid&data);
		static void handleSetP2PData(byte*&data);
		
		static void addFile(String file);
		
		static void RandomItemSpawn();
		
		static bool checkIDAvailable(int itemID);
	public:
		static void Unload();
		static void AddItem(Item*item);
		static Item*GetItem(int index);
		static int TotalItems();
		static void RemoveAll();
		static void SpawnItem(int itemNo);

		static void Update(long gameTime);
		static void Draw(Graphics2D&g, long gameTime);
	};
}