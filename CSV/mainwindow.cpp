#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    canvas;
    ui->gridLayout->replaceWidget(ui->frame, &canvas);
    delete ui->frame;
    connect(ui->toolButton, &QToolButton::clicked, this, &MainWindow::changeFile);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::displayData);


    int ans = doOperation(Initialization, &context, &params);
    canvas.data=&params.data;
    if (ans!=OK){
        qDebug("Error");
        this->~MainWindow();
    }
}

MainWindow::~MainWindow()
{
    freeStr(context.file);
    delete ui;
}

void MainWindow::openFile(){
    freeStr(context.file);
    context.file=copyStr((char*)ui->lineEdit->text().toStdString().c_str());
    int errors=doOperation(LoadData, &context, &params);// file, &DArray, &queue, (char*)"", -1, &vals);
    char* mes;
    switch(errors){
    case FileNotFound:{
        char* s[]={(char*)"Файл\n",context.file, (char*)"\nне найден"};
        mes=join((char**)s, 3, (char*)" ");
        break;
    }default:{
        char* a =intToStr(errors), *b=intToStr(errors+params.DArray.size);
        char* s[]={(char*)"Загрузка завершена\nполучено ошибок/всего строк:\n", a, (char*)"/", b};
        mes=join((char**)s, 4,(char*)" ");
        freeStr(a);
        freeStr(b);
    }}
    ui->label_4->setText(mes);
    freeStr(mes);
}
QTableWidgetItem* printCell(char* str){
    return new QTableWidgetItem(str);
}

QTableWidgetItem* printCell(float num){
    QTableWidgetItem* item=new QTableWidgetItem();
    item->setData(Qt::DisplayRole, num);
    return item;}

int printRow(Row* row, int indRow, QTableWidget* table){
    table->setItem(indRow, 0, printCell(row->year));
    table->setItem(indRow, 1, printCell(row->region));
    table->setItem(indRow, 2, printCell(row->npg));
    table->setItem(indRow, 3, printCell(row->birth_rate));
    table->setItem(indRow, 4, printCell(row->death_rate));
    table->setItem(indRow, 5, printCell(row->gdw));
    table->setItem(indRow, 6, printCell(row->urbanization));
    return OK;}

int printRowInSecondTable(StatisticData* vals, QTableWidget* table){
    table->setItem(0, 0, printCell(vals->minVal));
    table->setItem(1, 0, printCell(vals->maxVal));
    table->setItem(2, 0, printCell(vals->averageVal));
    return OK;}

int printTitles(ListStrings* titles, QTableWidget* table){
    for(int i=0;i<titles->count;++i){
        table->setHorizontalHeaderItem(i, printCell(titles->titles[i]));}
    return OK;}

void MainWindow::displayData(){
    context.column = ui->spinBox->value();
    freeStr(context.region);
    context.region=copyStr((char*)ui->lineEdit_2->text().toStdString().c_str());
    /*if(compareStr(context.region, (char*)"")){
            context.column=-1;
    }*/
    //context.region=copyStr(reg);
    int help= context.column;
    context.column=1;
    doOperation(DisplayData, &context, &params);
    canvas.maxRow=params.vals.maxVal;
    canvas.minRow=params.vals.minVal;
    context.column=help;
    doOperation(DisplayData, &context, &params);
    canvas.maxCol=params.vals.maxVal;
    canvas.minCol=params.vals.minVal;
    doOperation(SortData, &context, &params);
    Row row;
    ui->tableWidget->clear();
    //ui->tableWidget->setUpdatesEnabled(true);
    //ui->tableWidget_2->setUpdatesEnabled(true);
    //QStringList headerLabels;
    //headerLabels << "year" << "region" << "npg" << "birth_rate" << "death_rate" << "gdw" << "urbanization";
    printTitles(&params.titles, ui->tableWidget);
    //ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    ui->tableWidget->setRowCount(params.queue.size);
    for(int i=0;!isEmpty(&params.queue);++i){
        pop(&row, &params.queue);
        printRow(&row, i, ui->tableWidget);
    }
    printRowInSecondTable(&params.vals, ui->tableWidget_2);
    canvas.updateFrame();
    //ui->tableWidget->show();
    //ui->tableWidget_2->show();
    //ui->tableWidget->setUpdatesEnabled(false);
    //ui->tableWidget_2->setUpdatesEnabled(false);
}

void MainWindow::changeFile(){
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выбрать файл"), QDir::homePath());
        // filePath содержит путь к выбранному файлу
        if (!filePath.isEmpty()) {
            ui->lineEdit->setText(filePath);
        }
}

