#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "enterpoint.h"
#include"QDebug"
MyMainWindow::MyMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    //QButtonGroup *groupBox=new QButtonGroup(this);
    ui->setupUi(this);
    //ui->groupBox.addButton(ui->radioButton);
    QButtonGroup* group = new QButtonGroup(this);
    group->addButton(ui->radioButton);
    group->addButton(ui->radioButton_2);
    group->addButton(ui->radioButton_3);
    QButtonGroup* group1 = new QButtonGroup(this);
    group1->addButton(ui->radioButton_4);
    group1->addButton(ui->radioButton_5);
    group1->addButton(ui->radioButton_6);
    ui->radioButton_2->setChecked(true);
    connect(ui->radioButton, &QRadioButton::clicked, this, &MyMainWindow::validationCheck);
    connect(ui->radioButton_2, &QRadioButton::clicked, this, &MyMainWindow::validationCheck);
    connect(ui->radioButton_3, &QRadioButton::clicked, this, &MyMainWindow::validationCheck);
    connect(ui->radioButton_4, &QRadioButton::clicked, this, &MyMainWindow::validationCheck);
    connect(ui->radioButton_5, &QRadioButton::clicked, this, &MyMainWindow::validationCheck);
    connect(ui->radioButton_6, &QRadioButton::clicked, this, &MyMainWindow::validationCheck);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MyMainWindow::validationCheck);
    connect(ui->spinBox, &QSpinBox::textChanged, this, &MyMainWindow::validationCheck);
    connect(ui->spinBox_3, &QSpinBox::textChanged, this, &MyMainWindow::validationCheck);
    connect(ui->pushButton, &QPushButton::clicked, this, &MyMainWindow::countingFunc);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MyMainWindow::copyFunc);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MyMainWindow::changeFunc);
    validationCheck();
}
void MyMainWindow::copyFunc(){
    doOperation(Copy, &this->data, &this->newData);
}

void MyMainWindow::changeFunc(){
    doOperation(Change, &this->data, &this->newData);
    switch(this->newData.notationIn){
    case 2:
        ui->radioButton->setChecked(true);
        break;
    case 10:
        ui->radioButton_2->setChecked(true);
        break;
    default:
        ui->radioButton_3->setChecked(true);
        ui->spinBox->setValue(this->newData.notationIn);
        break;
    }
    switch(this->newData.notationOut){
    case 2:
        ui->radioButton_4->setChecked(true);
        break;
    case 10:
        ui->radioButton_5->setChecked(true);
        break;
    default:
        ui->radioButton_6->setChecked(true);
        ui->spinBox_3->setValue(this->newData.notationOut);
        break;
    }
    ui->lineEdit->setText(QString::fromStdString(this->newData.num));
    countingFunc();
}
void MyMainWindow::validationCheck(){
    this->newData.num=upperStr((char*)ui->lineEdit->text().toStdString().c_str());
    if (ui->radioButton->isChecked()){
        this->newData.notationIn=2;
    }else if (ui->radioButton_2->isChecked()){
        this->newData.notationIn=10;
    }else{
        this->newData.notationIn=ui->spinBox->value();
    }
    if (ui->radioButton_4->isChecked()){
        this->newData.notationOut=2;
    }else if (ui->radioButton_5->isChecked()){
        this->newData.notationOut=10;
    }else{
        this->newData.notationOut=ui->spinBox_3->value();
    }
    doOperation(Validation, &this->data, &this->newData);
    ui->label_2->setText(QString::fromStdString(this->data.mes));
}


void MyMainWindow::countingFunc(){
    doOperation(Counting, &this->data, &this->newData);
    ui->label->setText(QString::fromStdString(this->data.val));
    ui->label_2->setText(QString::fromStdString(this->data.mes));
    ui->label_3->clear();
    if(this->data.mes=="" && this->newData.notationIn==this->newData.notationOut){
        QPixmap myPixmap("/home/artem/Artem/C++/Labs2/MainWindow/src/tinkoff.jpg");
        qDebug("tinkoff");
        QSize PicSize(300, 300);
        myPixmap = myPixmap.scaled(PicSize,Qt::KeepAspectRatio);
        //myPixmap=myPixmap.scaled(300, 300);
        ui->label_3->setPixmap( myPixmap );
    }
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

