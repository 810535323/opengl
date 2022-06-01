#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->openGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionClear_triggered() //清空画面
{
    ui->openGLWidget->drawShape(myOpenGl::None);
}

void MainWindow::on_actionRec_triggered() //绘制矩形
{
    ui->openGLWidget->drawShape(myOpenGl::Rect);
}

void MainWindow::on_actionLine_triggered() //绘制矩形线框
{
    ui->openGLWidget->setWirefame(ui->actionLine->isChecked());
}
