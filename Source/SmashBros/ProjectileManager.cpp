
#include "ProjectileManager.h"
#include "Global.h"
#include "P2PDataManager.h"

namespace SmashBros
{
	ArrayList<Projectile*> ProjectileManager::projectiles = ArrayList<Projectile*>();
	ArrayList<int> ProjectileManager::destroyedProjectiles = ArrayList<int>();
	
	void ProjectileManager::handleAddP2PData(DataVoid&data)
	{
		if(projectiles.size()>0)
		{
			bool avail = true;
			data.add(&avail, sizeof(avail));
			
			int total = 0;
			
			DataVoid projUpdates;
			
			for(int i=0; i<projectiles.size(); i++)
			{
				Projectile*proj = projectiles.get(i);
				if(!proj->dead)
				{
					total++;
					int projID = proj->getID();
					projUpdates.add(&projID, sizeof(projID));
					
					proj->handleAddP2PData(projUpdates);
				}
			}
			
			data.add(&total, sizeof(total));
			data.add(projUpdates);
		}
		else
		{
			bool avail = false;
			data.add(&avail, sizeof(avail));
		}
		
		if(destroyedProjectiles.size()>0)
		{
			P2PDataManager::setReliable();
			
			bool avail = true;
			data.add(&avail, sizeof(avail));
			
			int total = destroyedProjectiles.size();
			data.add(&total, sizeof(total));
			
			for(int i=0; i<destroyedProjectiles.size(); i++)
			{
				int projID = destroyedProjectiles.get(i);
				data.add(&projID, sizeof(projID));
			}
			destroyedProjectiles.clear();
		}
		else
		{
			bool avail = false;
			data.add(&avail, sizeof(avail));
		}
	}
	
	void ProjectileManager::handleSetP2PData(byte*&data)
	{
		bool avail = DataVoid::toBool(data);
		data += sizeof(bool);
		
		if(avail)
		{
			int total = DataVoid::toInt(data);
			data += sizeof(int);
			
			for(int i=0; i<total; i++)
			{
				int projID = DataVoid::toInt(data);
				data += sizeof(int);
				
				Projectile*proj = NULL;
				
				for(int j=0; j<projectiles.size(); j++)
				{
					Projectile*checkProj = projectiles.get(j);
					
					if(projID == checkProj->getID())
					{
						proj = checkProj;
						j = projectiles.size();
					}
				}
				
				if(proj == NULL)
				{
					P2PDataManager::setErrorState();
					Game::showMessage("Error", (String)"An error has occured in ProjectileManager::handleSetP2PData(byte*&)\n No projectile to update found with id " + projID);
					String mylog = (String)"projectiles.size() = " + projectiles.size() + '\n';
					for(int j=0; j<projectiles.size(); j++)
					{
						int hold = projectiles.get(j)->getID();
						mylog += (String)"index " + j + ": " + hold;
					}
					Game::showMessage(mylog);
					return;
				}
				else
				{
					proj->handleSetP2PData(data);
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
				int projID = DataVoid::toInt(data);
				data += sizeof(int);
				
				Projectile*proj = NULL;
				int index = -1;
				
				for(int j=0; j<projectiles.size(); j++)
				{
					Projectile*checkProj = projectiles.get(j);
					if(projID == checkProj->getID())
					{
						proj = checkProj;
						index = j;
						j = projectiles.size();
					}
				}
				
				if(proj == NULL)
				{
					P2PDataManager::setErrorState();
					Game::showMessage("Error", (String)"An error has occured in ProjectileManager::handleSetP2PData(byte*&)\n No projectile to destroy found with id " + projID);
					String mylog = (String)"destroyedProjectiles.size() = " + destroyedProjectiles.size() + '\n';
					for(int j=0; j<destroyedProjectiles.size(); j++)
					{
						int hold = destroyedProjectiles.get(j);
						mylog += (String)"index " + j + ": " + hold;
					}
					mylog += (String)"projectiles.size() = " + projectiles.size() + '\n';
					for(int j=0; j<projectiles.size(); j++)
					{
						int hold = projectiles.get(j)->getID();
						mylog += (String)"index " + j + ": " + hold;
					}
					Game::showMessage(mylog);
					return;
				}
				else
				{
					//Game::showMessage((String)"destroyed projectile with id " + projID);
					delete proj;
					projectiles.remove(index);
				}
			}
		}
		destroyedProjectiles.clear();
	}
	
	bool ProjectileManager::checkIDAvailable(int projID)
	{
		for(int i=0; i<projectiles.size(); i++)
		{
			int check = projectiles.get(i)->getID();
			if(check == projID)
			{
				return false;
			}
		}
		return true;
	}
	
	Projectile* ProjectileManager::GetProjectile(int projID)
	{
		for(int i=0; i<projectiles.size(); i++)
		{
			Projectile* projectile = projectiles.get(i);
			if(projectile->getID()==projID)
			{
				return projectile;
			}
		}
		return null;
	}
	
	void ProjectileManager::AddProjectile(Projectile*p)
	{
		//Console::WriteLine((String)"Adding projectile with id " + p->getID() + " to ProjectileManager");
		projectiles.add(p);
	}

	void ProjectileManager::RemoveAll()
	{
		for(int i=0; i<projectiles.size(); i++)
		{
			projectiles.get(i)->destroy();
			projectiles.get(i)->onDestroy();
			delete projectiles.get(i);
		}
		projectiles.clear();
		destroyedProjectiles.clear();
	}

	void ProjectileManager::Update(long gameTime)
	{
		for(int i=(projectiles.size()-1); i>=0; i--)
		{
			Projectile*projectile = projectiles.get(i);
			if(projectile->dead)
			{
				projectile->onDestroy();
				delete projectile;
				projectiles.remove(i);
			}
			else
			{
				projectile->Update(gameTime);
				Stage*stage = Global::currentStage;
				for(int j=0; j<stage->platforms.size(); j++)
				{
					byte dir = stage->checkProjectileCollision(projectile, stage->platforms.get(j));
					if(dir > 0)
					{
						if(stage->platforms.get(j)->getType()==Platform::TYPE_GOTHROUGH)
						{
							if(dir == PrimitiveActor::DIR_UP || projectile->allPlatsSolid)
							{
								projectile->whilePlatformColliding(stage->platforms.get(j), dir);
								projectile->whileGroundColliding();
								if(projectile->isSolid())
								{
									if(projectile->yvelocity>0)
									{
										projectile->yvelocity = 0;
									}
								}
							}
						}
						else
						{
							projectile->whilePlatformColliding(stage->platforms.get(j), dir);
							if(dir == PrimitiveActor::DIR_UP)
							{
								projectile->whileGroundColliding();
							}
							if(projectile->isSolid())
							{
								switch(dir)
								{
									case PrimitiveActor::DIR_UP:
									if(projectile->yvelocity>0)
									{
										projectile->yvelocity = 0;
									}
									break;
									
									case PrimitiveActor::DIR_LEFT:
									if(projectile->xvelocity>0)
									{
										projectile->xvelocity = 0;
									}
									break;
									
									case PrimitiveActor::DIR_RIGHT:
									if(projectile->xvelocity<0)
									{
										projectile->xvelocity = 0;
									}
									break;
								}
							}
						}
					}
				}
				for(int j=0; j<=Global::possPlayers; j++)
				{
					if(Global::characters[j]!=null)
					{
						CheckProjectileCollision(projectile,Global::characters[j]);
					}
				}
			}
		}
	}

	void ProjectileManager::CheckProjectileCollision(Projectile*projectile, Player*playr)
	{
		byte dir = 0;
		if(projectile->isSolid() && (projectile->isOwnerSolid() || (!projectile->isOwnerSolid() && playr->getPlayerNo()!=projectile->getPlayerNo())))
		{
			dir = projectile->solidPlayerCollision(playr);
			switch(dir)
			{
				case PrimitiveActor::DIR_DOWN:
				playr->platformCollision(projectile->platform, PrimitiveActor::DIR_UP);
				if(!playr->hangColliding)
				{
					if(!playr->groundCheck)
					{
						playr->whileGroundColliding();
					}
					playr->groundColliding = true;
					if(!playr->prevGroundColliding)
					{
						playr->onGroundCollide();
					}
					playr->groundCheck = true;
				}
				playr->setCurrentCollidePlatformActor(PrimitiveActor::DIR_UP, projectile->platform);
				playr->collideQueue.add(PrimitiveActor::DIR_UP);
				break;
				
				case PrimitiveActor::DIR_UP:
				playr->platformCollision(projectile->platform, PrimitiveActor::DIR_DOWN);
				playr->setCurrentCollidePlatformActor(PrimitiveActor::DIR_DOWN, projectile->platform);
				playr->collideQueue.add(PrimitiveActor::DIR_DOWN);
				break;
				
				case PrimitiveActor::DIR_LEFT:
				playr->platformCollision(projectile->platform, PrimitiveActor::DIR_RIGHT);
				playr->setCurrentCollidePlatformActor(PrimitiveActor::DIR_RIGHT, projectile->platform);
				playr->collideQueue.add(PrimitiveActor::DIR_RIGHT);
				break;
				
				case PrimitiveActor::DIR_RIGHT:
				playr->platformCollision(projectile->platform, PrimitiveActor::DIR_LEFT);
				playr->setCurrentCollidePlatformActor(PrimitiveActor::DIR_LEFT, projectile->platform);
				playr->collideQueue.add(PrimitiveActor::DIR_LEFT);
				break;
			}
			
			switch(dir)
			{
				case PrimitiveActor::DIR_DOWN:
				dir = PrimitiveActor::DIR_UP;
				break;
				
				case PrimitiveActor::DIR_UP:
				dir = PrimitiveActor::DIR_DOWN;
				break;
				
				case PrimitiveActor::DIR_LEFT:
				dir = PrimitiveActor::DIR_RIGHT;
				break;
				
				case PrimitiveActor::DIR_RIGHT:
				dir = PrimitiveActor::DIR_LEFT;
				break;
			}
		}
		else
		{
			dir = projectile->isColliding2(playr);
		}
		if(dir>0)
		{
			byte pDir = 0;
			switch(dir)
			{
				case PrimitiveActor::DIR_DOWN:
				pDir = PrimitiveActor::DIR_UP;
				break;
				
				case PrimitiveActor::DIR_UP:
				pDir = PrimitiveActor::DIR_DOWN;
				break;
				
				case PrimitiveActor::DIR_LEFT:
				pDir = PrimitiveActor::DIR_RIGHT;
				break;
				
				case PrimitiveActor::DIR_RIGHT:
				pDir = PrimitiveActor::DIR_LEFT;
				break;
			}
			
			if(projectile->playersColliding.isColliding(playr->getPlayerNo()))
			{
				projectile->whilePlayerHitting(playr, dir);
			}
			else if(!projectile->deflectable || !playr->onDeflectProjectileCollision(projectile, pDir))
			{
				projectile->onPlayerHit(playr, dir);
				projectile->playersColliding.addCollision(playr->getPlayerNo());
			}
		}
		else
		{
			projectile->playersColliding.removeCollision(playr->getPlayerNo());
		}
	}

	void ProjectileManager::DrawBottomLayer(Graphics2D&g, long gameTime)
	{
		for(int i=(projectiles.size()-1); i>=0; i--)
		{
			if(projectiles.get(i)->layer == Projectile::LAYER_BOTTOM)
			{
				projectiles.get(i)->Draw(g, gameTime);
			}
		}
	}

	void ProjectileManager::DrawMiddleLowerLayer(Graphics2D&g, long gameTime)
	{
		for(int i=(projectiles.size()-1); i>=0; i--)
		{
			if(projectiles.get(i)->layer == Projectile::LAYER_MIDDLELOWER)
			{
				projectiles.get(i)->Draw(g, gameTime);
			}
		}
	}

	void ProjectileManager::DrawMiddleUpperLayer(Graphics2D&g, long gameTime)
	{
		for(int i=(projectiles.size()-1); i>=0; i--)
		{
			if(projectiles.get(i)->layer == Projectile::LAYER_MIDDLEUPPER)
			{
				projectiles.get(i)->Draw(g, gameTime);
			}
		}
	}

	void ProjectileManager::DrawTopLayer(Graphics2D&g, long gameTime)
	{
		for(int i=(projectiles.size()-1); i>=0; i--)
		{
			if(projectiles.get(i)->layer == Projectile::LAYER_TOP)
			{
				projectiles.get(i)->Draw(g, gameTime);
			}
		}
	}
}