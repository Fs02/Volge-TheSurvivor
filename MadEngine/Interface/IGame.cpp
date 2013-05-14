#include "stdafx.h"
#include "IGame.hpp"

Mad::Interface::IGame::IGame()
{
	GameState		= Mad::Manager::GameState::initialise();
	ResourceProvider= Mad::Manager::Resource::initialise();
	Controller		= Mad::Manager::Controller::initialise();
	Graphics		= Mad::Manager::Graphics::initialise();

	isDisplayFrameStats		= false;
	isQuit					= false;
}

Mad::Interface::IGame::~IGame()
{
	GameState->deinitialise();
	ResourceProvider->deinitialise();
	Controller->deinitialise();
	Graphics->deinitialise();
}

void Mad::Interface::IGame::setDisplayStatistics(bool flag)
{
	isDisplayFrameStats	= true;
}

void Mad::Interface::IGame::quit()
{
	isQuit				= true;
}

void Mad::Interface::IGame::start()
{
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
			
			Graphics->getRenderWindow().pollEvent(m_Event);
			
			if (m_Event.type == sf::Event::Closed) 
				quit();
		
			Graphics->getRenderWindow().clear();
			
			update();

			if (isDisplayFrameStats)
			{
				frameStats.endFrame();
				Graphics->beginRendering();
					Graphics->getRenderTarget().draw(*StatsHUD);
				Graphics->endRendering();
			}
			Graphics->getRenderWindow().display();

			if (GameState->getCurrentState() != gstate)
				loaded	= false;

		} while ((loaded == true) && (isQuit == false));
		unLoad();
	}
	
	cleanUp();
}

void Mad::Interface::IGame::cleanUp()
{
	Graphics->getDrawBatch().cleanUp();
	Graphics->getRenderWindow().close();
}

void Mad::Interface::IGame::initialize()
{
}

void Mad::Interface::IGame::load()
{
}

void Mad::Interface::IGame::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) quit();
}

void Mad::Interface::IGame::unLoad()
{
}
