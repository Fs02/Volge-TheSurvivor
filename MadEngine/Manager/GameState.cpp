#include "stdafx.h"

#include "GameState.hpp"

Mad::Manager::GameState* Mad::Manager::GameState::getSingleton()
{
	if (instance == nullptr)
		instance	= new GameState();
		
	return instance;
}

Mad::Manager::GameState::States Mad::Manager::GameState::getCurrentState()
{
	return m_States;
}

void Mad::Manager::GameState::changeState(States state)
{
	m_States	= state;
}

Mad::Manager::GameState::GameState()
{
	m_States	= Uninitialized;
}

Mad::Manager::GameState::~GameState()
{
}

Mad::Manager::GameState *Mad::Manager::GameState::instance	= nullptr;
Mad::Manager::GameState::States Mad::Manager::GameState::m_States	= Mad::Manager::GameState::States::Uninitialized;

