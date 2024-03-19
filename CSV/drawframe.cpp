#include "drawframe.h"

DrawFrame::DrawFrame(QWidget *parent)
    : QWidget{parent}
{

}


void DrawFrame::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.setPen(Qt::red);
    paint.drawLine(width()*0.1, height()*0.9, width()*0.93, height()*0.9);
    paint.setPen(Qt::blue);
    paint.drawLine(width()*0.1, height()*0.9, width()*0.1, height()*0.07);
    int r=width()*0.8/75;
    char* help;
    for (int row = 0; row <=r; ++row) {
        paint.drawLine(width()*0.1 + width()*0.8*row/r, height()*0.88, width()*0.1 + width()*0.8*row/r, height()*0.92);
        help=intToStr(minRow+row/r*(maxRow-minRow));
        paint.drawText(width()*0.07 + width()*0.8*row/r, height()*0.97, QString(help));
        free(help);
    }
    int c=height()*0.8/75;
    for (int col = 0; col <=c; ++col) {
        paint.drawLine(width()*0.08, height()*0.9 - height()*0.8*col/c, width()*0.12, height()*0.9 - height()*0.8*col/c);
        help=intToStr(minCol+col/c*(maxCol-minCol));
        paint.drawText(width()*0.01, height()*0.91 - height()*0.8*col/c, QString(help));
        free(help);
    }
    int a, b, d, e;
    /*for(int i =0;i<data.count;++i){
        for(int j=0;j<data.vals[i].count;++j){
            a=width()*0.1 + width()*0.8*data.vals[i].vals[j].val/r;
            b=height()*0.9 - height()*0.8*data.vals[i].vals[j].key/c;
            paint.drawEllipse(a,b, 10, 10);
            if(j){
                paint.drawLine(a,b,d,e);
            }
            d=a;
            e=b;
        }
    }*/
    paint.end(); // Завершаем рисование
}
