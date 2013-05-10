#include "../../stdafx.h"

#include "GameState.hpp"

Mad::Manager::GameState* Mad::Manager::GameState::getSingleton()
{
	if (instance == nullptr)
		instance	= new GameState();
		
	return instance;
}

int Mad::Manager::GameState::getCurrentState()
{
	return m_States;
}

void Mad::Manager::GameState::changeState(int state)
{
	m_States	= state;
}

Mad::Manager::GameState::GameState()
{
	m_States	= 0;
}

Mad::Manager::GameState::~GameState()
{
}

Mad::Manager::GameState *Mad::Manager::GameState::instance	= nullptr;
int Mad::Manager::GameState::m_States						= 0;

