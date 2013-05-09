#pragma once

#include "stdafx.h"

#include "MadEngine/MadEngine.hpp"
#include "PhysicsSystem.hpp"
#include "Entity/Human/Soldier.hpp"
#include "Entity/Zombie/Zombie.hpp"

class Game :
	public Mad::Interface::IGame
{
private:
	Mad::Graphics::Sprite		m_Splash;
	sf::Clock clock;
	float time;

	PhysicsSystem *m_PhysicsManager;

	Entity::Soldier*			m_Player;
	Entity::Zombie*				m_Zombie;

public:
	void initialize();
	void update();

	void splash();
	void menu();
	void load();
	void unLoad();
	void play();
};
