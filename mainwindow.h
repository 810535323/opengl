#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionClear_triggered(); //按钮行为
    
    void on_actionRec_triggered(); //按钮行为
    
    void on_actionLine_triggered(); //按钮行为
    
private:
    Ui::MainWindow *ui;
    
signals:
    
};
#endif // MAINWINDOW_H
