#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H
#include<QKeyEvent>
#include<QListWidget>

class MyListWidget: public QListWidget{
    Q_OBJECT
public:
    void keyPressEvent(QKeyEvent *event);
    MyListWidget();
};

#endif // MYLISTWIDGET_H
