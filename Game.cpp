#include "stdafx.h"
#include "Game.hpp"
#include "Entity/Components/HealthComponent.hpp"
#include "Entity/Components/SpriteComponent.hpp"
#include "Entity/Components/TransformableComponent.hpp"
#include "Entity/Components/PhysicsComponent.hpp"
#include "Entity/Components/PlayerCtrlComponent.hpp"
#include "Entity/Components/CameraComponent.hpp"
#include "Entity/Components/SoundComponent.hpp"

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
	setDisplayStatistics(true);
	time = 0;

	GameState->changeState(GSTATE::Splash);
	Controller=Mad::Manager::Controller::getSingleton();

	m_PhysicsManager = nullptr;
}

void Game::update()
{
	switch (GameState->getCurrentState())
	{
	case GSTATE::Splash:
		{
		splash();
		m_Splash.draw(0);
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
{	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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
			ResourceProvider->load<Mad::Graphics::Texture>("volge.png","volge.png");
			ResourceProvider->load<Mad::Graphics::Texture>("soldier.png", "soldier.png");
			ResourceProvider->load<Mad::Graphics::SpriteData>("volge.json", "volge.json");
			ResourceProvider->load<Mad::Graphics::SpriteData>("soldier.json", "soldier.json");

			m_Splash.setSource("volge.json");
			m_Splash.setPosition(b2Vec2(getSFWindow()->getSize().x/2.f,getSFWindow()->getSize().y/2.f));
			time += clock.getElapsedTime().asSeconds();
		}break;
	case GSTATE::Menu:
		{
		}break;
	case GSTATE::Play:
		{
			m_PhysicsManager	= new PhysicsSystem();
			m_PhysicsManager->enableDebugDraw(m_Window);
	
			ResourceProvider->load<Mad::Graphics::Texture>("soldier","soldier.png");
			ResourceProvider->load<Mad::Graphics::Texture>("zombie","zombie.png");
			ResourceProvider->load<Mad::Sound::SoundBuffer>("gun_m16_reload","gun_m16_reload.ogg");
			ResourceProvider->load<Mad::Sound::SoundBuffer>("gun_cock","gun_cock.ogg");
			ResourceProvider->load<Mad::Sound::SoundBuffer>("gun_shoot","gun_shoot.ogg");
			ResourceProvider->load<Mad::Sound::SoundBuffer>("gun_noammo","gun_noammo.ogg");
			ResourceProvider->load<Mad::Sound::SoundBuffer>("footsteps","footsteps.ogg");
	
			Controller->setKeyboardControl("forward",sf::Keyboard::Up);
			Controller->setKeyboardControl("backward",sf::Keyboard::Down);
			Controller->setKeyboardControl("exit",sf::Keyboard::Escape);
			Controller->setKeyboardControl("left",sf::Keyboard::Left);
			Controller->setKeyboardControl("right",sf::Keyboard::Right);
			Controller->setKeyboardControl("attack",sf::Keyboard::LControl);
			Controller->setKeyboardControl("reload",sf::Keyboard::LShift);
			Controller->setKeyboardControl("throw",sf::Keyboard::G);
	
			m_Player		= new Entity();

			m_Player->addComponent(new PlayerCtrlComponent());

			TransformableComponent* tr=new TransformableComponent();
			tr->setPosition(b2Vec2(250, 250));
			m_Player->addComponent(tr);

			SpriteComponent* sp=new SpriteComponent();
			sp->setSprite("soldier.json");
			sp->setSize(b2Vec2(1, 1));
			m_Player->addComponent(sp);

			CameraComponent* cam=new CameraComponent();
			cam->setVirtualSize(b2Vec2(10, 10));
			cam->makeActive();
			m_Player->addComponent(cam);

			PhysicsDef phDef;
			phDef.shape=PhysicsShape::Circle;
			phDef.friction=0.5f;
			phDef.mass=80.0f;
			phDef.circle.radius=0.5f;

			PhysicsComponent* ph=new PhysicsComponent(m_PhysicsManager, phDef, 0xffffffff);
			m_Player->addComponent(ph);

			SoundComponent* sc = new SoundComponent();
			sc->addSound("Idle", "gun_noammo", true);
			m_Player->addComponent(sc);

			m_Player->initialise();
			m_Player->onGenericEvent("Idle");

			m_Obstacle		=new Entity();

			tr=new TransformableComponent();
			tr->setPosition(b2Vec2(250, 270));
			m_Obstacle->addComponent(tr);

			phDef.shape=PhysicsShape::Box;
			phDef.friction=0.5f;
			phDef.mass=0;
			phDef.box.size.Set(2, 2);

			ph=new PhysicsComponent(m_PhysicsManager, phDef, ~0);
			m_Obstacle->addComponent(ph);

			m_Obstacle->initialise();
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
	
	m_PhysicsManager->update(deltaTime);
	m_PhysicsManager->drawDebugData();
	
	DrawBatch->drawText("Test Text");
	DrawBatch->drawText("another test text",sf::Vector2f(100,100), 32, 15, sf::Color::Red, sf::Text::Underlined);

	m_Player->update(deltaTime);
	m_Obstacle->update(deltaTime);
	
	if (Controller->getControl("exit"))
		quit();

	clock.restart();
}
