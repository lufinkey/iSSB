
#include "../../Stage.h"

#pragma once

namespace SmashBros
{
	class FractalStage : public Stage
	{
	private:
		class RandomThing : public GameElement
		{
		private:
			double newScale;
			double scaleIncr;

		public:
			boolean isDead;

			RandomThing();
			RandomThing(boolean create);
			virtual ~RandomThing();

			virtual void Update(long gameTime);
			virtual void onMoveFinish();
		};

		class NicCage : public RandomThing
		{
		private:
			float rotate;
			GameElement*swirl;

		public:
			boolean isrotating;

			NicCage();
			virtual ~NicCage();

			virtual void Update(long gameTime);
			virtual void Draw(Graphics2D&g, long gameTime);
		};

		class RandomStuff
		{
		private:
			ArrayList<RandomThing*> creepy;
			long nextSpawnTime;

		public:
			RandomStuff();
			virtual ~RandomStuff();

			virtual void Update(long gameTime);
			virtual void Draw(Graphics2D&g, long gameTime);
		};

		class ComplexNumber
		{
		private:
			double a, b;

		public:
			ComplexNumber();
			ComplexNumber(double a, double b);
			ComplexNumber square();
			ComplexNumber add(const ComplexNumber&cn);
			double magnitude();
		};

		class Fractal
		{
		private:
			static const unsigned int WIDTH = 350;
			static const unsigned int HEIGHT = 350;

			ComplexNumber c;
			boolean**values;

			double minX,maxX,minY,maxY;
			double Scale;

			Color color1,color2;
			
			BufferedImage*image;
			Image img;

			double threshold;
			int iterations;
			
			void redrawFractal();
			void getValues();
			boolean isInSet(ComplexNumber cn);

		public:
			int inverted;

			Fractal();
			virtual ~Fractal();

			virtual void Draw(Graphics2D&g, long gameTime);
		};

		Fractal*f;
		RandomStuff*randomstuff;

		void loadGameElements();
		void loadPlatforms();
		void loadHangPoints();
		void createGenericPlatform(byte type, float x1, float y1);
		void createSolidPlatform(float x1, float y1);

	public:
		FractalStage(float x1, float y1);
		virtual ~FractalStage();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
	};
}