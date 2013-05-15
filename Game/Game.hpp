#pragma once

#include "stdafx.h"

class Game :
	public Mad::Interface::IGame
{
private:
	Mad::Graphics::Sprite		m_Splash;
	sf::Clock clock;
	float time;

	PhysicsSystem *m_PhysicsManager;
	EntityManager* m_EntityManager;

	Entity*			m_Player;
	Entity*			m_Obstacle;

public:
	void initialize();
	void update();

	void splash();
	void menu();
	void load();
	void unLoad();
	void play();
};
