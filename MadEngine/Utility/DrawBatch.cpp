#include "stdafx.h"
#include "DrawBatch.hpp"

Mad::Utility::DrawBatch::DrawBatch()
		: m_TargetWindow(nullptr), m_Font(nullptr), m_Text(nullptr), m_Sprite(
				nullptr), m_RectShape(nullptr), m_CircleShape(nullptr)
{
	m_Font = new sf::Font;
	m_Font->loadFromFile("Assets//Font//BuxtonSketch.ttf");
}

Mad::Utility::DrawBatch::~DrawBatch()
{
	this->cleanUp();
}

void Mad::Utility::DrawBatch::setDrawTarget(sf::RenderWindow& targetWindow)
{
	m_TargetWindow = &targetWindow;
}

sf::RenderTarget& Mad::Utility::DrawBatch::getRenderTarget()
{
	return *dynamic_cast<sf::RenderTarget*>(m_TargetWindow);
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
	m_Text = nullptr;

	delete m_Sprite;
	m_Sprite = nullptr;

	delete m_RectShape;
	m_RectShape = nullptr;

	delete m_CircleShape;
	m_CircleShape = nullptr;
}

void Mad::Utility::DrawBatch::drawText(const std::string& text,
		const sf::Vector2f& pos, float rot, int size, const sf::Color& color,
		sf::Text::Style style)
{
	if (m_Text == nullptr)
	{
		m_Text = new sf::Text;
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
