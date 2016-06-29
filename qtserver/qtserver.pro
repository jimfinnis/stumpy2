#-------------------------------------------------
#
# Project created by QtCreator 2013-03-07T21:17:27
#
#-------------------------------------------------

QT       += core gui opengl
# CONFIG  += debug
TARGET = qtserver
TEMPLATE = app
LIBS += -lGLU

SOURCES += main.cpp \
    glwidget.cpp \
    serverbase/util/time.cpp \
    engine/maths.cpp \
    engine/texture.cpp \
    engine/tokeniser.cpp \
    engine/effect.cpp \
    engine/tga.cpp\
    engine/mesh.cpp\
    serverbase/model.cpp\
    serverbase/errors.cpp\
    serverbase/server.cpp\
    serverbase/controller.cpp\
    serverbase/stdConns.cpp\
    components/output.cpp\
    components/add.cpp\
    components/light.cpp\
    components/prim.cpp\
    components/transforms.cpp\
    components/mul.cpp\
    components/ring.cpp\
    components/clock.cpp\
    components/osc.cpp\
    components/mixer.cpp\
    components/colour.cpp\
    components/hsv.cpp\
    components/textcomp.cpp\
    components/state.cpp\
    components/funcs.cpp\
    components/linear.cpp\
    components/debug.cpp\
    components/envmap.cpp
   

HEADERS  += \
    glwidget.h \
    serverbase/util/exception.h \
    serverbase/util/types.h \
    serverbase/util/time.h \
    engine/maths.h \
    engine/texture.h \
    engine/mesh.h \
    engine/vertexdata.h \
    engine/state.h \
    engine/effect.h \
    engine/tga.h \
    serverbase/component.h \
    serverbase/controller.h \
    serverbase/errors.h \
    serverbase/instances.h \
    serverbase/intkeyedhash.h \
    serverbase/iterator.h \
    serverbase/list.h \
    serverbase/model.h \
    serverbase/param.h \
    serverbase/stdConns.h \
    serverbase/patch.h \
    serverbase/server.h \
    engine/tokeniser.h
