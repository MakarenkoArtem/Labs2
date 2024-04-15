#include "drawframe.h"
#include "QDebug"
DrawFrame::DrawFrame(QWidget *parent)
    : QWidget{parent}
{
    data=(DataForGrap*)malloc(sizeof(DataForGrap));
    data->count=0;
    data->vals=(CounteredList*)malloc(sizeof(CounteredList)*0);
}

void clear(DataForGrap* data){
    for(int i =0;i<data->count;++i){
        free(data->vals[i].region);
        free(data->vals[i].vals);
       }
    free(data->vals);
    //free(data);
}

void DrawFrame::updateFrame(DataForGrap* newData){
    if(newData==data){
    }else{
        clear(data);
        data=newData;
    }
    update();
}

void DrawFrame::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.setPen(Qt::red);
    paint.drawLine(width()*0.1, height()*0.9, width()*0.96, height()*0.9);
    paint.setPen(Qt::blue);
    paint.drawLine(width()*0.1, height()*0.9, width()*0.1, height()*0.07);
    minRow=(int)minRow;
    if(maxRow-(int)maxRow>0){
        maxRow=(int)(maxRow+1);
    }
    minCol=(int)minCol;
    if(maxCol-(int)maxCol/1>0){
        maxCol=(int)(maxCol+1);
    }
    int r=std::max(1.0, std::min(width()*0.8/75, (double)maxRow-minRow));
    char* help;
    for (int row = 0; row <=r-(maxRow-minRow<1.0); ++row) {
        paint.drawLine(width()*0.1 + width()*0.84*row/r, height()*0.88, width()*0.1 + width()*0.84*row/r, height()*0.92);
        help=intToStr(minRow+row*(maxRow-minRow)/r);
        paint.drawText(width()*0.07 + width()*0.84*row/r, height()*0.97, QString(help));
        free(help);
    }
    int c=std::max(1.0,std::min(height()*0.8/75, (double)maxCol-minCol));
    for (int col = 0; col <=c-(maxCol-minCol<1.0); ++col) {
        paint.drawLine(width()*0.08, height()*0.9 - height()*0.8*col/c, width()*0.12, height()*0.9 - height()*0.8*col/c);
        help=intToStr(minCol+col*(maxCol-minCol)/c);
        paint.drawText(width()*0.01, height()*0.91 - height()*0.8*col/c, QString(help));
        free(help);
    }
    int a, b, d, e;
    if (maxCol==minCol && minCol!=0){maxCol+=maxCol==minCol;}
    maxRow+=maxRow==minRow;
    ;
    for(int i =0;i<data->count;++i){
        paint.setPen(QColor(i*25%256,255-i*81%256,255-i*36%256));
        for(int j=0;j<data->vals[i].count;++j){
            a=width()*0.1 + width()*0.84*(data->vals[i].vals[j].key-minRow)/(maxRow-minRow);
            b=height()*0.9 - height()*0.84*(data->vals[i].vals[j].val-minCol)/(maxCol-minCol);
            paint.drawEllipse(a-5,b-5, 10, 10);
            if(j){
                //qDebug("%i %i %i", data->vals[i].vals[j].key, a, d);
                paint.drawLine(a,b,d,e);
            }
            d=a;
            e=b;
        }
    }
    paint.end(); // Завершаем рисование
}
