#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFrame>
#include <QMainWindow>
#include <drawframe.h>
#include<libraries/mystring.h>
#include<enterpoint.h>
#include<arrays.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; class Frame; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    AppParams params;
    AppContext context;

private:
    void changeFile();
    void openFile();
    void displayData();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
