#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFrame>
#include <QKeyEvent>
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
    DrawFrame canvas;
    void keyPressEvent(QKeyEvent *event);


private slots:
    void validationCheck();
private:
    void addRegion();
    void changeFile();
    void openFile();
    void displayData();
    void changeCurRegion(int ind);
    void updateList();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
