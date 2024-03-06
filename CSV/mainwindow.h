#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<libraries/mystring.h>
#include<enterpoint.h>
#include<arrays.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    char* file;
    MyData vals;
    DBookList DArray;
    Queue queue;


private:
    void changeFile();
    void openFile();
    void displayData();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H