#include "stdafx.h"
#include "Game.hpp"

namespace GSTATE
{
	enum {Uninitialized, Splash, Menu, Play, Pause, Resume, Exit};
}

void Game::initialize()
{
	Mad::Utility::ConfigParser cfg("setting.cfg");
	std::string width,height,depth,title;

	cfg.getValue("width",width);
	cfg.getValue("height",height);
	cfg.getValue("depth",depth);
	cfg.getValue("title",title);

	create(std::stoi(width),std::stoi(height),std::stoi(depth),title);
	//setFrameLimit(60);
	setVerticalSyncEnabled(true);
	setUseSmoothTexture(false);
	setDisplayStatistics(true);
	time = 0;

	GameState->changeState(GSTATE::Splash);

	m_PhysicsManager = nullptr;
}

void Game::update()
{
	switch (GameState->getCurrentState())
	{
	case GSTATE::Splash:
		{
		splash();
		m_Splash.draw();
		}break;
	case GSTATE::Menu:
		{
		menu();
		}break;
	case GSTATE::Play:
		{
			play();
		}break;
	}
}

void Game::splash()
{	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	//if (time >100.f)
		GameState->changeState(GSTATE::Menu);
}

void Game::menu()
{
	GameState->changeState(GSTATE::Play);
}

void Game::load()
{
	switch (GameState->getCurrentState())
	{
	case GSTATE::Splash:
		{
			ResourceProvider->loadTextureFromFile("volge","volge.png");

			m_Splash.setTexture("volge");
			m_Splash.setOrigin(m_Splash.getSize().x/2.f, m_Splash.getSize().y/2.f);
			m_Splash.setPosition(getSFWindow()->getSize().x/2.f,getSFWindow()->getSize().y/2.f);
			time += clock.getElapsedTime().asSeconds();
		}break;
	case GSTATE::Menu:
		{
		}break;
	case GSTATE::Play:
		{
			m_PhysicsManager	= new PhysicsSystem();
			m_PhysicsManager->enableDebugDraw(m_Window);
	
			ResourceProvider->loadTextureFromFile("soldier","soldier.png");
			ResourceProvider->loadTextureFromFile("zombie","zombie.png");
			ResourceProvider->loadSoundBufferFromFile("gun_m16_reload","gun_m16_reload.ogg");
			ResourceProvider->loadSoundBufferFromFile("gun_cock","gun_cock.ogg");
			ResourceProvider->loadSoundBufferFromFile("gun_shoot","gun_shoot.ogg");
			ResourceProvider->loadSoundBufferFromFile("gun_noammo","gun_noammo.ogg");
			ResourceProvider->loadSoundBufferFromFile("footsteps","footsteps.ogg");
	
			Controller->setKeyboardControl("forward",sf::Keyboard::Up);
			Controller->setKeyboardControl("backward",sf::Keyboard::Down);
			Controller->setKeyboardControl("exit",sf::Keyboard::Escape);
			Controller->setKeyboardControl("left",sf::Keyboard::Left);
			Controller->setKeyboardControl("right",sf::Keyboard::Right);
			Controller->setKeyboardControl("attack",sf::Keyboard::LControl);
			Controller->setKeyboardControl("reload",sf::Keyboard::LShift);
			Controller->setKeyboardControl("throw",sf::Keyboard::G);
			Controller->setKeyboardControl("delete",sf::Keyboard::Delete);
	
			m_Player		= new Entity();

			TransformableComponent* tr=new TransformableComponent();
			tr->setPosition(sf::Vector2f(250, 250));
			m_Player->addComponent(tr);

			SpriteComponent* sp=new SpriteComponent();
			sp->setSprite("soldier");
			m_Player->addComponent(sp);

			m_Player->initialise();
		}break;
	}
}

void Game::unLoad()
{
	switch (GameState->getCurrentState() - 1) //Unload object from previous state
	{
	case GSTATE::Splash:
		{
		} break;

	case GSTATE::Menu:
		{
		} break;

	case GSTATE::Play:
		{
			delete m_Player;
			delete m_PhysicsManager;
			m_PhysicsManager=nullptr;
		} break;
	}
}

void Game::play()
{
	float deltaTime		= clock.getElapsedTime().asSeconds();
	
	m_PhysicsManager->drawDebugData();
	m_PhysicsManager->update(deltaTime);
	
	DrawBatch->drawText("Test Text");
	DrawBatch->drawText("another test text",sf::Vector2f(100,100), 32, 15, sf::Color::Red, sf::Text::Underlined);
	
	m_Player->update(deltaTime);
	//if (Controller->getControl("delete"))
	//	delete m_Player;
	if (Controller->getControl("exit"))
		quit();

	clock.restart();
}
