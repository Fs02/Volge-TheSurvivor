#include "stdafx.h"
#include "Sprite.hpp"

Mad::Graphics::Sprite::Sprite()
{
	if (DrawBatch != nullptr)
		DrawBatch		= Mad::Utility::DrawBatch::getSingleton();

	m_Angle			= 0.f;

	m_Rect.height	= 0;
	m_Rect.width	= 0;
}

Mad::Graphics::Sprite::Sprite(const std::string& textureId)
{
	if (DrawBatch != nullptr)
		DrawBatch		= Mad::Utility::DrawBatch::getSingleton();

	m_TextureId		= textureId;
	m_Angle			= 0.f;
	m_Size			= (sf::Vector2f)Mad::Manager::Resource::get<Mad::Graphics::Texture>(m_TextureId)->getSize();

	m_Rect.height	= 0;
	m_Rect.width	= 0;
}

Mad::Graphics::Sprite::Sprite(const std::string& textureId, const sf::IntRect& rectArea)
{
	if (DrawBatch != nullptr)
		DrawBatch		= Mad::Utility::DrawBatch::getSingleton();

	m_TextureId		= textureId;
	m_Angle			= 0.f;	
	m_Size			= (sf::Vector2f)Mad::Manager::Resource::get<Mad::Graphics::Texture>(m_TextureId)->getSize();
	m_Rect			= rectArea;
}

Mad::Graphics::Sprite::~Sprite()
{
}

sf::Texture& Mad::Graphics::Sprite::getTexture()
{
	return Mad::Manager::Resource::get<Mad::Graphics::Texture>(m_TextureId)->getTexture();
}

void Mad::Graphics::Sprite::draw()
{
	if (m_Rect.width == 0 && m_Rect.height == 0)
		DrawBatch->drawSprite(m_TextureId, m_Position, m_Angle, m_Origin);
	else
		DrawBatch->drawSprite(m_TextureId,m_Rect, m_Position, m_Angle, m_Origin);
}

void Mad::Graphics::Sprite::setTexture(const std::string& textureId)
{
	m_TextureId		= textureId;
	m_Size			= (sf::Vector2f)Mad::Manager::Resource::get<Mad::Graphics::Texture>(m_TextureId)->getSize();
}

void Mad::Graphics::Sprite::setTextureRect(const sf::IntRect& rectArea)
{
	m_Rect			= rectArea;
}

void Mad::Graphics::Sprite::setPosition(float x, float y)
{
	m_Position.x	= x;
	m_Position.y	= y;
}

void Mad::Graphics::Sprite::setPosition(const sf::Vector2f& Position)
{
	m_Position		= Position;
}

void Mad::Graphics::Sprite::setRotation(float angle)
{
	m_Angle			= angle;
}

void Mad::Graphics::Sprite::setOrigin(float x, float y)
{
	m_Origin.x		= x;
	m_Origin.y		= y;
}

void Mad::Graphics::Sprite::setOrigin(const sf::Vector2f& Origin)
{
	m_Origin			= Origin;
}

sf::Vector2f& Mad::Graphics::Sprite::getPosition()
{
	return m_Position;
}

float Mad::Graphics::Sprite::getRotation()
{
	return m_Angle;
}

sf::Vector2f& Mad::Graphics::Sprite::getOrigin()
{
	return m_Origin;
}

sf::Vector2f& Mad::Graphics::Sprite::getSize()
{
	return m_Size;
}

std::string& Mad::Graphics::Sprite::getTextureId() 
{
	return m_TextureId;
}