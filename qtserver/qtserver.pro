#-------------------------------------------------
#
# Project created by QtCreator 2013-03-07T21:17:27
#
#-------------------------------------------------

QT       += core gui opengl
CONFIG  += debug
TARGET = qtserver
TEMPLATE = app
LIBS += -lGLU

SOURCES += main.cpp \
    glwidget.cpp \
    util/time.cpp \
    engine/maths.cpp \
    engine/texture.cpp \
    engine/tokeniser.cpp \
    engine/effect.cpp \
    engine/tga.cpp\
    engine/mesh.cpp\
    model/timer.cpp\
    model/model.cpp\
    model/errors.cpp\
    model/server.cpp\
    model/controller.cpp\
    components/output.cpp\
    components/add.cpp\
    components/light.cpp\
    components/prim.cpp\
    components/transforms.cpp\
    components/test.cpp\
    components/mul.cpp\
    components/ring.cpp\
    components/clock.cpp\
    components/osc.cpp\
    components/mixer.cpp\
    components/diffusecomp.cpp\
    components/textcomp.cpp
   

HEADERS  += \
    glwidget.h \
    util/exception.h \
    util/types.h \
    engine/maths.h \
    engine/texture.h \
    engine/mesh.h \
    engine/vertexdata.h \
    engine/state.h \
    engine/effect.h \
    engine/tga.h\
    model/server.h\
    model/controller.h\
    engine/tokeniser.h
