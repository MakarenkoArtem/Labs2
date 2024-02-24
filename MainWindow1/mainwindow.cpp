#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "enterpoint.h"
#include"QDebug"

void freeMatrix(void** matrix, int rows);

char* errorValue[4]={(char*)"", (char*)"Число больше 4 байт", (char*)"Число не соответсвует системе счиления", (char*)"Просто ошибка"};
char* errorImage[4]={(char*)"", (char*)"", (char*)"", (char*)""};

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
    ui->lineEdit->setText("0");

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

    this->data.val=createNewString(0,'0');
    this->data.binaryNum=createNewString(0,'0');
    this->data.otherNum=createNewString(0,'0');
    this->newData.num=createNewString(0,'0');
    this->data.error=OK;

    validationCheck();
}

void MyMainWindow::copyFunc(){
    QClipboard *clipboard=QGuiApplication::clipboard();
    clipboard->setText(this->data.val);
    //this->data.error=doOperation(Copy, &this->data, &this->newData);
}

void MyMainWindow::changeFunc(){
    this->data.error=doOperation(Change, &this->data, &this->newData);
    int notationIn=this->newData.notationIn,notationOut=this->newData.notationOut;
    ui->lineEdit->setText(QString::fromStdString(string(this->newData.num)));
    qDebug("line %s", this->newData.num);
    switch(notationIn){
    case 2:
        ui->radioButton->setChecked(true);
        break;
    case 10:
        ui->radioButton_2->setChecked(true);
        break;
    default:
        ui->radioButton_3->setChecked(true);
        ui->spinBox->setValue(notationIn);
        qDebug("notationIn %i", notationIn);
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
        ui->radioButton_6->setChecked(true);
        ui->spinBox_3->setValue(notationOut);
        qDebug("notationOut %i", notationOut);
        break;
    }
    this->countingFunc();
}

void MyMainWindow::validationCheck(){
    qDebug("free 25 %s", this->newData.num);
    freeStr(this->newData.num);
    this->newData.num=upperStr(copyStr((char*)ui->lineEdit->text().toStdString().c_str()));
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
    this->data.error=doOperation(Validation, &this->data, &this->newData);
    ui->label_2->setText(QString::fromStdString(string(errorValue[this->data.error])));
}

void MyMainWindow::countingFunc(){
    this->data.error=doOperation(Counting, &this->data, &this->newData);
    ui->label->setText(QString::fromStdString(string(this->data.val)));
    ui->label_2->setText(QString::fromStdString(string(errorValue[this->data.error])));
    ui->label_3->clear();
    int n=0;
    char** filePath=split((char*)QDir::currentPath().toStdString().c_str(), (char*)"/", &n);
    qDebug("free 1");
    free(filePath[n-1]);
    filePath[n-1]=copyStr((char*)"MainWindow1");
    char* image = errorImage[this->data.error];
    if(compareStr(errorValue[this->data.error], (char*)"") && this->newData.notationIn==this->newData.notationOut){
        image=(char*)"/src/tinkoff.jpg";
    }
    char* file=join(filePath, n, (char*)"/");
    file=addStr((char*)realloc(file, (lenStr(file)+lenStr(image)+1)*sizeof(char)),image);
    qDebug("%s", file);
    QPixmap myPixmap(file);//"C:/Users/User/Downloads/MainWindow/src/tinkoff.jpg");
    QSize PicSize(300, 300);
    myPixmap = myPixmap.scaled(PicSize,Qt::KeepAspectRatio);
    ui->label_3->setPixmap( myPixmap );
    qDebug("free 2");
    freeMatrix((void**)filePath, n);
    qDebug("free 3");
    free(file);
}

MyMainWindow::~MyMainWindow()
{
    //if(this->data.binaryNum!= this->data.val && this->data.otherNum!= this->data.val){
    free(this->data.val);//}
    free(this->data.binaryNum);
    free(this->data.otherNum);
    free(this->newData.num);
    delete ui;
}

void freeMatrix(void** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}
