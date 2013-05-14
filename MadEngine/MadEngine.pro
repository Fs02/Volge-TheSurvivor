TEMPLATE = lib
CONFIG += console staticlib
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    3rdParty/b2DebugDraw/DebugDraw.cpp \
    3rdParty/JSON/JSON.cpp \
    Graphics/Texture.cpp \
    Graphics/Sprite.cpp \
    Interface/IResource.cpp \
    Interface/IPhysicsSystem.cpp \
    Interface/IGame.cpp \
    Manager/Resource.cpp \
    Manager/Graphics.cpp \
    Manager/GameState.cpp \
    Manager/Controller.cpp \
    Sound/SoundBuffer.cpp \
    Sound/Music.cpp \
    Utility/DrawBatch.cpp \
    Utility/ConfigParser.cpp \
    Entity/Property.cpp \
    Entity/EntityManager.cpp \
    Entity/Entity.cpp \
    Entity/Item/Gun.cpp \
    Entity/Components/WeaponComponent.cpp \
    Entity/Components/TransformableComponent.cpp \
    Entity/Components/SpriteComponent.cpp \
    Entity/Components/SoundComponent.cpp \
    Entity/Components/PlayerCtrlComponent.cpp \
    Entity/Components/PhysicsComponent.cpp \
    Entity/Components/HealthComponent.cpp \
    Entity/Components/CameraComponent.cpp \
    Entity/PhysicsSystem.cpp

HEADERS += \
    3rdParty/b2DebugDraw/DebugDraw.hpp \
    3rdParty/FrameClock/FrameClock.hpp \
    3rdParty/FrameClock/ClockHUD.hpp \
    3rdParty/JSON/JSON.hpp \
    Graphics/Texture.hpp \
    Graphics/Sprite.hpp \
    Interface/IResource.hpp \
    Interface/IPhysicsSystem.hpp \
    Interface/IGame.hpp \
    Manager/Resource.hpp \
    Manager/Graphics.hpp \
    Manager/GameState.hpp \
    Manager/Exceptions.hpp \
    Manager/Controller.hpp \
    Sound/SoundBuffer.hpp \
    Sound/Music.hpp \
    Utility/DrawBatch.hpp \
    Utility/ConfigParser.hpp \
    Entity/Property.hpp \
    Entity/EntityManager.hpp \
    Entity/Entity.hpp \
    Entity/Item/IItem.hpp \
    Entity/Item/Gun.hpp \
    Entity/Components/WeaponComponent.hpp \
    Entity/Components/TransformableComponent.hpp \
    Entity/Components/SpriteComponent.hpp \
    Entity/Components/SoundComponent.hpp \
    Entity/Components/PlayerCtrlComponent.hpp \
    Entity/Components/PhysicsComponent.hpp \
    Entity/Components/HealthComponent.hpp \
    Entity/Components/CameraComponent.hpp \
    Entity/PhysicsSystem.hpp

