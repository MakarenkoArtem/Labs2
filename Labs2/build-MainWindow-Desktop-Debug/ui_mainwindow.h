/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QVBoxLayout *verticalLayout_9;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_9;
    QSpacerItem *verticalSpacer_14;
    QSpacerItem *verticalSpacer_10;
    QSpacerItem *verticalSpacer_13;
    QSpacerItem *verticalSpacer_16;
    QSpinBox *spinBox;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_7;
    QVBoxLayout *verticalLayout_10;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_11;
    QSpacerItem *verticalSpacer_12;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_19;
    QSpacerItem *verticalSpacer_15;
    QSpacerItem *verticalSpacer_18;
    QSpacerItem *verticalSpacer_17;
    QSpinBox *spinBox_3;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLabel *label_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(685, 460);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"	border-radius : 10px;\n"
"	background-color: rgba(100,100, 225, 165);\n"
"}\n"
"QLabel{\n"
"	border-radius : 5px;\n"
"	background-color: rgba(255,255, 255, 175);\n"
"\n"
"}\n"
"QRadioButton{\n"
"color: rgb(255, 255, 255);\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_12 = new QVBoxLayout(centralwidget);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(280, 0));
        lineEdit->setMaximumSize(QSize(300, 16777215));
        lineEdit->setStyleSheet(QString::fromUtf8("border-radius: 5px;\n"
"background-color: rgb(129, 69, 189);\n"
"color: rgb(255, 255, 255);\n"
"font: 11pt \"Ubuntu\";\n"
"background-color: rgba(255, 46, 245, 100);"));

        horizontalLayout->addWidget(lineEdit);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(280, 0));
        label->setMaximumSize(QSize(300, 16777215));
        label->setStyleSheet(QString::fromUtf8("\n"
"	border-radius : 5px;\n"
"font: 11pt \"Ubuntu\";"));

        horizontalLayout->addWidget(label);

        horizontalLayout->setStretch(0, 1);

        verticalLayout_12->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(centralwidget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setChecked(true);

        verticalLayout->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(centralwidget);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        verticalLayout->addWidget(radioButton_3);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_8);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_6);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_9);

        verticalSpacer_14 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_14);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_10);

        verticalSpacer_13 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_13);

        verticalSpacer_16 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_16);

        spinBox = new QSpinBox(centralwidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setStyleSheet(QString::fromUtf8("font: 11pt \"Ubuntu\";"));
        spinBox->setMinimum(2);
        spinBox->setMaximum(16);

        verticalLayout_9->addWidget(spinBox);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_4);

        verticalSpacer_7 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_7);


        horizontalLayout_3->addLayout(verticalLayout_9);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 23));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(39, 46, 143);\n"
"font: 13pt \"Ubuntu\";\n"
"border-radius: 10px;\n"
"color: white;\n"
"background-color: rgb(0, 85, 255);\n"
""));

        verticalLayout_10->addWidget(pushButton);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(120, 23));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(39, 46, 143);\n"
"font: 13pt \"Ubuntu\";\n"
"border-radius: 10px;\n"
"color: white;\n"
"background-color: rgb(0, 85, 255);\n"
""));

        verticalLayout_10->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(0, 23));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(39, 46, 143);\n"
"font: 13pt \"Ubuntu\";\n"
"border-radius: 10px;\n"
"color: white;\n"
"background-color: rgb(0, 85, 255);\n"
""));

        verticalLayout_10->addWidget(pushButton_3);


        horizontalLayout_3->addLayout(verticalLayout_10);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        radioButton_4 = new QRadioButton(centralwidget);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));
        radioButton_4->setChecked(true);

        verticalLayout_2->addWidget(radioButton_4);

        radioButton_5 = new QRadioButton(centralwidget);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));
        radioButton_5->setChecked(false);

        verticalLayout_2->addWidget(radioButton_5);

        radioButton_6 = new QRadioButton(centralwidget);
        radioButton_6->setObjectName(QString::fromUtf8("radioButton_6"));

        verticalLayout_2->addWidget(radioButton_6);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_11);

        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_12);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        verticalSpacer_19 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_19);

        verticalSpacer_15 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_15);

        verticalSpacer_18 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_18);

        verticalSpacer_17 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_17);

        spinBox_3 = new QSpinBox(centralwidget);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        spinBox_3->setStyleSheet(QString::fromUtf8("font: 11pt \"Ubuntu\";"));
        spinBox_3->setMinimum(2);
        spinBox_3->setMaximum(16);

        verticalLayout_4->addWidget(spinBox_3);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_5);

        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);


        horizontalLayout_3->addLayout(verticalLayout_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_12->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_12->addItem(verticalSpacer_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);\n"
"font: 15pt \"Ubuntu\";"));

        horizontalLayout_4->addWidget(label_2);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(10, 150));
        label_3->setStyleSheet(QString::fromUtf8("\n"
"	background-color: rgba(255,255, 255, 0);\n"
"\n"
""));

        horizontalLayout_4->addWidget(label_3);


        verticalLayout_12->addLayout(horizontalLayout_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 685, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWindow", "\321\201\320\270\321\201\321\202\320\265\320\274\320\260 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\277\320\265\321\200\320\265\320\262\320\265\321\201\321\202\320\270", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\320\272\320\276\320\277\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "<-->", nullptr));
        radioButton_4->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        radioButton_5->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        radioButton_6->setText(QCoreApplication::translate("MainWindow", "\321\201\320\270\321\201\321\202\320\265\320\274\320\260 \320\277\320\276\320\273\321\214\320\267\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        label_2->setText(QString());
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
