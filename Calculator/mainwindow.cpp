#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"entrypoint.h"
#include "exception"
#define PATH "/home/artem/Artem/C++/Labs2/Calculator/"
#define BUTTONS_COUNT 22

std::map<string, string> errors={{"Division by zero", "divison.jpg"}, {"Есть не закрытая скобка", "brackets.png"}, {"Нет открывающей скобки","brackets.png"},
                                 {"Не реализованный оператор", "realError.png"}, {"Не хватает чисел", "warning.png"}, {"у числа несколько дробных частей", "errorNum.png"},
                                 {"у числа нет целой части", "errorNum.png"}};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton* buts[BUTTONS_COUNT]={ui->button0, ui->button1, ui->button2, ui->button3, ui->button4, ui->button5, ui->button6, ui->button7, ui->button8, ui->button9,
                        ui->buttonDiv, ui->buttonMinus, ui->buttonMult, ui->buttonPlus, ui->buttonPoint, ui->buttonLBrac, ui->buttonRBrac, ui->buttonSqrt,
                                     ui->buttonSin, ui->buttonCos, ui->buttonTg, ui->buttonCtg};
    for(int i=0; i!=BUTTONS_COUNT; ++i){
        connect(buts[i], &QPushButton::clicked, this, &MainWindow::addChar);
    }
    //connect(ui->label, SIGNAL(resizeEvent(QResizeEvent)), this, &MainWindow::resizeImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}
string join(vector<string> list) {
    string str ="";
    for (auto it:list) {
        str+=it;
    }
    return str;
}

void MainWindow::addChar(){
    setImage("");
    QPushButton *currentButton = qobject_cast<QPushButton*>(sender());
    context.but= currentButton->text().toStdString();
    doOperation(AddChar, &context, &params);
    ui->label->setText(QString(join(params.input).c_str()));

}




void MainWindow::on_buttonC_clicked(){
    setImage("");
    doOperation(DelChar, &context, &params);
    ui->label->setText(QString(join(params.input).c_str()));
}
void MainWindow::resizeImage(){
    ui->image->setBaseSize(ui->label->height(),ui->label->height());
}

void MainWindow::setImage(string image){
    try {
        resizeImage();
        QPixmap myPixmap(image.c_str());
        QSize PicSize(ui->label->height(), ui->label->height());//ui->label->height(),ui->label->height());
        myPixmap = myPixmap.scaled(PicSize,Qt::KeepAspectRatio);
        ui->image->setPixmap( myPixmap );
    }  catch (std::exception &ex) {
        ui->image->setBaseSize(0,0);
    }
}

void MainWindow::on_buttonEqual_clicked(){
    try {
        doOperation(Calc, &context, &params);
    }  catch (std::exception &ex) {
        params.output=ex.what();
    }
    ui->label->setText(QString((join(params.input)+"\n="+params.output).c_str()));
    if(errors.count(params.output)){//contains() появился только в С++20
        setImage(PATH+errors[params.output]);
    }else{
        setImage("");
    }
}


void MainWindow::on_buttonDEL_clicked(){
    setImage("");
    params.input.clear();
    ui->label->setText(QString(join(params.input).c_str()));
}


void MainWindow::on_buttonRev_clicked(){
    setImage("");
    doOperation(RevFunc, &context, &params);
    ui->label->setText(QString(join(params.input).c_str()));

}


void MainWindow::on_buttonMPlus_clicked(){
    params.memory+=std::stod(params.output);
}


void MainWindow::on_buttonMMinus_clicked(){
    params.memory-=std::stod(params.output);
}


void MainWindow::on_buttonMR_clicked(){
    ui->label->setText(QString((join(params.input)+"\n="+std::to_string(params.memory)).c_str()));
}


void MainWindow::on_buttonMC_clicked(){
   params.memory=0;
}

