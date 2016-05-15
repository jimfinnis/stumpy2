#include "glwidget.h"
#include "model/controller.h"
#include "util/exception.h"
#include "engine/effect.h"
#include "engine/mesh.h"
#include <stdio.h>

#include <QTimer>

GLWidget::GLWidget(QWidget *parent) :
QGLWidget(parent)
{
    
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(10);
    
    server = new Server(65111);
    server->setListener(new Controller(&lib,server));
}



Mesh *test;

void GLWidget::initializeGL(){
    
    printf("Starting GL\n%s\n",glGetString(GL_VERSION));
    
    glClearColor(0,0,1,1);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    extern void loadPrims();
    loadPrims();
    
    test = new Mesh("media","bevcube.x");
    
    EffectManager::getInstance(); // forces compile of shaders
}

void GLWidget::resizeGL(int width,int height){
    float aspect = ((float)width)/(float)height;
    Matrix::setProjection(90,0.1,2000,aspect);
    glViewport(0,0,width,height);
}

void GLWidget::paintGL(){
    server->process();
    gTimerDevice.tick();
        glClearColor(0,0,1,0);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    printf("tick\n");
    lib.run();
    
/*
    static float a=0;
    
    a+=0.01f;
    
    Matrix world=Matrix::IDENTITY;
    world.setRotX(-PI*0.5f);
    
    Matrix m1=Matrix::IDENTITY;
    m1.setRotY(a);
    
    world = world*m1;
    
    Matrix view =Matrix::IDENTITY;
    view.setTranslation(0,0,-5);
*/
}
