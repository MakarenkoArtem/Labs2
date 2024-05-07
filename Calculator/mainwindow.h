#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QMainWindow>
#include "datatypes.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    AppParams params;
    AppContext context;


private slots:
    void on_buttonC_clicked();

    void on_buttonEqual_clicked();

    void on_buttonDEL_clicked();

private:
    void addChar();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
