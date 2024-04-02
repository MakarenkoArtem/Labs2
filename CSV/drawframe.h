#ifndef DRAWFRAME_H
#define DRAWFRAME_H

#include <QWidget>
#include<QPainter>
#include <arrays.h>
#include <libraries/mystring.h>


class DrawFrame : public QWidget
{
    Q_OBJECT
public:
    int minRow, maxRow, minCol, maxCol, countVals;
    DataForGrap* data;
    char* titleCol, *titleRow;
    explicit DrawFrame(QWidget *parent = nullptr);
    void updateFrame(DataForGrap* newData);
private:
    void paintEvent(QPaintEvent *event) override;

signals:


};

#endif // DRAWFRAME_H
