TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-graphics -lsfml-window -lsfml-system

SOURCES += \
        animatedsprite.cpp \
        main.cpp

HEADERS += \
    animatedsprite.h