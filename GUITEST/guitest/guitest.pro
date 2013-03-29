#-------------------------------------------------
#
# Project created by QtCreator 2013-03-25T11:14:20
#
#-------------------------------------------------

QT += core gui
QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = guitest
TEMPLATE = app
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGLU
INCLUDEPATH += $$PWD/
QMAKE_CXXFLAGS += -std=c++11
CXX_FLAGS += -O2

SOURCES += \
    $$PWD/Game.cpp \
    $$PWD/tools.cpp \
    $$PWD/SceneMain/SceneMain.cpp \
    $$PWD/SceneMain/Camera.cpp \
    $$PWD/SceneMain/Model.cpp \
    $$PWD/graphics/Texture.cpp \
    $$PWD/graphics/TextureManager.cpp \
    $$PWD/audio/AudioManager.cpp \
    $$PWD/audio/Effect.cpp \
    $$PWD/audio/Music.cpp \
    $$PWD/input/InputManager.cpp

HEADERS += \
    $$PWD/Scene.hpp \
    $$PWD/Game.hpp \
    $$PWD/tools.hpp \
    $$PWD/SceneMain/SceneMain.hpp \
    $$PWD/SceneMain/Camera.hpp \
    $$PWD/SceneMain/Model.hpp \
    $$PWD/graphics/Texture.hpp \
    $$PWD/graphics/TextureManager.hpp \
    $$PWD/audio/AudioManager.hpp \
    $$PWD/audio/Effect.hpp \
    $$PWD/audio/Music.hpp \
    $$PWD/Math.hpp \
    $$PWD/input/InputManager.hpp

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    qtcolorbutton.cpp

HEADERS  += mainwindow.hpp \
    glwidget.h \
    qtcolorbutton.h

FORMS    += mainwindow.ui
