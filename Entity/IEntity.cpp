#pragma once

#include "stdafx.h"
#include "IEntity.hpp"

Entity::IEntity::IEntity()
{
}

Entity::IEntity::~IEntity()
{
}

const std::string& Entity::IEntity::getName() const
{
	return m_Name;
}

const std::string& Entity::IEntity::getFamilyName() const
{
	return m_FamilyName;
}