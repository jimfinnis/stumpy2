#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>

#include "serverbase/model.h"
#include "serverbase/server.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
          
    
public:
    explicit GLWidget(QWidget *parent = 0);

    virtual void initializeGL();
    virtual void resizeGL(int width,int height);
    virtual void paintGL();
    
    
    virtual void keyPressEvent(QKeyEvent *e)
    {
        switch(e->key()){
        case Qt::Key_F11:
        case Qt::Key_F:
            togglefull();
            break;
        case Qt::Key_Q:
            quit();
            break;
        default:
            QGLWidget::keyPressEvent(e);
        }
    }    
    
    QSize minimumSizeHint() const{
        return QSize(50, 50);
    }
    
    QSize sizeHint() const{
        return QSize(800,600);
    }
signals:
    
public slots:
    
private:
    
    void togglefull(){
        fullsc = !fullsc;
        if(fullsc)
            showFullScreen();
        else
            showNormal();
        
    }
    
    void quit();
    
    bool fullsc;
    PatchLibrary lib;
    Server *server;
};

#endif // GLWIDGET_H
