#-------------------------------------------------
#
# Project created by QtCreator 2013-10-30T15:13:37
#
#-------------------------------------------------

QT       += opengl widgets

SOURCES += main.cpp\
        mainwindow.cpp \
    blackhole.cpp \
    star.cpp \
    viewport.cpp \
    particlesystem.cpp \
    particle.cpp \
    mtrand.cpp \
    helperFunctions.cpp

HEADERS  += mainwindow.h \
    blackhole.h \
    star.h \
    helpers.h \
    viewport.h \
    particlesystem.h \
    particle.h \
    mtrand.h \
    helperFunctions.h

# The following is necessary to compile on my Linux version:
LIBS += -L/usr/local/lib -lGLU

RESOURCES += \
    textures.qrc
