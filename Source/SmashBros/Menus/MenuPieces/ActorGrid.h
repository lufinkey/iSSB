
#include "../../../GameEngine/GameEngine.h"

#pragma once

namespace SmashBros
{
	class ActorGrid
	{
	private:
		ArrayList<Actor*> actors;

		int currentIndex;
		int hoveredIndex;
		int selectedIndex;

		float Scale;
		boolean changeScales;

		float xSpace;
		float ySpace;
		int rows,cols;

		void addToGrid(Actor*a,float x1,float y1,int xAmount,int yAmount,float xspace,float yspace,int num);

	public:
		float x,y;

		ActorGrid(float x1, float y1, int rows, int cols);
		virtual ~ActorGrid();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);

		void setScale(float scale);
		float getScale();
		int getSelectedIndex();
		int getHoveredIndex();
		int size();
		void setSpacing(float x, float y);
		void add(Actor*a);
		Actor*get(int index);
		Actor*get(int row, int col);
		void remove(int index, boolean deallocate=true);
		void remove(Actor*a, boolean deallocate=true);
		void remove(const ArrayList<Actor*>&actors, boolean deallocate=true);
	};
}