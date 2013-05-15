#ifndef _MADENGINE_HPP_
#define _MADENGINE_HPP_

#include "Interface/IGame.hpp"
#include "Interface/IPhysicsSystem.hpp"
#include "Interface/IResource.hpp"

#include "Manager/GameState.hpp"
#include "Manager/Resource.hpp"
#include "Manager/Controller.hpp"
#include "Manager/Exceptions.hpp"
#include "Manager/Graphics.hpp"

#include "Utility/ConfigParser.hpp"
#include "Utility/DrawBatch.hpp"

#include "Graphics/Sprite.hpp"
#include "Graphics/Texture.hpp"

#include "3rdParty/FrameClock/FrameClock.hpp"
#include "3rdParty/FrameClock/ClockHUD.hpp"
#include "3rdParty/b2DebugDraw/DebugDraw.hpp"
#include "3rdParty/JSON/JSON.hpp"
#include "3rdParty/rapidxml-1.13/rapidxml.hpp"
#include "3rdParty/rapidxml-1.13/rapidxml_iterators.hpp"
#include "3rdParty/rapidxml-1.13/rapidxml_print.hpp"
#include "3rdParty/rapidxml-1.13/rapidxml_utils.hpp"

//Begin of The Survivor Game Class
#include "Entity/Entity.hpp"
#include "Entity/EntityManager.hpp"
#include "Entity/PhysicsSystem.hpp"
#include "Entity/Property.hpp"

#include "Entity/Components/CameraComponent.hpp"
#include "Entity/Components/HealthComponent.hpp"
#include "Entity/Components/PhysicsComponent.hpp"
#include "Entity/Components/PlayerCtrlComponent.hpp"
#include "Entity/Components/SoundComponent.hpp"
#include "Entity/Components/SpriteComponent.hpp"
#include "Entity/Components/TransformableComponent.hpp"
#include "Entity/Components/WeaponComponent.hpp"
//End of The Survivor Game Class

#define DEGTORAD (b2_pi /180.0f)
#define RADTODEG (180.0f/b2_pi)
#define RATIO 30.f
#define UNRATIO (1.0f/30.f)

#endif