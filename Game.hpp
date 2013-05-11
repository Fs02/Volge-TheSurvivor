#pragma once

#include "stdafx.h"

#include "MadEngine/MadEngine.hpp"
#include "PhysicsSystem.hpp"
#include "Entity/Components/HealthComponent.hpp"
#include "Entity/Components/SpriteComponent.hpp"
#include "Entity/Components/TransformableComponent.hpp"
#include "Entity/Components/PhysicsComponent.hpp"

class Game :
	public Mad::Interface::IGame
{
private:
	Mad::Graphics::Sprite		m_Splash;
	sf::Clock clock;
	float time;

	PhysicsSystem *m_PhysicsManager;

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
