#include "Entity.hpp"
#include <fstream>
#include "../3rdParty/rapidxml-1.13/rapidxml.hpp"
#include "PhysicsSystem.hpp"
#include "Components/CameraComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Components/PhysicsComponent.hpp"
#include "Components/PlayerCtrlComponent.hpp"
#include "Components/SoundComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/TransformableComponent.hpp"
#include "Components/WeaponComponent.hpp"

/*
 * CommonStates
 */

const std::string CommonStates::Idle="Idle";
const std::string CommonStates::Dead="Dead";

/*
 * Entity
 */

Entity::Entity()
	:m_IsRedundant(false)
{
}

Entity::~Entity()
{
	for(unsigned int i=0; i < m_components.size(); ++i)
		delete m_components[i];
}

void Entity::initialise()
{
	for(unsigned int i=0; i < m_components.size(); ++i)
		m_components[i]->initialise(this);
}

void Entity::addComponent(IComponent* comp)
{
	if(!comp)
		return;
	for(unsigned int i=0; i < m_components.size(); ++i)
		if(m_components[i] == comp)
			return;
	m_components.push_back(comp);
}

void Entity::removeComponent(IComponent *comp)
{
    for(auto iter = m_components.begin(); iter != m_components.end(); ++iter)
    {
        if(comp == (*iter))
        {
            delete comp;
            m_components.erase(iter);
            return;
        }
    }
}

std::list<const IComponent*> Entity::listComponents() const
{
	std::list<const IComponent*> result;
	for(size_t i=0; i < m_components.size(); ++i)
		result.push_back(m_components[i]);
	return result;
}

void Entity::loadComponent(const std::string& fileName)
{
	this->addComponent(new PlayerCtrlComponent());

	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* root_node;

	// Read the xml file into a vector
	std::ifstream theFile(fileName);
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	root_node = doc.first_node("Entity");
	for (rapidxml::xml_node<> * comp_node = root_node->first_node("Component"); comp_node; comp_node = comp_node->next_sibling())
	{
		rapidxml::xml_node<>* params_node = comp_node->first_node("params");
		std::string params_name;
		std::string comp_name = comp_node->first_attribute("name")->value();
		if (comp_name == "TransformableComponent")
		{
			TransformableComponent* tc = new TransformableComponent();
			tc->setPosition(b2Vec2(250, 250));
			this->addComponent(tc);
		}
		else if (comp_name == "SpriteComponent")
		{
			SpriteComponent* sc = new SpriteComponent();
			for (params_node; params_node; params_node = params_node->next_sibling())
			{
				params_name	= params_node->first_attribute("name")->value();
				if (params_name == "SpriteData")
				{
					sc->setSprite(params_node->first_attribute("value")->value());
				}
				else if (params_name == "Size")
				{
					sc->setSize(b2Vec2(std::stof(params_node->first_attribute("x")->value()), std::stof(params_node->first_attribute("y")->value())));
				}
				else;
			}
			this->addComponent(sc);
			
		}
		else if (comp_name == "CameraComponent")
		{
			CameraComponent* cm = new CameraComponent();
			for (params_node; params_node; params_node = params_node->next_sibling())
			{
				if (params_name == "Size")
					cm->setVirtualSize(b2Vec2(std::stof(params_node->first_attribute("x")->value()), std::stof(params_node->first_attribute("y")->value())));
				else;
			}
			cm->makeActive();
			this->addComponent(cm);
		}
		else if (comp_name == "WeaponComponent")
		{
			WeaponComponent* wp = new WeaponComponent(PhysicsSystem::getSingleton());
			params_name = params_node->first_attribute("name")->value();
			if (params_name == "Type")
			{
				//better with json
				if (params_name == "M16")
				{
					Item::Gun* gun = new Item::Gun("M16", 20, 30, 30, 0.5f, 0.1f);
					wp->setGun(gun);
				}
				this->addComponent(wp);
			}
		}
		else if (comp_name == "PhysicsComponent")
		{
			params_name = params_node->first_attribute("name")->value();
			PhysicsComponent* ph;
			if (params_name == "def")
			{
				//better with json
				PhysicsDef phDef;
				phDef.shape = PhysicsShape::Circle;
				phDef.friction = 0.5f;
				phDef.mass = 80.0f;
				phDef.circle.radius = 0.5f;
				ph = new PhysicsComponent(PhysicsSystem::getSingleton(), phDef,
				0xffffffff);
			}
			this->addComponent(ph);
		}
		else if (comp_name == "SoundComponent")
		{
			SoundComponent* sc = new SoundComponent();
			for (params_node; params_node; params_node = params_node->next_sibling())
			{
				sc->addSound(params_node->first_attribute("name")->value()
					, params_node->first_attribute("value")->value()
					, true);
			}
		}
		else;
	}
	initialise();
}

void Entity::update(float deltaTime)
{
	for(unsigned int i=0; i < m_components.size(); ++i)
		m_components[i]->update(deltaTime);
}

void Entity::onCollisionBegin(Entity* other)
{
	for(unsigned int i=0; i < m_components.size(); ++i)
		m_components[i]->onCollisionBegin(other);
}

void Entity::onCollisionEnd(Entity* other)
{
	for(unsigned int i=0; i < m_components.size(); ++i)
		m_components[i]->onCollisionEnd(other);
}

void Entity::onDamage(Entity* other, int damage)
{
	for(unsigned int i=0; i < m_components.size(); ++i)
		m_components[i]->onDamage(other, damage);
}

void Entity::onStateChanged(const std::string& stateName)
{
	for(unsigned int i=0; i < m_components.size(); ++i)
		m_components[i]->onStateChanged(stateName);
}

void Entity::onGenericEvent(const std::string& name)
{
	for(unsigned int i=0; i < m_components.size(); ++i)
		m_components[i]->onGenericEvent(name);
}

void Entity::markAsRedundant()
{
	m_IsRedundant=true;
}

bool Entity::isRedundant() const
{
	return m_IsRedundant;
}

/*
 * IComponent
 */

IComponent::~IComponent()
{
}

void IComponent::onCollisionBegin(Entity* other)
{
}

void IComponent::onCollisionEnd(Entity* other)
{
}

void IComponent::onDamage(Entity* other, int damage)
{
}

void IComponent::onStateChanged(const std::string& stateName)
{
}

void IComponent::onGenericEvent(const std::string& name)
{
}
