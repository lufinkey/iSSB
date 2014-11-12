
#include "FractalStage.h"
#include "../../Global.h"
#include "../../Camera.h"

namespace SmashBros
{
	FractalStage::FractalStage(float x1, float y1) : Stage(x1,y1)
	{
		Console::WriteLine("loading fractal");
		f = new Fractal();
		Console::WriteLine("loading trippy ass shit");
		randomstuff = new RandomStuff();

		setSpawnPoint(0, 0,0);
		setSpawnPoint(1,  -150, -150);
		setSpawnPoint(2,  -50,  -150);
		setSpawnPoint(3,  50,   -150);
		setSpawnPoint(4,  150,  -150);
		
		loadGameElements();
		loadPlatforms();
		loadHangPoints();
		
		setWireframeColor(Color::GREEN);
		showWireframes(true);
		
		setItemBoundaries(-350, -260, 350, 0);
		
		//setBackground("Images/Game/Stages/TestStage/bg.png");
		//setBackgroundScale(2.8);

		loadFile("Images/Game/Stages/TestStage/nyan_cat.png");
		loadFile("Images/Game/Stages/TestStage/roflsaurus.png");
		loadFile("Images/Game/Stages/TestStage/swirl.png");
		loadFile("Images/Game/Stages/TestStage/nic_cage.png");
	}

	FractalStage::~FractalStage()
	{
		delete f;
		delete randomstuff;
	}
	
	void FractalStage::loadGameElements()
	{
		GameElement*a;
		
		a = new GameElement(0,0);
		a->addAnimation(new Animation("normal",1,"Images/Game/Stages/TestStage/platform1.png"));
		a->changeAnimation("normal", FORWARD);
		addElement(a);
	}
	
	void FractalStage::loadPlatforms()
	{
		Platform*plat;
		
		plat = new Platform(Platform::TYPE_NORMAL,-295, -67, 590, 134);
		addPlatform(plat);
		
		createGenericPlatform(Platform::TYPE_GOTHROUGH,0,-160);
		createGenericPlatform(Platform::TYPE_NORMAL,-340,40);
		createGenericPlatform(Platform::TYPE_NORMAL,-370,120);
		createGenericPlatform(Platform::TYPE_NORMAL,-280,160);
		createSolidPlatform(130,-180);
		
		//createCirclePlatform(130,-60);
	}
	
	void FractalStage::loadHangPoints()
	{
		HangPoint*hp;
		
		hp = new HangPoint(HangPoint::LEFT,-302,-65);
		addHangPoint(hp);
		
		hp = new HangPoint(HangPoint::RIGHT,292,-65);
		addHangPoint(hp);
	}
	
	void FractalStage::createGenericPlatform(byte type, float x1, float y1)
	{
		GameElement*a;
		a = new GameElement(x1,y1);
		a->addAnimation(new Animation("normal",1,"Images/Game/Stages/TestStage/gothrough_plat1.png"));
		a->changeAnimation("normal", FORWARD);
		addElement(a);
		
		Platform*plat;
		plat = new Platform(type,x1-34,y1-8,68,16);
		addPlatform(plat);
	}
	
	void FractalStage::createSolidPlatform(float x1, float y1)
	{
		Platform*a;
		a = new Platform(Platform::TYPE_NORMAL,x1,y1);
		a->addAnimation(new Animation("normal",1,"Images/Game/Stages/TestStage/circle.png"));
		a->changeAnimation("normal", FORWARD);
		addPlatform(a);
	}
	
	void FractalStage::Update(long gameTime)
	{
		Stage::Update(gameTime);
		randomstuff->Update(gameTime);
		//cage.Update(gameTime);
	}
	
	void FractalStage::Draw(Graphics2D&g, long gameTime)
	{
		f->Draw(g, gameTime);
		setElementColor(Color(f->inverted,true));
		//DrawBackground(g,gameTime);
		randomstuff->Draw(g, gameTime);
		Stage::Draw(g, gameTime);
	}
	
	FractalStage::RandomStuff::RandomStuff()
	{
		nextSpawnTime = (long)(GameEngine::random()*14000);
	}

	FractalStage::RandomStuff::~RandomStuff()
	{
		for(int i=0; i<creepy.size(); i++)
		{
			delete creepy.get(i);
		}
		creepy.clear();
	}
	
	void FractalStage::RandomStuff::Update(long gameTime)
	{
		if(Global::getWorldTime() >= nextSpawnTime)
		{
			int num = (int)(300*GameEngine::random());
				
			if(num>200)
			{
				NicCage*cage = new NicCage();
				if(num > 240)
				{
					cage->isrotating = true;
				}
				creepy.add(cage);
			}
			else
			{
				creepy.add(new RandomThing());
				nextSpawnTime = Global::getWorldTime() + (long)(GameEngine::random()*5000);
			}
		}
			
		for(int i=(creepy.size()-1); i>=0; i--)
		{
			creepy.get(i)->Update(gameTime);
			if(creepy.get(i)->isDead)
			{
				delete creepy.get(i);
				creepy.remove(i);
			}
		}
	}
		
	void FractalStage::RandomStuff::Draw(Graphics2D&g, long gameTime)
	{
		for(int i=(creepy.size()-1); i>=0; i--)
		{
			creepy.get(i)->Draw(g, gameTime);
		}
	}

	FractalStage::RandomThing::RandomThing() : GameElement((float)(GameEngine::random()*900), (float)(GameEngine::random()*600))
	{
		newScale = 1;
		scaleIncr = 1;
		isDead = false;
		
		int creature = (int)(GameEngine::random()*2);
			
		Animation*anim;
			
		switch(creature)
		{
			default:
			anim = new Animation("normal", 8,1,6);
			anim->addFrame("Images/Game/Stages/TestStage/nyan_cat.png");
			break;
				
			case 1:
			anim = new Animation("normal", 18,1,11);
			anim->addFrame("Images/Game/Stages/TestStage/roflsaurus.png");
			break;
		}
		
		addAnimation(anim);
		changeAnimation("normal",FORWARD);
		
		setScale((float)(GameEngine::random()*1.5f + 0.2f));
		
		newScale = GameEngine::random()*1.5f + 0.2f;
		
		float moveX = (float)(GameEngine::random()*900);
		float moveY = (float)(GameEngine::random()*600);
		float speed = 2;
		
		double dist = distance(x,y,moveX,moveY);
		
		int frames = (int)((double)dist/(float)speed);
		
		scaleIncr = (double)(newScale - getScale())/(double)frames;
		
		moveTo(moveX, moveY, speed);
		
		setColor(Color((unsigned char)(GameEngine::random()*255),(unsigned char)(GameEngine::random()*255), (unsigned char)(GameEngine::random()*255), 255));
	}
		
	FractalStage::RandomThing::RandomThing(boolean create) : GameElement((float)(GameEngine::random()*900), (float)(GameEngine::random()*600))
	{
		newScale = 1;
		scaleIncr = 1;
		isDead = false;
		
		setScale((float)(GameEngine::random()*1.5f + 0.2f));
			
		newScale = GameEngine::random()*1.5f + 0.2f;
			
		float moveX = (float)(GameEngine::random()*900);
		float moveY = (float)(GameEngine::random()*600);
		float speed = 2;
			
		double dist = distance(x,y,moveX,moveY);
			
		int frames = (int)((double)dist/(float)speed);
			
		scaleIncr = (double)(newScale - getScale())/(double)frames;
			
		moveTo(moveX, moveY, speed);
		
		//setColor(Color((unsigned char)(GameEngine::random()*255),(unsigned char)(GameEngine::random()*255), (unsigned char)(GameEngine::random()*255), 255));
	}

	FractalStage::RandomThing::~RandomThing()
	{
		//
	}
	
	void FractalStage::RandomThing::Update(long gameTime)
	{
		GameElement::Update(gameTime);
		setScale(getScale() + (float)scaleIncr);
	}
	
	void FractalStage::RandomThing::onMoveFinish()
	{
		isDead = true;
	}
	
	FractalStage::NicCage::NicCage() : RandomThing(false)
	{
		rotate = 0;
		isrotating = false;
		
		swirl = new GameElement(0,0);
		Animation*anim = new Animation("normal", 15,15,1);
		anim->addFrame("Images/Game/Stages/TestStage/swirl.png");
		swirl->addAnimation(anim);
		swirl->changeAnimation("normal", FORWARD);
		swirl->setScale(getScale()*0.8f);
		
		addAnimation(new Animation("normal",1,"Images/Game/Stages/TestStage/nic_cage.png"));
		changeAnimation("normal",FORWARD);
	}
	
	FractalStage::NicCage::~NicCage()
	{
		delete swirl;
	}

	void FractalStage::NicCage::Update(long gameTime)
	{
		RandomThing::Update(gameTime);
		if(isrotating)
		{
			rotate+=0.5;
			setRotation(rotate);
		}
	}
		
	void FractalStage::NicCage::Draw(Graphics2D&g, long gameTime)
	{
		float oldRotation = g.getRotation();
		
		if(getRotation()!=0)
		{
			g.rotate(getRotation(),(float)(x*Camera::Zoom),(float)(y*Camera::Zoom));
		}
		
		setColor(Color((unsigned char)(GameEngine::random()*255),(unsigned char)(GameEngine::random()*255), (unsigned char)(GameEngine::random()*255), 255));
		
		RandomThing::Draw(g, gameTime);
		
		if(!isrotating)
		{
				
			swirl->setScale(getScale()*0.1f);
				
			swirl->x = x - (float)(46*getScale());
			swirl->y = y - (float)(3*getScale());
			swirl->Draw(g, gameTime);
				
			swirl->x = x + (float)(34*getScale());
			swirl->y = y - (float)(2*getScale());
			swirl->Draw(g, gameTime);
		}
		
		g.setRotation(oldRotation);
	}
	
	FractalStage::Fractal::Fractal()
	{
		c = ComplexNumber(-0.223, 0.745);
		
		values = null;
		
		minX = -1.5;
		maxX = 1.5;
		minY = -1.5;
		maxY = 1.5;
	    
		Scale = 1;
	    
		image = null;
		
		threshold = 1;
		
		iterations = 50;
		
		img.create(WIDTH,HEIGHT,Color::WHITE);
		
		color1 = Color(0,0,0,255);
	    color2 = Color(255,255,255,0);
	    
	    getValues();
		
	    for(unsigned int i=0;i<WIDTH;i++)
	    {
	        for(unsigned int j=0;j<HEIGHT;j++)
	        {
	            if(values[i][j])
				{
					img.setPixel(i, j, color1);
				}
	            if(!values[i][j])
				{
					img.setPixel(i, j, color2);
				}
	        }
	    }
	    
	    for(int i=0; i<WIDTH; i++)
		{
			delete[] values[i];
		}
		delete[] values;
		
		values = null;
		
		image = new BufferedImage(img);
	}
	
	FractalStage::Fractal::~Fractal()
	{
		delete image;
	}
	
	void FractalStage::Fractal::Draw(Graphics2D&g, long gameTime)
	{
	    //redrawFractal();
		
		Scale = GameEngine::random()*4 + 1;
		
	    float w = (float)((float)900*Scale);
	    float h = (float)((float)600*Scale);
	    float x1 = (float)((float)900 - w/2);
	    float y1 = (float)((float)600 - h/2);

		float oldRotation = g.getRotation();
		
		//image->update(img);

		color1 = Color((unsigned char)(GameEngine::random()*255),(unsigned char)(GameEngine::random()*255),(unsigned char)(GameEngine::random()*255));
	    color2 = Color((unsigned char)(GameEngine::random()*255),(unsigned char)(GameEngine::random()*255),(unsigned char)(GameEngine::random()*255));
	    while(color1.equals(color2))
	    {
	        color2 = Color((unsigned char)(GameEngine::random()*255),(unsigned char)(GameEngine::random()*255),(unsigned char)(GameEngine::random()*255));
	    }
	    Game::setBackgroundColor(color2);

	    g.rotate((float)(GameEngine::random()*360), 450, 300);
		g.setImageMask(color1);
	    g.drawImage(image,x1,y1,w,h);

		g.setRotation(oldRotation);
	}
	    
	void FractalStage::Fractal::redrawFractal()
	{
	    Color c1 = Color((unsigned char)(GameEngine::random()*255),(unsigned char)(GameEngine::random()*255),(unsigned char)(GameEngine::random()*255));
	    Color c2 = Color((unsigned char)(GameEngine::random()*255),(unsigned char)(GameEngine::random()*255),(unsigned char)(GameEngine::random()*255));
	    while(c1.equals(c2))
	    {
	        c2 = Color((unsigned char)(GameEngine::random()*255),(unsigned char)(GameEngine::random()*255),(unsigned char)(GameEngine::random()*255));
	    }
	    Game::setBackgroundColor(Color::RED);
	    //inverted = getNegativeColor(color1.getRGB());
	    Scale = (GameEngine::random()*4 + 1);

		unsigned int w = img.getWidth();
		unsigned int h = img.getHeight();

		for(unsigned int y=0; y<h; y++)
	    {
	        for(unsigned int x=0; x<w; x++)
	        {
	            Color current = Color(img.getPixel(x, y));
	            if(current.equals(color1))
	            {
	            	img.setPixel(x, y, c1);
	            }
	            else
	            {
	            	img.setPixel(x, y, c2);
	            }
	        }
	    }
	    color1 = c1;
	    color2 = c2;
	}

	void FractalStage::Fractal::getValues()
	{
	    values = new boolean*[WIDTH];
		for(unsigned int i=0; i<WIDTH; i++)
		{
			values[i] = new boolean[HEIGHT];
		}

	    for(int i=0;i<WIDTH;i++)
		{
	        for(int j=0;j<HEIGHT;j++)
			{
				double a = (double)i*(maxX-minX)/(double)WIDTH + minX;
				double b = (double)j*(maxY-minY)/(double)HEIGHT + minY;
				
	            values[i][j] = isInSet(ComplexNumber(a,b));
	        }
	    }
	}
	
	boolean FractalStage::Fractal::isInSet(ComplexNumber cn)
	{
	    for(int i=0; i<iterations; i++)
		{
	        cn = cn.square().add(c);
	    }

	    if(cn.magnitude()<threshold*threshold)
		{
			return true;
		}
		return false;
	}

	FractalStage::ComplexNumber::ComplexNumber()
	{
		a = 0;
		b = 0;
	}

	FractalStage::ComplexNumber::ComplexNumber(double a, double b)
	{
	    this->a = a;
	    this->b = b;
	}

	FractalStage::ComplexNumber FractalStage::ComplexNumber::square()
	{
	    return ComplexNumber(a*a - b*b, 2*a*b);
	}

	FractalStage::ComplexNumber FractalStage::ComplexNumber::add(const ComplexNumber&cn)
	{
	    return ComplexNumber(a+cn.a, b+cn.b);
	}

	double FractalStage::ComplexNumber::magnitude()
	{
	    return a*a+b*b;
	}
}