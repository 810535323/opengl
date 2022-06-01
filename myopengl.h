#ifndef MYOPENGL_H
#define MYOPENGL_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>

class myOpenGl : public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    enum Shape{None,Rect,Circle,Triangle}; //枚举类型
    explicit myOpenGl(QWidget *parent = nullptr);
    ~myOpenGl();

    void drawShape(Shape shape); //判断输入类型(调用update函数)
    void setWirefame(bool wireframe); //判断是否线框显示
protected:
    virtual void initializeGL(); //初始化GL
    virtual void resizeGL(int w, int h); //重置窗口函数
    virtual void paintGL(); //绘画GL
private:
    QOpenGLShaderProgram shaderProgram; //导入顶点、片段着色器文件与简化编译连接操作
    Shape m_shape; //判断输入类型
signals:

public slots:
};

#endif // MYOPENGL_H
