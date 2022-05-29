#ifndef MYOPENGL_H
#define MYOPENGL_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>

class myOpenGl : public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit myOpenGl(QWidget *parent = nullptr);
    ~myOpenGl();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
private:
signals:

public slots:
};

#endif // MYOPENGL_H
