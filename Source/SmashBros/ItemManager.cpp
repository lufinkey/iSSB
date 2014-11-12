
#include "ItemManager.h"
#include "Global.h"
#include "Game/Items/SmashBall.h"
#include "Game/Items/RayGun.h"
#include "Game/Items/HeartContainer.h"
#include "Game/Items/BeamSword.h"
#include "Game/Items/SuperMushroom.h"
#include "Game/Items/PoisonMushroom.h"
#include "P2PDataManager.h"

namespace SmashBros
{
	ArrayList<Item*> ItemManager::items = ArrayList<Item*>();
	long ItemManager::spawnTime = 0;
	ArrayList<String> ItemManager::files = ArrayList<String>();
	ArrayList<ItemManager::CreateItemInfo> ItemManager::createdItems = ArrayList<ItemManager::CreateItemInfo>();
	ArrayList<int> ItemManager::destroyedItems = ArrayList<int>();
	
	void ItemManager::handleAddP2PData(DataVoid&data)
	{
		ArrayList<CreateItemInfo> justCreated = createdItems;
		if(createdItems.size()>0)
		{
			P2PDataManager::setReliable();
			
			bool avail = true;
			data.add(&avail, sizeof(avail));
			
			int totalCreated = createdItems.size();
			data.add(&totalCreated, sizeof(totalCreated));
			
			for(int i=0; i<createdItems.size(); i++)
			{
				CreateItemInfo&info = createdItems.get(i);
				//Console::WriteLine((String)"sending item create message with id " + info.itemID);
				data.add(&info.itemID, sizeof(info.itemID));
				data.add(&info.itemNo, sizeof(info.itemNo));
				data.add(&info.x, sizeof(info.x));
				data.add(&info.y, sizeof(info.y));
			}
			createdItems.clear();
		}
		else
		{
			bool avail = false;
			data.add(&avail, sizeof(avail));
		}
		
		int totalItems = items.size();
		ArrayList<Item*> otherItems;
		for(int i=0; i<=Global::possPlayers; i++)
		{
			if(Global::characters[i]!=null)
			{
				Player*playr = Global::characters[i];
				if(playr->itemHolding!=null)
				{
					otherItems.add(playr->itemHolding);
				}
				if(playr->itemWearing!=null)
				{
					otherItems.add(playr->itemWearing);
				}
				if(playr->itemHatting!=null)
				{
					otherItems.add(playr->itemHatting);
				}
				if(playr->itemWielding!=null)
				{
					otherItems.add(playr->itemWielding);
				}
			}
		}
		totalItems+=otherItems.size();
		
		if(totalItems>0)
		{
			bool avail = true;
			data.add(&avail, sizeof(avail));
			
			DataVoid itemUpdates;
			int realTotal = 0;
			
			for(int i=0; i<items.size(); i++)
			{
				Item*item = items.get(i);
				bool tooSoon = false;
				/*for(int j=0; j<justCreated.size(); j++)
				{
					if(item->getID() == justCreated.get(j).itemID)
					{
						tooSoon = true;
						j = justCreated.size();
					}
				}*/
				if(!item->dead && !tooSoon)
				{
					realTotal++;
					
					int itemID = item->getID();
					//Console::WriteLine((String)"updating item with id " + itemID);
					itemUpdates.add(&itemID, sizeof(itemID));
					
					item->handleAddP2PData(itemUpdates);
				}
				else
				{
					//Console::WriteLine((String)"was gonna send item " + item->getID() + " but it was dead");
				}
			}
			
			for(int i=0; i<otherItems.size(); i++)
			{
				Item*item = items.get(i);
				bool tooSoon = false;
				/*for(int j=0; j<justCreated.size(); j++)
				{
					if(item->getID() == justCreated.get(j).itemID)
					{
						tooSoon = true;
						j = justCreated.size();
					}
				}*/
				if(!item->dead && !tooSoon)
				{
					realTotal++;
					
					int itemID = item->getID();
					//Console::WriteLine((String)"updating item with id " + itemID);
					itemUpdates.add(&itemID, sizeof(itemID));
					
					item->handleAddP2PData(itemUpdates);
				}
				else
				{
					//Console::WriteLine((String)"was gonna send item " + item->getID() + " but it was dead");
				}
			}
			
			data.add(&realTotal, sizeof(realTotal));
			data.add(itemUpdates);
		}
		else
		{
			bool avail = false;
			data.add(&avail, sizeof(avail));
		}
		
		if(destroyedItems.size()>0)
		{
			P2PDataManager::setReliable();
			
			bool avail = true;
			data.add(&avail, sizeof(avail));
			
			int total = destroyedItems.size();
			data.add(&total, sizeof(total));
			
			for(int i=0; i<destroyedItems.size(); i++)
			{
				int itemID = destroyedItems.get(i);
				data.add(&itemID, sizeof(itemID));
				//Console::WriteLine((String)"sending destroy signal to item with id " + itemID);
			}
			destroyedItems.clear();
		}
		else
		{
			bool avail = false;
			data.add(&avail, sizeof(avail));
		}
	}
	
	void ItemManager::handleSetP2PData(byte*&data)
	{
		bool avail = DataVoid::toBool(data);
		data += sizeof(bool);
		
		if(avail)
		{
			int totalCreated = DataVoid::toInt(data);
			data += sizeof(int);
			
			for(int i=0; i<totalCreated; i++)
			{
				CreateItemInfo info;
				
				info.itemID = DataVoid::toInt(data);
				data += sizeof(int);
				
				info.itemNo = DataVoid::toInt(data);
				data += sizeof(int);
				
				info.x = DataVoid::toFloat(data);
				data += sizeof(float);
				
				info.y = DataVoid::toFloat(data);
				data += sizeof(float);
				
				//Console::WriteLine((String)"got message to create item with id " + info.itemID);
				
				Item::setNextID(info.itemID);
				Item*newItem = CreateItem(info.itemNo, info.x, info.y);
				newItem->id = info.itemID;
				AddItem(newItem);
				Console::WriteLine((String)"Spawned item " + Global::getItemName(info.itemNo) + "with ID " + newItem->id);
			}
		}
		
		avail = DataVoid::toBool(data);
		data += sizeof(bool);
		
		if(avail)
		{
			int totalItems = DataVoid::toInt(data);
			data += sizeof(int);
			
			for(int i=0; i<totalItems; i++)
			{
				int itemID = DataVoid::toInt(data);
				data += sizeof(int);
				
				Item*item = NULL;
				
				//Console::WriteLine((String)"Got message to update item with id " + itemID);
				
				for(int j=0; j<items.size(); j++)
				{
					Item*checkItem = items.get(j);
					if(itemID == checkItem->getID())
					{
						item = checkItem;
						j = items.size();
					}
				}
				
				if(item == NULL)
				{
					//Console::WriteLine("but i didn't fucking have it");
					P2PDataManager::setErrorState();
					Game::showMessage("Error", (String)"An error has occured in ItemManager::handleSetP2PData(byte*&)\n No item to update found with id " + itemID);
					String mylog = (String)"items.size() = " + items.size() + '\n';
					for(int j=0; j<items.size(); j++)
					{
						int hold = items.get(j)->getID();
						mylog += (String)"index " + j + ": " + hold;
					}
					Game::showMessage(mylog);
					return;
				}
				else
				{
					//Console::WriteLine("and i had it. thank jesus");
					item->handleSetP2PData(data);
				}
			}
		}
		
		avail = DataVoid::toBool(data);
		data += sizeof(bool);
		
		if(avail)
		{
			int total = DataVoid::toInt(data);
			data += sizeof(int);
			
			for(int i=0; i<total; i++)
			{
				int itemID = DataVoid::toInt(data);
				data += sizeof(int);
				
				Item*item = NULL;
				int index = -1;
				
				for(int j=0; j<items.size(); j++)
				{
					Item*checkItem = items.get(j);
					if(itemID == checkItem->getID())
					{
						item = checkItem;
						index = j;
						j = items.size();
					}
				}
				
				if(item == NULL)
				{
					P2PDataManager::setErrorState();
					Game::showMessage("Error", (String)"An error has occured in ItemManager::handleSetP2PData(byte*&)\n No item to destroy found with id " + itemID);
					String mylog = (String)"destroyedItems.size() = " + destroyedItems.size() + '\n';
					for(int j=0; j<destroyedItems.size(); j++)
					{
						int hold = destroyedItems.get(j);
						mylog += (String)"index " + j + ": " + hold;
					}
					mylog += (String)"items.size() = " + items.size() + '\n';
					for(int j=0; j<items.size(); j++)
					{
						int hold = items.get(j)->getID();
						mylog += (String)"index " + j + ": " + hold;
					}
					Game::showMessage(mylog);
					return;
				}
				else
				{
					delete item;
					items.remove(index);
				}
			}
		}
		destroyedItems.clear();
	}
	
	bool ItemManager::checkIDAvailable(int itemID)
	{
		for(int i=0; i<items.size(); i++)
		{
			int check = items.get(i)->getID();
			if(check == itemID)
			{
				return false;
			}
		}
		for(int i=0; i<=Global::possPlayers; i++)
		{
			Player*playr = Global::characters[i];
			if(playr!=NULL)
			{
				if(playr->itemHolding!=null)
				{
					if(itemID == playr->itemHolding->getID())
					{
						return false;
					}
				}
				if(playr->itemWearing!=null)
				{
					if(itemID == playr->itemWearing->getID())
					{
						return false;
					}
				}
				if(playr->itemHatting!=null)
				{
					if(itemID == playr->itemHatting->getID())
					{
						return false;
					}
				}
				if(playr->itemWielding!=null)
				{
					if(itemID == playr->itemWielding->getID())
					{
						return false;
					}
				}
			}
		}
		return true;
	}

	void ItemManager::Unload()
	{
		for(int i=0; i<files.size(); i++)
		{
			AssetManager::unloadImage(files.get(i));
		}
		RemoveAll();
		spawnTime = 0;
	}

	void ItemManager::addFile(String file)
	{
		for(int i=0; i<files.size(); i++)
		{
			if(file.equals(files.get(i)))
			{
				return;
			}
		}
		files.add(file);
	}

	void ItemManager::AddItem(Item*item)
	{
		for(int i=0; i<items.size(); i++)
		{
			if(item==items.get(i))
			{
				return;
			}
		}
		
		if(!item->isHeld())
		{
			item->onCreate();
		}
		item->index = items.size();
		items.add(item);
	}

	Item*ItemManager::GetItem(int index)
	{
		if(index < items.size())
		{
			return items.get(index);
		}
		return null;
	}

	int ItemManager::TotalItems()
	{
		return items.size();
	}

	void ItemManager::RemoveAll()
	{
		for(int i=0; i<items.size(); i++)
		{
			items.get(i)->destroy();
			items.get(i)->onDestroy();
			delete items.get(i);
		}
		items.clear();
		destroyedItems.clear();
		createdItems.clear();
	}

	void ItemManager::Update(long gameTime)
	{
		if(Global::gameType == Global::TYPE_GROUPBRAWL)
		{
			if(spawnTime==0)
			{
				spawnTime=Global::getWorldTime()+(long)((GameEngine::random()*30000)+5000);
			}
			else
			{
			    if(spawnTime<=Global::getWorldTime())
			    {
			        RandomItemSpawn();
			        spawnTime=Global::getWorldTime()+(long)((GameEngine::random()*30000)+5000);
			    }
			}
		}
		for(int i=0; i<=Global::possPlayers; i++)
		{
			if(Global::characters[i]!=null)
			{
				Global::characters[i]->itemCollidingIndex = -1;
			}
		}
		for(int i=(items.size()-1); i>=0; i--)
		{
			Item*item = items.get(i);
			if(item->dead)
			{
				item->onDestroy();
				Console::WriteLine((String)"Destroyed Item " + Global::getItemName(item->itemNo));
				delete item;
				items.remove(i);
			}
			else if(item->held)
			{
				items.remove(i);
			}
		}
		for(int i=0; i<items.size(); i++)
		{
			Item*item = items.get(i);
			item->index = i;
			item->Update(gameTime);
		}
	}

	void ItemManager::Draw(Graphics2D&g, long gameTime)
	{
		for(int i=0; i<items.size(); i++)
		{
			Item*item = items.get(i);
			item->index = i;
			item->Draw(g, gameTime);
		}
	}

	void ItemManager::RandomItemSpawn()
	{
		if(Global::itemsActive.size()>0)
		{
			int index = (int)(GameEngine::random()*Global::itemsActive.size());
			SpawnItem(Global::itemsActive.get(index));
		}
	}
	
	Item*ItemManager::CreateItem(int itemNo, float x1, float y1)
	{
		Item*newItem = NULL;
		
		switch(itemNo) //TODO: add items
		{
			case Global::ITEM_SMASHBALL:
			if(!Global::smashBallOnField && !Global::playerHasSmashBall)
			{
				newItem = new SmashBall(x1,y1);
			}
			break;
				
			case Global::ITEM_RAYGUN:
			newItem = new RayGun(x1,y1);
			break;
			
			case Global::ITEM_HEARTCONTAINER:
			newItem = new HeartContainer(x1,y1);
			break;
			
			case Global::ITEM_BEAMSWORD:
			newItem = new BeamSword(x1,y1);
			break;
			
			case Global::ITEM_SUPERMUSHROOM:
			newItem = new SuperMushroom(x1,y1);
			break;
			
			case Global::ITEM_POISONMUSHROOM:
			newItem = new PoisonMushroom(x1,y1);
			break;
		}
		
		if(newItem!=NULL)
		{
			if(P2PDataManager::isEnabled() && P2PDataManager::isServer())
			{
				//Console::WriteLine((String)"adding item with id " + newItem->getID() + " to createdItems");
				CreateItemInfo info;
				info.itemID = newItem->getID();
				info.itemNo = itemNo;
				info.x = x1;
				info.y = y1;
				createdItems.add(info);
			}
		}
		
		return newItem;
	}
	
	void ItemManager::SpawnItem(int itemNo)
	{
		GameEngine::RectangleF bounds = Global::currentStage->itemBounds;
		float x1 = (float)((GameEngine::random()*bounds.width)+bounds.x);
		float y1 = (float)((GameEngine::random()*bounds.height)+bounds.y);
		
		Item*newItem = CreateItem(itemNo, x1, y1);
		
		if(newItem!=NULL)
		{
			AddItem(newItem);
			Console::WriteLine((String)"Spawned item " + Global::getItemName(itemNo));
		}
	}
}