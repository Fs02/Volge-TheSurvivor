#include "stdafx.h"
#include "IGame.hpp"

Mad::Interface::IGame::IGame()
{
	GameState		= Mad::Manager::GameState::getSingleton();
	ResourceProvider= Mad::Manager::Resource::getSingleton();
	Controller		= Mad::Manager::Controller::getSingleton();
	DrawBatch		= Mad::Utility::DrawBatch::getSingleton();

	isDisplayFrameStats		= false;
	isQuit					= false;
}

Mad::Interface::IGame::~IGame()
{
}

void Mad::Interface::IGame::create(unsigned int windowWidth, unsigned int windowHeight, unsigned int BitsPerPixel, const std::string& title, bool fullScreen)
{
	if (fullScreen)
		m_Window.create(sf::VideoMode(windowWidth, windowHeight, BitsPerPixel), title, sf::Style::Fullscreen);
	else
		m_Window.create(sf::VideoMode(windowWidth, windowHeight, BitsPerPixel), title, sf::Style::Close);
}

void Mad::Interface::IGame::setFrameLimit(unsigned int limit)
{
	m_Window.setFramerateLimit(limit);
}

void Mad::Interface::IGame::setVerticalSyncEnabled(bool flag)
{
	m_Window.setVerticalSyncEnabled(flag);
}

void Mad::Interface::IGame::setMouseCursorVisible(bool flag)
{
	m_Window.setMouseCursorVisible(flag);
}

void Mad::Interface::IGame::setDisplayStatistics(bool flag)
{
	isDisplayFrameStats	= true;
}

void Mad::Interface::IGame::quit()
{
	isQuit				= true;
}

sf::RenderWindow* Mad::Interface::IGame::getSFWindow()
{
	return &m_Window;
}

void Mad::Interface::IGame::start()
{
	DrawBatch->setDrawTarget(m_Window);

	initialize();

	sf::Font hudFont;
	hudFont.loadFromFile("Assets/Font/BuxtonSketch.ttf");
	
	ClockHUD *StatsHUD;
	if (isDisplayFrameStats)
		StatsHUD	= new ClockHUD(frameStats, hudFont);

	while (isQuit == false)
	{
		int gstate	= GameState->getCurrentState();
		
		load();
		bool loaded = true;

		do
		{
			if (isDisplayFrameStats)
				frameStats.beginFrame();
			
			m_Window.pollEvent(m_Event);
			
			if (m_Event.type == sf::Event::Closed) 
				quit();
		
			m_Window.clear();
			
			update();

			if (isDisplayFrameStats)
			{
				//m_Window.pushGLStates();
				m_Window.draw(*StatsHUD);
				//m_Window.popGLStates();
				frameStats.endFrame();
			}
			m_Window.display();

			if (GameState->getCurrentState() != gstate)
				loaded	= false;

		} while ((loaded == true) && (isQuit == false));
		unLoad();
	}
	
	cleanUp();
}

void Mad::Interface::IGame::cleanUp()
{
	DrawBatch->cleanUp();
	m_Window.close();
}

void Mad::Interface::IGame::initialize()
{
	create(800,600,32,"MadEngine SDK");
}

void Mad::Interface::IGame::load()
{
}

void Mad::Interface::IGame::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) quit();

	//Start Drawing to window
	DrawBatch->begin();
	//Draw Stuff Here

	DrawBatch->end();
}

void Mad::Interface::IGame::unLoad()
{
}
