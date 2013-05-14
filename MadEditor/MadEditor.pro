#-------------------------------------------------
#
# Project created by QtCreator 2013-05-14T20:10:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MadEditor
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH += ../MadEngine
LIBS += -L../Volge-TheSurvivor-Debug -L/usr/local/lib -lMadEngine -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lBox2D

SOURCES += main.cpp\
        MainWindow.cpp \
    GameWorld.cpp

HEADERS  += MainWindow.h \
    GameWorld.hpp

FORMS    += MainWindow.ui
