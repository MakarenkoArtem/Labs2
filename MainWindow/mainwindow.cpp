#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "enterpoint.h"
#include "QDebug"
#include "libraries/mystring.h"

void freeMatrix(void** matrix, int rows);

char* errorValue[4]={(char*)"", (char*)"Число больше 4 байт", (char*)"Число не соответсвует системе счиления", (char*)"Просто ошибка"};
char* errorImage[4]={(char*)"", (char*)"", (char*)"/src/Oleg.jpg", (char*)""};

MyMainWindow::MyMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QButtonGroup* group = new QButtonGroup(this);
    group->addButton(ui->radioButton);
    group->addButton(ui->radioButton_2);
    group->addButton(ui->radioButton_3);
    QButtonGroup* group1 = new QButtonGroup(this);
    group1->addButton(ui->radioButton_4);
    group1->addButton(ui->radioButton_5);
    group1->addButton(ui->radioButton_6);

    ui->radioButton_2->setChecked(true);
    //ui->lineEdit->setText("0");

    connect(ui->radioButton, &QRadioButton::clicked, this, &MyMainWindow::validationCheck);
    connect(ui->radioButton_2, &QRadioButton::clicked, this, &MyMainWindow::validationCheck);
    connect(ui->radioButton_3, &QRadioButton::clicked, this, &MyMainWindow::validationCheck);
    connect(ui->radioButton_4, &QRadioButton::clicked, this, &MyMainWindow::validationCheck);
    connect(ui->radioButton_5, &QRadioButton::clicked, this, &MyMainWindow::validationCheck);
    connect(ui->radioButton_6, &QRadioButton::clicked, this, &MyMainWindow::validationCheck);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MyMainWindow::validationCheck);
    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(validationCheck()));
    connect(ui->spinBox_3, SIGNAL(valueChanged(int)), this,  SLOT(validationCheck()));

    connect(ui->pushButton, &QPushButton::clicked, this, &MyMainWindow::countingFunc);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &MyMainWindow::copyFunc);

    connect(ui->pushButton_3, &QPushButton::clicked, this, &MyMainWindow::changeFunc);


    this->params.filePath = copyStr((char*)QDir::currentPath().toStdString().c_str());//передаю расположение exe через params.filePath для работы с текущим адресом в логике
    doOperation(Initialization, &this->params, & this->context);
}

void MyMainWindow::copyFunc(){
    QClipboard *clipboard=QGuiApplication::clipboard();
    clipboard->setText(this->params.val);
    //this->data.error=doOperation(Copy, &this->data, &this->newData);
}

void MyMainWindow::changeFunc(){
    char* num=upperStr(copyStr((char*)ui->lineEdit->text().toStdString().c_str()));
    char* val = copyStr(params.val);
    //this->params.error=doOperation(Change, &this->params, &this->context);
    ui->lineEdit->setText(QString::fromStdString(string(val)));
    freeStr(val);
    int notationIn=this->context.notationOut,notationOut=this->context.notationIn;
    qDebug("line %s", this->context.num);
    switch(notationIn){
    case 2:
        ui->radioButton->setChecked(true);
        break;
    case 10:
        ui->radioButton_2->setChecked(true);
        break;
    default:
        ui->spinBox->setValue(notationIn);
        qDebug("notationIn %i", notationIn);
        ui->radioButton_3->setChecked(true);
        break;
    }
    switch(notationOut){
    case 2:
        ui->radioButton_4->setChecked(true);
        break;
    case 10:
        ui->radioButton_5->setChecked(true);
        break;
    default:
        ui->spinBox_3->setValue(notationOut);
        qDebug("notationOut %i", notationOut);
        ui->radioButton_6->setChecked(true);
        break;
    }
    this->validationCheck();
    params.val=num;
    ui->label->setText(QString::fromStdString(string(num)));
}

void MyMainWindow::validationCheck(){
    //QString s=this->styleSheet();
    //this->setStyleSheet(s+"QRadioButton::indicator:checked {image: url(C:/Users/User/Downloads/MainWindow1/src/sigma.jpg);width:100%;height:100%;}");
    qDebug("free 25 %s", this->context.num);
    //freeStr(this->context.num);
    this->context.num=upperStr(copyStr((char*)ui->lineEdit->text().toStdString().c_str()));
    if (ui->radioButton->isChecked()){
        this->context.notationIn=2;
    }else if (ui->radioButton_2->isChecked()){
        this->context.notationIn=10;
    }else{
        this->context.notationIn=ui->spinBox->value();
    }
    if (ui->radioButton_4->isChecked()){
        this->context.notationOut=2;
    }else if (ui->radioButton_5->isChecked()){
        this->context.notationOut=10;
    }else{
        this->context.notationOut=ui->spinBox_3->value();
    }
    this->params.error=doOperation(Validation, &this->params, &this->context);
    //ui->label_2->setText(QString::fromStdString(string(errorValue[this->data.error])));
    this->errorFunc();
}

void MyMainWindow::errorFunc(){
    ui->label->setText(QString::fromStdString(string(this->params.val)));
    ui->label_2->setText(QString::fromStdString(string(errorValue[this->params.error])));
    ui->label_3->clear();

    char* image = errorImage[this->params.error];
    if(compareStr(errorValue[this->params.error], (char*)"") && this->context.notationIn==this->context.notationOut){
        image=(char*)"/src/tinkoff.jpg";
    }
    char* file=copyStr(this->params.filePath);
    file=addStr((char*)realloc(file, (lenStr(file)+lenStr(image)+1)*sizeof(char)),image);
    qDebug("%s", file);
    QPixmap myPixmap(file);//"C:/Users/User/Downloads/MainWindow/src/tinkoff.jpg");
    QSize PicSize(300, 300);
    myPixmap = myPixmap.scaled(PicSize,Qt::KeepAspectRatio);
    ui->label_3->setPixmap( myPixmap );
    freeStr(file);
}

void MyMainWindow::countingFunc(){
    this->context.num=upperStr(copyStr((char*)ui->lineEdit->text().toStdString().c_str()));
    this->params.error=doOperation(Counting, &this->params, &this->context);
    ui->label->setText(this->params.val);
    if(this->params.error){
        ui->label_2->setText(QString::fromStdString(string(errorValue[this->params.error])));}

}

MyMainWindow::~MyMainWindow()
{
    //if(this->data.binaryNum!= this->data.val && this->data.otherNum!= this->data.val){
    free(this->params.val);//}
    free(this->params.binaryNum);
    free(this->params.otherNum);
    free(this->context.num);
    delete ui;
}

void freeMatrix(void** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}
