#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QButtonGroup>
#include<data.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow();
    Data data;
    NewData newData;

private:
    void validationCheck();
    void countingFunc();
    void changeFunc();
    void copyFunc();
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
