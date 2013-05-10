#include "../../stdafx.h"
#include "Controller.hpp"

Mad::Manager::Controller::Controller()
{
}

Mad::Manager::Controller::~Controller()
{
	m_KeyMap.clear();
}

Mad::Manager::Controller *Mad::Manager::Controller::getSingleton()
{
	if (instance == nullptr)
		instance	= new Controller;

	return instance;
}

bool Mad::Manager::Controller::getControl(const std::string& name)
{
	if (m_KeyMap.find(name) == m_KeyMap.end())
		throw Mad::Manager::Exceptions::InvalidKey("Controller index");

	if ((m_KeyMap[name].ControllerType	== Keyboard) &&
		sf::Keyboard::isKeyPressed(m_KeyMap[name].KeyboardCode))
	{
		return true;
	}

	if ((m_KeyMap[name].ControllerType	== Mouse) &&
		sf::Mouse::isButtonPressed(m_KeyMap[name].mouseButton))
	{
		return true;
	}
	
	return false;
}

void Mad::Manager::Controller::setKeyboardControl(const std::string& name, sf::Keyboard::Key keyboardCode)
{
	m_KeyMap[name].ControllerType	= Keyboard;
	m_KeyMap[name].KeyboardCode		= keyboardCode;
}

void Mad::Manager::Controller::setMouseControl(const std::string& name, sf::Mouse::Button mouseButtonCode)
{
	m_KeyMap[name].ControllerType	= Mouse;
	m_KeyMap[name].mouseButton		= mouseButtonCode;
}

Mad::Manager::Controller								*Mad::Manager::Controller::instance			= nullptr;
std::map<std::string, Mad::Manager::Controller::Keys>	Mad::Manager::Controller::m_KeyMap;
