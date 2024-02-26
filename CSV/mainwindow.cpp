#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    file=createNewString(0, ' ');
    queue=initQueue();
    DArray.size=0;
    DArray.books=(Book*)malloc(0);

    connect(ui->toolButton, &QToolButton::clicked, this, &MainWindow::changeFile);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::displayData);
}

MainWindow::~MainWindow()
{
    freeStr(file);
    delete ui;
}

void MainWindow::openFile(){
    freeStr(file);
    file=copyStr((char*)ui->lineEdit->text().toStdString().c_str());
    int errors=doOperation(LoadData, file, &DArray, &queue, (char*)"", -1, &vals);
    char* mes;
    switch(errors){
    case FileNotFound:{
        char* s[]={(char*)"Файл\n",file, (char*)"\nне найден"};
        mes=join((char**)s, 3, (char*)" ");
        break;
    }default:{
        char* a =intToStr(errors), *b=intToStr(errors+DArray.size);
        char* s[]={(char*)"Загрузка завершена получено ошибок/всего строк: ", a, (char*)"/", b};
        mes=join((char**)s, 4,(char*)" ");
        freeStr(a);
        freeStr(b);
    }
    }

    ui->label_4->setText(mes);
    freeStr(mes);
}
QTableWidgetItem* printRow(char* str){
    return new QTableWidgetItem(str);
}

QTableWidgetItem* printRow(float num){
    QTableWidgetItem* item=new QTableWidgetItem();
    item->setData(Qt::DisplayRole, num);
    return item;}

void MainWindow::displayData(){
    int column = ui->spinBox->value();
    char* reg=copyStr((char*)ui->lineEdit_2->text().toStdString().c_str());
    if(compareStr(reg, (char*)"")){
            column=-1;
}
    doOperation(DisplayData, file, &DArray, &queue, reg, column, &vals);
    freeStr(reg);
    Book b;
    ui->tableWidget->clear();
    QStringList headerLabels;
    headerLabels << "year" << "region" << "ngp" << "birth_rate" << "death_rate" << "gdw" << "urbanization";
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    ui->tableWidget->setRowCount(0);
    for(int i=0;!isEmpty(&queue);++i){
        ui->tableWidget->setRowCount(i+1);
        pop(&b, &queue);
        ui->tableWidget->setItem(i, 0, printRow(b.year));
        ui->tableWidget->setItem(i, 1, printRow(b.region));
        ui->tableWidget->setItem(i, 2, printRow(b.npg));
        ui->tableWidget->setItem(i, 3, printRow(b.birth_rate));
        ui->tableWidget->setItem(i, 4, printRow(b.death_rate));
        ui->tableWidget->setItem(i, 5, printRow(b.gdw));
        ui->tableWidget->setItem(i, 6, printRow(b.urbanization));
    }
    ui->tableWidget_2->setItem(0, 0, printRow(vals.minVal));
    ui->tableWidget_2->setItem(1, 0, printRow(vals.maxVal));
    ui->tableWidget_2->setItem(2, 0, printRow(vals.averageVal));
    ui->tableWidget->show();
}

void MainWindow::changeFile(){
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выбрать файл"), QDir::homePath());
        // filePath содержит путь к выбранному файлу
        if (!filePath.isEmpty()) {
            ui->lineEdit->setText(filePath);
        }
}

