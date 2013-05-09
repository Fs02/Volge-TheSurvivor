#include "stdafx.h"
#include "IGame.hpp"

Mad::Interface::IGame::IGame()
{
	GameState		= Mad::Manager::GameState::getSingleton();
	ResourceProvider= Mad::Manager::Resource::getSingleton();
	Controller		= Mad::Manager::Controller::getSingleton();
	DrawBatch		= Mad::Utility::DrawBatch::getSingleton();

	isDisplayFrameStats		= false;
	b2debugDrawI			= nullptr;
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

void Mad::Interface::IGame::setUseSmoothTexture(bool flag)
{
	ResourceProvider->setSmoothTexture(flag);
}

void Mad::Interface::IGame::quit()
{
	isQuit				= true;
}

sf::RenderWindow* Mad::Interface::IGame::getSFWindow()
{
	return &m_Window;
}

void Mad::Interface::IGame::b2DebugDraw(b2World* world)
{
	if (b2debugDrawI == nullptr)
		b2debugDrawI		= new DebugDraw(m_Window);

	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        const b2Transform& xf = b->GetTransform();
        for (b2Fixture* fixture = b->GetFixtureList(); fixture; fixture = fixture->GetNext())
        {
            b2Color color = b2Color(0.5f, 0.5f, 0.3f);

            switch (fixture->GetType())
            {
                case b2Shape::e_circle:
                {
                    b2CircleShape* circle = (b2CircleShape*)fixture->GetShape();

                    b2Vec2 center = b2Mul(xf, circle->m_p);
                    float32 radius = circle->m_radius;
                    b2Vec2 axis = b2Mul(xf.q, b2Vec2(1.0f, 0.0f));

                    b2debugDrawI->DrawSolidCircle(center, radius, axis, color);
                }
                break;

                case b2Shape::e_edge:
                {
                    b2EdgeShape* edge = (b2EdgeShape*)fixture->GetShape();
                    b2Vec2 v1 = b2Mul(xf, edge->m_vertex1);
                    b2Vec2 v2 = b2Mul(xf, edge->m_vertex2);
                    b2debugDrawI->DrawSegment(v1, v2, color);
                }
                break;

                case b2Shape::e_chain:
                {
                    b2ChainShape* chain = (b2ChainShape*)fixture->GetShape();
                    int32 count = chain->m_count;
                    const b2Vec2* vertices = chain->m_vertices;

                    b2Vec2 v1 = b2Mul(xf, vertices[0]);
                    for (int32 i = 1; i < count; ++i)
                    {
                        b2Vec2 v2 = b2Mul(xf, vertices[i]);
                        b2debugDrawI->DrawSegment(v1, v2, color);
                        b2debugDrawI->DrawCircle(v1, 0.05f, color);
                        v1 = v2;
                    }
                }
                break;

                case b2Shape::e_polygon:
                {
                    b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
                    int32 vertexCount = poly->m_vertexCount;
                    b2Assert(vertexCount <= b2_maxPolygonVertices);
                    b2Vec2 vertices[b2_maxPolygonVertices];

                    for (int32 i = 0; i < vertexCount; ++i)
                    {
                        vertices[i] = b2Mul(xf, poly->m_vertices[i]);
                    }

                    b2debugDrawI->DrawSolidPolygon(vertices, vertexCount, color);
                }
                break;

                default:
                break;
            }
        }
    }
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

			std::cout<<GameState->getCurrentState()<<" | "<<gstate<<std::endl;
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
	ResourceProvider->loadTextureFromFile("MadEngine","MadEngine.png");
	m_Logo.setTexture("MadEngine");
	m_Logo.setOrigin(m_Logo.getSize().x/2, m_Logo.getSize().y);
	m_Logo.setPosition(400,300);
}

void Mad::Interface::IGame::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) GameState->changeState(Mad::Manager::GameState::Exit);

	//Start Drawing to window
	DrawBatch->begin();
	//Draw Stuff Here
	m_Logo.draw();

	DrawBatch->end();
}

void Mad::Interface::IGame::unLoad()
{
}
