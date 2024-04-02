#include "mylistwidget.h"

MyListWidget::MyListWidget()
{

}
void MyListWidget::keyPressEvent(QKeyEvent* event){
    qDebug("%s",event->text().toStdString().c_str());
}
