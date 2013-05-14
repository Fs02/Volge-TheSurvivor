TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11
LIBS += -L/home/piotrek/Dev/Volge-TheSurvivor-Debug -L/usr/local/lib -lMadEngine -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lBox2D
INCLUDEPATH += ../MadEngine

SOURCES += \
    TheSurvivor.cpp \
    stdafx.cpp \
    PhysicsSystem.cpp \
    Game.cpp \
    Item/Gun.cpp \
    Entity/Property.cpp \
    Entity/EntityManager.cpp \
    Entity/Entity.cpp \
    Entity/Components/WeaponComponent.cpp \
    Entity/Components/TransformableComponent.cpp \
    Entity/Components/SpriteComponent.cpp \
    Entity/Components/SoundComponent.cpp \
    Entity/Components/PlayerCtrlComponent.cpp \
    Entity/Components/PhysicsComponent.cpp \
    Entity/Components/HealthComponent.cpp \
    Entity/Components/CameraComponent.cpp

HEADERS += \
    stdafx.h \
    PhysicsSystem.hpp \
    Game.hpp \
    Item/IItem.hpp \
    Item/Gun.hpp \
    Entity/Property.hpp \
    Entity/EntityManager.hpp \
    Entity/Entity.hpp \
    Entity/Components/WeaponComponent.hpp \
    Entity/Components/TransformableComponent.hpp \
    Entity/Components/SpriteComponent.hpp \
    Entity/Components/SoundComponent.hpp \
    Entity/Components/PlayerCtrlComponent.hpp \
    Entity/Components/PhysicsComponent.hpp \
    Entity/Components/HealthComponent.hpp \
    Entity/Components/CameraComponent.hpp

OTHER_FILES += \
    setting.cfg \
    Game.pro.user

