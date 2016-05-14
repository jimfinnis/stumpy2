#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

#include "model/model.h"
#include "model/server.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    virtual void initializeGL();
    virtual void resizeGL(int width,int height);
    virtual void paintGL();
    
    QSize minimumSizeHint() const{
        return QSize(50, 50);
    }
    
    QSize sizeHint() const{
        return QSize(400, 400);
    }
signals:
    
public slots:
    
    
private:
    PatchLibrary lib;
    Server *server;
};

#endif // GLWIDGET_H
