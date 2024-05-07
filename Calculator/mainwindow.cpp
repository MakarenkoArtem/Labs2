#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"entrypoint.h"
#include "exception"
#define BUTTONS_COUNT 17
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton* buts[BUTTONS_COUNT]={ui->button0, ui->button1, ui->button2, ui->button3, ui->button4, ui->button5, ui->button6, ui->button7, ui->button8, ui->button9,
                        ui->buttonDiv, ui->buttonMinus, ui->buttonMult, ui->buttonPlus, ui->buttonPoint,
                                     ui->buttonLBrac, ui->buttonRBrac};
    for(int i=0; i!=BUTTONS_COUNT; ++i){
        connect(buts[i], &QPushButton::clicked, this, &MainWindow::addChar);
    }

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
    QPushButton *currentButton = qobject_cast<QPushButton*>(sender());
    context.but= currentButton->text().toStdString();
    doOperation(AddChar, &context, &params);
    ui->label->setText(QString(join(params.input).c_str()));

}




void MainWindow::on_buttonC_clicked(){
    doOperation(DelChar, &context, &params);
    ui->label->setText(QString(join(params.input).c_str()));
}



void MainWindow::on_buttonEqual_clicked(){
    try {
        doOperation(Calc, &context, &params);
        ui->label->setText(QString((join(params.input)+"\n="+params.output).c_str()));
    }  catch (std::exception &ex) {
        ui->label->setText(QString((join(params.input)+"\n="+ex.what()).c_str()));
    }
}


void MainWindow::on_buttonDEL_clicked(){
    params.input.clear();
    ui->label->setText(QString(join(params.input).c_str()));
}

