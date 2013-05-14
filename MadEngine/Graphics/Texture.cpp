#include "Texture.hpp"

Mad::Graphics::Texture::Texture()
{
	m_Size			= sf::Vector2u(0,0);
}

Mad::Graphics::Texture::Texture(const std::string& file, sf::IntRect area)
{
	loadFromFile(file,area);
}

Mad::Graphics::Texture::Texture(sf::Texture& sfTexture)
{
	loadFromSFTexture(sfTexture);
}

Mad::Graphics::Texture::~Texture()
{
}

void Mad::Graphics::Texture::loadFromFile(const std::string& file, sf::IntRect area)
{
	if (!m_Data.loadFromFile(file, area))
		throw Mad::Manager::Exceptions::FileNotFound();
	m_Size			= m_Data.getSize();
}

void Mad::Graphics::Texture::loadFromSFTexture(sf::Texture& sfTexture)
{
	m_Data			= sfTexture;
	m_Size			= m_Data.getSize();
}

void Mad::Graphics::Texture::setSmooth(bool flag)
{
	m_Data.setSmooth(flag);
}

void Mad::Graphics::Texture::setRepeated(bool flag)
{
	m_Data.setSmooth(flag);
}

sf::Vector2u& Mad::Graphics::Texture::getSize()
{
	return m_Size;
}

sf::Texture& Mad::Graphics::Texture::getTexture()
{
	return m_Data;
}