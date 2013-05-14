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
    Game.cpp

HEADERS += \
    stdafx.h \
    Game.hpp \
    Item/IItem.hpp

OTHER_FILES += \
    setting.cfg \
    Game.pro.user

