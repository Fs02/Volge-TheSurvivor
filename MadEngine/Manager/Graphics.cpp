#include "Graphics.hpp"
#include "Exceptions.hpp"
#include <cassert>

Mad::Manager::Graphics* Mad::Manager::Graphics::ms_Singleton=nullptr;

void Mad::Manager::Graphics::createWindow(const std::string& title, int w,
		int h)
{
	m_Window.create(sf::VideoMode(w, h), title);
	m_GameView=m_DefView=m_Window.getView();
}

sf::RenderTarget& Mad::Manager::Graphics::getRenderTarget()
{
	return dynamic_cast<sf::RenderTarget&>(m_Window);
}

sf::RenderWindow& Mad::Manager::Graphics::getRenderWindow()
{
	return m_Window;
}

float Mad::Manager::Graphics::getAspectRatio() const
{
	sf::Vector2u s=m_Window.getSize();
	return (float)s.x/s.y;
}

sf::View& Mad::Manager::Graphics::getGameView()
{
	return m_GameView;
}

sf::View& Mad::Manager::Graphics::getDefaultView()
{
	return m_DefView;
}

Mad::Utility::DrawBatch& Mad::Manager::Graphics::getDrawBatch()
{
	return *Utility::DrawBatch::getSingleton();
}

void Mad::Manager::Graphics::beginGameRendering()
{
	if(m_InsideBeginEnd)
		throw Exceptions::Error("beginGameRendering() has been called between begin* and end* calls!");
	m_InsideBeginEnd=true;

	m_Window.setActive(true);
	m_Window.setView(m_GameView);
}

void Mad::Manager::Graphics::endGameRendering()
{
	m_InsideBeginEnd=false;
}

void Mad::Manager::Graphics::beginRendering()
{
	if(m_InsideBeginEnd)
		throw Exceptions::Error("beginRendering() has been called between begin* and end* calls!");
	m_InsideBeginEnd=true;

	m_Window.setActive(true);
	m_Window.setView(m_DefView);
}

void Mad::Manager::Graphics::endRendering()
{
	m_InsideBeginEnd=false;
}

Mad::Manager::Graphics* Mad::Manager::Graphics::getSingleton()
{
	return ms_Singleton;
}

Mad::Manager::Graphics* Mad::Manager::Graphics::initialise()
{
	assert(!ms_Singleton);
	ms_Singleton=new Graphics();
	return ms_Singleton;
}

void Mad::Manager::Graphics::deinitialise()
{
	delete ms_Singleton;
	ms_Singleton=nullptr;
}

Mad::Manager::Graphics::Graphics()
	:m_InsideBeginEnd(false)
{
}

Mad::Manager::Graphics::~Graphics()
{
}
