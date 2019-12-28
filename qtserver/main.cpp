#include <QApplication>
#include <QGLWidget>
#include <stdio.h>
#include "glwidget.h"
#include "serverbase/util/time.h"
#include "engine/obj.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Time::init();
    GLWidget w;
    w.show();
    
    return a.exec();
}
