#include "myopengl.h"
#include <QDebug>

unsigned int VBO, VAO;
unsigned int shaderProgram;
float vertices[] = {
    -0.5f,-0.5f,0.0f,
    0.5f,-0.5f,0.0f,
    0.0f,0.5f,0.f
};

const char *vertexShaderSource = "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
        "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
        "}\n\0";

myOpenGl::myOpenGl(QWidget *parent)
{

}

myOpenGl::~myOpenGl()
{

}

void myOpenGl::initializeGL()
{
    initializeOpenGLFunctions();

    //创建VAO、VBO对象并赋予ID
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //绑定VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //为当前绑定到target的缓冲区对象创建一个新的数据存储。
    //如果data不是NULL，则使用来自此指针的数据初始化数据存储
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //告知显卡如何解析缓冲里的属性值
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //开启VAO管理的第一个属性值
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //编译顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    //获取编译信息
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        qDebug()<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED!\n"<<infoLog;
    }

    //编译片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    //获取编译信息
    if(!success){
        glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
        qDebug()<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED!\n"<<infoLog;
    }

    //链接顶点、片段着色器
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    //获取链接信息
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
        qDebug()<<"ERROR::SHADER::PROGRAM::LINKING_FAILED!\n"<<infoLog;
    }

    //删除顶点、片段着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void myOpenGl::resizeGL(int w, int h)
{

}

void myOpenGl::paintGL()
{
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //使用编译程序
    glUseProgram(shaderProgram);
    //绑定VAO
    glBindVertexArray(VAO);
    //绘制图形
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
