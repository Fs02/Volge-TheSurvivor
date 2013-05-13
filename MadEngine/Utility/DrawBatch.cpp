#include "stdafx.h"
#include "DrawBatch.hpp"

Mad::Utility::DrawBatch::DrawBatch()
{
	m_Font			= new sf::Font;
	m_Font->loadFromFile("Assets//Font//BuxtonSketch.ttf");
}

Mad::Utility::DrawBatch::~DrawBatch()
{
}

Mad::Utility::DrawBatch* Mad::Utility::DrawBatch::initialise()
{
	return getSingleton();
}

void Mad::Utility::DrawBatch::deinitialise()
{
	delete instance;
	instance		= nullptr;
}

Mad::Utility::DrawBatch *Mad::Utility::DrawBatch::getSingleton()
{
	if (instance == nullptr)
		instance	= new DrawBatch();

	return instance;
}

void Mad::Utility::DrawBatch::setDrawTarget(sf::RenderWindow& targetWindow)
{
	m_TargetWindow	= &targetWindow;
}

sf::RenderTarget& Mad::Utility::DrawBatch::getRenderTarget()
{
	return *(sf::RenderTarget*)&m_TargetWindow;
}

void Mad::Utility::DrawBatch::begin()
{
	m_TargetWindow->pushGLStates();
}

void Mad::Utility::DrawBatch::end()
{
	m_TargetWindow->popGLStates();
}

void Mad::Utility::DrawBatch::cleanUp()
{
	delete m_Text;
	m_Text			= nullptr;

	delete m_Sprite;
	m_Sprite		= nullptr;

	delete m_RectShape;
	m_RectShape		= nullptr;

	delete m_CircleShape;
	m_CircleShape	= nullptr;
}

void Mad::Utility::DrawBatch::drawText(const std::string& text, const sf::Vector2f& pos, float rot, int size, const sf::Color& color, sf::Text::Style style)
{
	if (m_Text == nullptr)		
	{
		m_Text		= new sf::Text;
		m_Text->setFont(*m_Font);
	}

	m_Text->setString(text);
	m_Text->setCharacterSize(size);
	m_Text->setColor(color);
	m_Text->setStyle(style);
	m_Text->setPosition(pos);
	m_Text->setRotation(rot);
	m_TargetWindow->draw(*m_Text);
}

///

void Mad::Utility::DrawBatch::drawSprite(const sf::Sprite& sprite)
{
	m_TargetWindow->draw(sprite);
}

void Mad::Utility::DrawBatch::drawSprite(const std::string& textureId, const sf::Vector2f& pos, float rot, const sf::Vector2f& origin)
{
	if (m_Sprite == nullptr)	m_Sprite	= new sf::Sprite;

	m_Sprite->setTexture(Mad::Manager::Resource::get<Mad::Graphics::Texture>(textureId)->getTexture());

	m_Sprite->setTextureRect(sf::IntRect(0,0,m_Sprite->getTexture()->getSize().x, m_Sprite->getTexture()->getSize().y));
	m_Sprite->setPosition(pos);
	m_Sprite->setRotation(rot);
	m_Sprite->setOrigin(origin);
	m_TargetWindow->draw(*m_Sprite);
}

void Mad::Utility::DrawBatch::drawSprite(const std::string& textureId, const sf::IntRect& area, const sf::Vector2f& pos, float rot, const sf::Vector2f& origin)
{
	if (m_Sprite == nullptr)	m_Sprite	= new sf::Sprite;

	m_Sprite->setTexture(Mad::Manager::Resource::get<Mad::Graphics::Texture>(textureId)->getTexture());
	m_Sprite->setTextureRect(area);
	m_Sprite->setPosition(pos);
	m_Sprite->setRotation(rot);
	m_Sprite->setOrigin(origin);
	m_TargetWindow->draw(*m_Sprite);
}

Mad::Utility::DrawBatch	*Mad::Utility::DrawBatch::instance			= nullptr;
sf::RenderWindow		*Mad::Utility::DrawBatch::m_TargetWindow	= nullptr;
Mad::Manager::Resource	*Mad::Utility::DrawBatch::m_ResourceMan		= nullptr;

sf::Font				*Mad::Utility::DrawBatch::m_Font			= nullptr;
sf::Text				*Mad::Utility::DrawBatch::m_Text			= nullptr;
sf::Sprite				*Mad::Utility::DrawBatch::m_Sprite			= nullptr;
sf::RectangleShape		*Mad::Utility::DrawBatch::m_RectShape		= nullptr;
sf::CircleShape			*Mad::Utility::DrawBatch::m_CircleShape		= nullptr;
