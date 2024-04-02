#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QSpinBox>



int setComboBox(QComboBox* box, ListStrings* data){
    box->clear();
    for(int i=0;i<data->count;box->addItem(QString(data->titles[i++])));
    return OK;}
int setListWidget(QListWidget* list, ListStrings* data){
    list->clear();
    for(int i=0;i<data->count;list->addItem(QString(data->titles[i++])));
    return OK;}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->gridLayout->replaceWidget(ui->frame, &canvas);
    delete ui->frame;
    connect(ui->toolButton, &QToolButton::clicked, this, &MainWindow::changeFile);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::displayData);
    connect(ui->minYear, SIGNAL(valueChanged(int)), this, SLOT(validationCheck()));
    connect(ui->maxYear, SIGNAL(valueChanged(int)), this, SLOT(validationCheck()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(validationCheck()));
    connect(ui->listWidget, &QListWidget::currentRowChanged, this, &MainWindow::changeCurRegion);
    //connect(ui->listWidget, static_cast<bool(QWidgetList::*)(int)>(&QWidgetList::removeOne), this, &MainWindow::removeRegion);
    connect(ui->addRegion, &QPushButton::clicked, this, &MainWindow::addRegion);
    int ans = doOperation(Initialization, &context, &params);
    canvas.updateFrame(params.data);
    if (ans!=OK){
        qDebug("Error");
        this->~MainWindow();
    }
}


void MainWindow::addRegion(){
    context.addRegion=copyStr((char*)ui->inputRegion->currentText().toStdString().c_str());
    ui->label_4->clear();
    if(doOperation(AddRegion, &context, &params)){
        ui->label_4->setText("Такого региона нет\nили он уже просматривается");
        return;
    }
    ui->listWidget->addItem(QString(context.activeRegions.titles[context.activeRegions.count-1]));
    ui->inputRegion->removeItem(ui->inputRegion->currentIndex());
    //setListWidget(ui->listWidget, &context.activeRegions);
}

void MainWindow::changeCurRegion(int ind){
    context.curRegion=ind;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if (event->key()==Qt::Key_Delete && OK==doOperation(DelRegion, &context, &params)){
        QListWidgetItem* item= ui->listWidget->takeItem(context.curRegion);
        ui->inputRegion->addItem(item->text());
        delete item;
        ui->listWidget->setCurrentRow(context.curRegion);
    }
}


void MainWindow::validationCheck(){
    context.column=ui->comboBox->currentIndex();
    int dynamMinYear=ui->minYear->value();
    int dynamMaxYear=ui->maxYear->value();
    if (dynamMaxYear<dynamMinYear){
        ui->maxYear->setValue(dynamMinYear);
        ui->label_4->setText("Ошибка в годах,\nно я уже поправил)");
    }
}

/*MainWindow::changeListRegions(int ind){

}
*/
MainWindow::~MainWindow(){
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
        ui->maxYear->setValue(context.dynamMaxYear);
        ui->minYear->setValue(context.dynamMinYear);
    }}
    setComboBox(ui->inputRegion, &params.regions);
    setComboBox(ui->comboBox, &params.titles);
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
    context.dynamMinYear=ui->minYear->value();
    context.dynamMaxYear=ui->maxYear->value();
    //context.column = ui->spinBox->value();
    //freeStr(context.region);
    //context.region=copyStr((char*)ui->lineEdit_2->text().toStdString().c_str());
    canvas.maxRow=context.dynamMaxYear;
    canvas.minRow=context.dynamMinYear;
    doOperation(DisplayData, &context, &params);
    canvas.maxCol=params.vals.maxVal;
    canvas.minCol=params.vals.minVal;
    doOperation(SortData, &context, &params);
    Row row;
    ui->tableWidget->clear();
    printTitles(&params.titles, ui->tableWidget);
    //ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    ui->tableWidget->setRowCount(params.queue.size);
    for(int i=0;!isEmpty(&params.queue);++i){
        pop(&row, &params.queue);
        printRow(&row, i, ui->tableWidget);
    }
    printRowInSecondTable(&params.vals, ui->tableWidget_2);
    canvas.updateFrame(params.data);
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

