
#include "ActorGrid.h"

namespace SmashBros
{
	ActorGrid::ActorGrid(float x1, float y1, int rows, int cols)
	{
		currentIndex = 0;
		hoveredIndex = -1;
		selectedIndex = -1;
		Scale = 1;
		changeScales = false;
		xSpace = 5;
		ySpace = 5;

		this->rows = rows;
		this->cols = cols;
		this->x = x1;
		this->y = y1;
	}

	ActorGrid::~ActorGrid()
	{
		for(int i=0; i<actors.size(); i++)
		{
			delete actors.get(i);
		}
		actors.clear();
	}

	void ActorGrid::Update(long gameTime)
	{
		hoveredIndex = -1;
		selectedIndex = -1;
		for(int i=0; i<actors.size(); i++)
		{
			Actor*a = actors.get(i);
			if(a!=null)
			{
				a->Update(gameTime);
				if(a->mouseOver())
				{
					hoveredIndex = i;
					if(a->isClicked())
					{
						selectedIndex = i;
					}
				}
			}
		}
	}

	void ActorGrid::Draw(Graphics2D&g, long gameTime)
	{
		for(int i=0; i<actors.size(); i++)
		{
			Actor*a = actors.get(i);
			if(a!=null)
			{
				a->Draw(g, gameTime);
			}
		}
	}

	void ActorGrid::setScale(float scale)
	{
		Scale = scale;
		changeScales = true;
		for(int i=0; i<actors.size(); i++)
		{
			actors.get(i)->Scale = scale;
		}
	}

	float ActorGrid::getScale()
	{
		return Scale;
	}

	int ActorGrid::getSelectedIndex()
	{
		return selectedIndex;
	}

	int ActorGrid::getHoveredIndex()
	{
		return hoveredIndex;
	}

	int ActorGrid::size()
	{
		return currentIndex;
	}

	void ActorGrid::setSpacing(float x, float y)
	{
		xSpace = x;
		ySpace = y;
	}

	void ActorGrid::add(Actor*a)
	{
		currentIndex++;
		if(a!=null)
		{
			if(changeScales && a->Scale==1)
			{
				a->Scale = this->Scale;
			}
			addToGrid(a,x,y,cols,rows,xSpace,ySpace,currentIndex);
		}
		actors.add(a);
	}

	Actor*ActorGrid::get(int index)
	{
		return actors.get(index);
	}
	
	Actor*ActorGrid::get(int row, int col)
	{
		int index = (cols*row)+col;
		Actor*a = get(index);
		return a;
	}

	void ActorGrid::addToGrid(Actor*a,float x1,float y1,int xAmount,int yAmount,float xspace,float yspace,int num)
	{
	    int xLoc;
	    int yLoc;
	    float xCreate;
	    float yCreate;
	    if(num>xAmount)
	    {
	    	xLoc = ((num-1)%xAmount)+1;
	        yLoc = ((num-1)/xAmount)+1;
	    }
	    else
	    {
	        xLoc=num;
	        yLoc=1;
	    }
	    xCreate=x1+(xspace*(xLoc-1));
	    yCreate=y1+(yspace*(yLoc-1));
	    a->x=xCreate;
	    a->y=yCreate;
	}
}