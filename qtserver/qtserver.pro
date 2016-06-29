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
    util/time.cpp \
    engine/maths.cpp \
    engine/texture.cpp \
    engine/tokeniser.cpp \
    engine/effect.cpp \
    engine/tga.cpp\
    engine/mesh.cpp\
    serverbase/timer.cpp\
    serverbase/model.cpp\
    serverbase/errors.cpp\
    serverbase/server.cpp\
    serverbase/controller.cpp\
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
    util/exception.h \
    util/types.h \
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
    serverbase/patch.h \
    serverbase/server.h \
    serverbase/timer.h \
    engine/tokeniser.h
