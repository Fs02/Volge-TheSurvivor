#include "EntityManager.hpp"
#include <iostream>
#include "Components/CameraComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Components/PhysicsComponent.hpp"
#include "Components/PlayerCtrlComponent.hpp"
#include "Components/SoundComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/TransformableComponent.hpp"
#include "Components/WeaponComponent.hpp"

EntityManager::EntityManager(PhysicsSystem *pm)
{
	m_PhysicsManager = pm;
	m_Listener	= nullptr;
}

EntityManager::~EntityManager()
{
}

void EntityManager::setListener(IEntityMgrListener *listener)
{
    m_Listener=listener;
}

Entity *EntityManager::createEntity(const std::string& name)
{
    if(m_Entities.count(name) == 1)
        return nullptr;
    Entity* ent=new Entity();
	    m_Entities[name]=ent;
    if(m_Listener != nullptr)
       m_Listener->onEntityAdded(name, ent);
    return ent;
}

Entity* EntityManager::getEntity(const std::string &name)
{
    auto iter=m_Entities.find(name);
    if(iter == m_Entities.end())
        return nullptr;
    return iter->second;
}

const Entity* EntityManager::getEntity(const std::string &name) const
{
    auto iter=m_Entities.find(name);
    if(iter == m_Entities.end())
        return nullptr;
    return iter->second;
}

/*
void EntityManager::loadEntity(const std::string& fileName)
{
	Entity* ent = new Entity();
	ent->addComponent(new PlayerCtrlComponent());

	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* root_node;

	// Read the xml file into a vector
	std::ifstream theFile (fileName);
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
			ent->addComponent(tc);
			std::cout<<"Transformable"<<std::endl;
		}
		else if (comp_name == "SpriteComponent")
		{
			SpriteComponent* sc = new SpriteComponent();
			for (params_node; params_node; params_node = params_node->next_sibling())
			{
				params_name	= params_node->first_attribute("name")->value();
				std::cout<<params_name<<std::endl;
				if (params_name == "SpriteData")
				{
					sc->setSprite(params_node->first_attribute("value")->value());
				}
				else if (params_name == "Size")
				{
					sc->setSize(b2Vec2(std::stof(params_node->first_attribute("x")->value()), std::stof(params_node->first_attribute("y")->value())));
				}
				else;
				std::cout<<"SpriteComponent"<<std::endl;
			}
			ent->addComponent(sc);
			
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
			ent->addComponent(cm);
		}
		else if (comp_name == "WeaponComponent")
		{
			WeaponComponent* wp = new WeaponComponent(m_PhysicsManager);
			params_name = params_node->first_attribute("name")->value();
			if (params_name == "Type")
			{
				//better with json
				if (params_name == "M16")
				{
					Item::Gun* gun = new Item::Gun("M16", 20, 30, 30, 0.5f, 0.1f);
					wp->setGun(gun);
				}
				ent->addComponent(wp);
			}
			std::cout<<"Weapon"<<std::endl;
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
				ph = new PhysicsComponent(m_PhysicsManager, phDef,
				0xffffffff);
			}
			ent->addComponent(ph);
			std::cout<<"physcics"<<std::endl;
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
			std::cout<<"sound"<<std::endl;
		}
		else;
	}
	createEntity(ent);
}
*/


/*
void EntityManager::createEntity(Entity* ent)
{
	m_TobeAdded.push_back(ent);
}

void EntityManager::destroyEntity(Entity* ent)
{
	m_TobeRemoved.push_back(ent);
}
*/

std::list<std::string> EntityManager::listEntities() const
{
    std::list<std::string> result;
    for(auto iter=m_Entities.begin(); iter != m_Entities.end(); ++iter)
        result.push_back(iter->first);
    return result;
}

void EntityManager::update(float deltaTime)
{
	for(auto iter=m_Entities.begin(); iter != m_Entities.end(); ++iter)
	{
		iter->second->update(deltaTime);
		if(iter->second->isRedundant())	
			m_Redundant.push_back(iter->second);
	}

	while(!m_Redundant.empty())
	{
		this->m_removeEntity(m_Redundant.front());
		m_Redundant.pop_front();
	}
}
/*
void EntityManager::preLoop()
{
	for (auto it = m_TobeAdded.begin(); it != m_TobeAdded.end(); ++it)
	{
		(*it)->initialise();
		m_Entities.push_back(*it);
	}

	m_TobeAdded.clear();
}
*/
/*
void EntityManager::postLoop()
{
	auto it = m_TobeRemoved.begin();
	while (it != m_TobeRemoved.end())
	{
		delete *it;
		it	= m_TobeRemoved.erase(it);
	}
}
*/

void EntityManager::m_removeEntity(Entity *ent)
{
    for(auto iter=m_Entities.begin(); iter != m_Entities.end(); ++iter)
    {
        if(iter->second == ent)
        {
            if(m_Listener)
                m_Listener->onEntityRemoved(iter->first, ent);
            m_Entities.erase(iter);
            delete ent;
            return;
        }
    }
}