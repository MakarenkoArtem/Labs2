#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <libraries/mystring.h>
#include <QMainWindow>
#include<QButtonGroup>
#include<data.h>
#include <QDir>
#include<QClipboard>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow();
    AppParams params;
    AppContext context;

private slots:
    void validationCheck();

private:
    void countingFunc();
    void changeFunc();
    void copyFunc();
    void errorFunc();
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
