#include "stdafx.h"
#include "Game.hpp"

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

	GameState->changeState(Mad::Manager::GameState::Splash);

	m_PhysicsManager = nullptr;
}

void Game::update()
{
	switch (GameState->getCurrentState())
	{
	case Mad::Manager::GameState::Splash:
		{
		splash();
		m_Splash.draw();
		}break;
	case Mad::Manager::GameState::Menu:
		{
		menu();
		}break;
	case Mad::Manager::GameState::Play:
		{
			b2DebugDraw(m_World);
			play();
		}break;
	}
}

void Game::splash()
{	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	//if (time >100.f)
		GameState->changeState(GameState->Menu);
}

void Game::menu()
{
	GameState->changeState(GameState->Play);
}

void Game::load()
{
	switch (GameState->getCurrentState())
	{
	case Mad::Manager::GameState::Splash:
		{
			ResourceProvider->loadTextureFromFile("volge","volge.png");

			m_Splash.setTexture("volge");
			m_Splash.setOrigin(m_Splash.getSize().x/2.f, m_Splash.getSize().y/2.f);
			m_Splash.setPosition(getSFWindow()->getSize().x/2.f,getSFWindow()->getSize().y/2.f);
			time += clock.getElapsedTime().asSeconds();
		}break;
	case Mad::Manager::GameState::Menu:
		{
		}break;
	case Mad::Manager::GameState::Play:
		{
			m_World				= new b2World(b2Vec2(0.f,0.f));
			m_PhysicsManager	= new PhysicsSystem(m_World);
	
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
	
			b2BodyDef def;
			def.type		= b2_staticBody;
			def.position.Set(10,10);
			b2Body* newBody	= m_World->CreateBody(&def);
	
			b2PolygonShape shape;
			shape.SetAsBox(1,0.5f);
			newBody->CreateFixture(&shape,1.f);
	
			m_Player		= new Entity::Soldier(m_World);
			m_Zombie		= new Entity::Zombie(m_World);
		}break;
	}
}

void Game::unLoad()
{
}

void Game::play()
{
	DrawBatch->drawText("Test Text");
	DrawBatch->drawText("another test text",sf::Vector2f(100,100), 32, 15, sf::Color::Red, sf::Text::Underlined);
	
	m_Player->update();
	m_Player->draw();

	m_Zombie->update();
	m_Zombie->draw();
	//if (Controller->getControl("delete"))
	//	delete m_Player;
	if (Controller->getControl("exit"))
		quit();

	//m_PhysicsManager->update(clock.getElapsedTime().asSeconds());
	//clock.restart();
	m_World->Step(clock.getElapsedTime().asSeconds(),8,8);
	clock.restart();
	m_PhysicsManager->processBuffer();
}