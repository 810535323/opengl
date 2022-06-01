#include "myopengl.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

unsigned int VBO, VAO, EBO; //创建变量
/*---------------------------矩形-----------------------
float vertices[] = {
    0.5f,0.5f,0.0f, //右上角
    0.5f,-0.5f,0.0f, //右下角
    -0.5f,-0.5f,0.0f, //左下角
    -0.5f,0.5f,0.0f //左上角
};

unsigned int indices[] = {
    // 注意索引从0开始! 
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形
    0,1,3, //第一个三角形
    1,2,3 //第二个三角形
};

const char *vertexShaderSource = "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
        "}\0";

//uniform为外部函数可更改变量
const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 ourColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = ourColor;\n"
        "}\n\0";
--------------------------------------------------------*/
float vertices[] = { //给定位置点
    // 位置              // 颜色
    -0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,    // 左上
     0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 右上
     0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   // 右下
    -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,   // 左下
};

unsigned int indices[] = { //制定三角点
    // 注意索引从0开始! 
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形
    0,1,2, //第一个三角形
    0,2,3 //第二个三角形
};

myOpenGl::myOpenGl(QWidget *parent)
{
    Q_UNUSED(parent);
}

myOpenGl::~myOpenGl() //析构函数
{
    makeCurrent(); //创建上下文 ？
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);
    shaderProgram.deleteLater();
    doneCurrent();
}

void myOpenGl::drawShape(myOpenGl::Shape shape) //选择类型(Updata重新调用paintGL函数，其他方式无效)
{
    m_shape = shape;
    update();
}

void myOpenGl::setWirefame(bool wireframe) //是否线框显示
{
    makeCurrent(); //创建上下文 ？
    if(wireframe){
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }else{
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }
    update();
    doneCurrent();
}

void myOpenGl::initializeGL() //初始化创建VAO、VBO、EBO对象并添加顶点、指定器数据，最后由shaderprogram连接编译器
{
    initializeOpenGLFunctions();

    //创建VAO、VBO、EBO对象并赋予ID
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1,&EBO);

    //绑定VAO VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //为当前绑定到target的缓冲区对象创建一个新的数据存储。
    //如果data不是NULL，则使用来自此指针的数据初始化数据存储
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //告知显卡如何定义三角重合边缘，降低消耗
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //告知显卡如何解析缓冲里的属性值
    //第一段位置
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //开启VAO管理的第一个属性值
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

//    //编译顶点着色器
//    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
//    glCompileShader(vertexShader);
//    int success;
//    //获取编译信息
//    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
//    if(!success){
//        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
//        qDebug()<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED!\n"<<infoLog;
//    }

//    //编译片段着色器
//    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
//    glCompileShader(fragmentShader);
//    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
//    //获取编译信息
//    if(!success){
//        glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
//        qDebug()<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED!\n"<<infoLog;
//    }

    //链接顶点、片段着色器文件
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/vertex.vsh");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":shaders/fragment.fsh");
    //获取链接信息并打印错误
    bool success = shaderProgram.link();
    if(!success){
        qDebug()<<"ERROR::SHADER::PROGRAM::LINKING_FAILED!\n"<<shaderProgram.log();
    }

//    //删除顶点、片段着色器
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
}

void myOpenGl::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
}

void myOpenGl::paintGL()
{
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //使用编译程序
    shaderProgram.bind();
    //绑定VAO
    glBindVertexArray(VAO);
    //绘制图形
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    switch (m_shape) {
    case Rect:
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        break;
    default:
        break;
    }
}
