#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <stdexcept>
#include <QMainWindow>
#include <QApplication>
#include <map>
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

    void on_buttonRev_clicked();

    void on_buttonMPlus_clicked();

    void on_buttonMMinus_clicked();

    void on_buttonMR_clicked();

    void on_buttonMC_clicked();

private:
    void resizeImage();
    void setImage(string image);
    void addChar();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
