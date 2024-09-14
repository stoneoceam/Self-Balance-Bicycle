/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFormLayout *formLayout;
    QWidget *widget_7;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_PortNumber;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *comboBox_BaudRate;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *comboBox_FlowControl;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *comboBox_Parity;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *comboBox_DataBits;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QComboBox *comboBox_StopBits;
    QPushButton *pushButton_Update;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_7;
    QPlainTextEdit *plainTextEdit_Recieve;
    QWidget *widget_9;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *lineEdit_Send;
    QWidget *widget_10;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_Open;
    QPushButton *pushButton_Close;
    QPushButton *pushButton_Send;
    QPushButton *pushButton_Clear;
    QWidget *widget_11;
    QHBoxLayout *horizontalLayout_10;
    QCheckBox *checkBox_HexDisplay;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName("formLayout");
        widget_7 = new QWidget(centralwidget);
        widget_7->setObjectName("widget_7");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_7->sizePolicy().hasHeightForWidth());
        widget_7->setSizePolicy(sizePolicy1);
        widget_7->setMinimumSize(QSize(230, 320));
        widget_7->setMaximumSize(QSize(230, 320));
        verticalLayout = new QVBoxLayout(widget_7);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(widget_7);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 5, 5, 5);
        label = new QLabel(widget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        comboBox_PortNumber = new QComboBox(widget);
        comboBox_PortNumber->setObjectName("comboBox_PortNumber");
        comboBox_PortNumber->setMinimumSize(QSize(120, 0));

        horizontalLayout->addWidget(comboBox_PortNumber);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(widget_7);
        widget_2->setObjectName("widget_2");
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(5, 5, 5, 5);
        label_2 = new QLabel(widget_2);
        label_2->setObjectName("label_2");
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_2);

        comboBox_BaudRate = new QComboBox(widget_2);
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->setObjectName("comboBox_BaudRate");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBox_BaudRate->sizePolicy().hasHeightForWidth());
        comboBox_BaudRate->setSizePolicy(sizePolicy2);
        comboBox_BaudRate->setMinimumSize(QSize(85, 0));

        horizontalLayout_2->addWidget(comboBox_BaudRate);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget_7);
        widget_3->setObjectName("widget_3");
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setSpacing(5);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(5, 5, 5, 5);
        label_3 = new QLabel(widget_3);
        label_3->setObjectName("label_3");
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label_3);

        comboBox_FlowControl = new QComboBox(widget_3);
        comboBox_FlowControl->addItem(QString());
        comboBox_FlowControl->addItem(QString());
        comboBox_FlowControl->addItem(QString());
        comboBox_FlowControl->setObjectName("comboBox_FlowControl");
        sizePolicy2.setHeightForWidth(comboBox_FlowControl->sizePolicy().hasHeightForWidth());
        comboBox_FlowControl->setSizePolicy(sizePolicy2);
        comboBox_FlowControl->setMinimumSize(QSize(85, 0));

        horizontalLayout_3->addWidget(comboBox_FlowControl);


        verticalLayout->addWidget(widget_3);

        widget_4 = new QWidget(widget_7);
        widget_4->setObjectName("widget_4");
        horizontalLayout_4 = new QHBoxLayout(widget_4);
        horizontalLayout_4->setSpacing(5);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(5, 5, 5, 5);
        label_4 = new QLabel(widget_4);
        label_4->setObjectName("label_4");
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(label_4);

        comboBox_Parity = new QComboBox(widget_4);
        comboBox_Parity->addItem(QString());
        comboBox_Parity->addItem(QString());
        comboBox_Parity->addItem(QString());
        comboBox_Parity->addItem(QString());
        comboBox_Parity->addItem(QString());
        comboBox_Parity->setObjectName("comboBox_Parity");
        sizePolicy2.setHeightForWidth(comboBox_Parity->sizePolicy().hasHeightForWidth());
        comboBox_Parity->setSizePolicy(sizePolicy2);
        comboBox_Parity->setMinimumSize(QSize(85, 0));

        horizontalLayout_4->addWidget(comboBox_Parity);


        verticalLayout->addWidget(widget_4);

        widget_5 = new QWidget(widget_7);
        widget_5->setObjectName("widget_5");
        horizontalLayout_5 = new QHBoxLayout(widget_5);
        horizontalLayout_5->setSpacing(5);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(5, 5, 5, 5);
        label_5 = new QLabel(widget_5);
        label_5->setObjectName("label_5");
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(label_5);

        comboBox_DataBits = new QComboBox(widget_5);
        comboBox_DataBits->addItem(QString());
        comboBox_DataBits->addItem(QString());
        comboBox_DataBits->addItem(QString());
        comboBox_DataBits->addItem(QString());
        comboBox_DataBits->setObjectName("comboBox_DataBits");
        sizePolicy2.setHeightForWidth(comboBox_DataBits->sizePolicy().hasHeightForWidth());
        comboBox_DataBits->setSizePolicy(sizePolicy2);
        comboBox_DataBits->setMinimumSize(QSize(85, 0));

        horizontalLayout_5->addWidget(comboBox_DataBits);


        verticalLayout->addWidget(widget_5);

        widget_6 = new QWidget(widget_7);
        widget_6->setObjectName("widget_6");
        horizontalLayout_6 = new QHBoxLayout(widget_6);
        horizontalLayout_6->setSpacing(5);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(5, 5, 5, 5);
        label_6 = new QLabel(widget_6);
        label_6->setObjectName("label_6");
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(label_6);

        comboBox_StopBits = new QComboBox(widget_6);
        comboBox_StopBits->addItem(QString());
        comboBox_StopBits->addItem(QString());
        comboBox_StopBits->addItem(QString());
        comboBox_StopBits->setObjectName("comboBox_StopBits");
        sizePolicy2.setHeightForWidth(comboBox_StopBits->sizePolicy().hasHeightForWidth());
        comboBox_StopBits->setSizePolicy(sizePolicy2);
        comboBox_StopBits->setMinimumSize(QSize(85, 0));

        horizontalLayout_6->addWidget(comboBox_StopBits);


        verticalLayout->addWidget(widget_6);

        pushButton_Update = new QPushButton(widget_7);
        pushButton_Update->setObjectName("pushButton_Update");

        verticalLayout->addWidget(pushButton_Update);


        formLayout->setWidget(0, QFormLayout::LabelRole, widget_7);

        widget_8 = new QWidget(centralwidget);
        widget_8->setObjectName("widget_8");
        horizontalLayout_7 = new QHBoxLayout(widget_8);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        plainTextEdit_Recieve = new QPlainTextEdit(widget_8);
        plainTextEdit_Recieve->setObjectName("plainTextEdit_Recieve");
        plainTextEdit_Recieve->setReadOnly(true);

        horizontalLayout_7->addWidget(plainTextEdit_Recieve);


        formLayout->setWidget(0, QFormLayout::FieldRole, widget_8);

        widget_9 = new QWidget(centralwidget);
        widget_9->setObjectName("widget_9");
        horizontalLayout_8 = new QHBoxLayout(widget_9);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        lineEdit_Send = new QLineEdit(widget_9);
        lineEdit_Send->setObjectName("lineEdit_Send");

        horizontalLayout_8->addWidget(lineEdit_Send);


        formLayout->setWidget(1, QFormLayout::FieldRole, widget_9);

        widget_10 = new QWidget(centralwidget);
        widget_10->setObjectName("widget_10");
        horizontalLayout_9 = new QHBoxLayout(widget_10);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        pushButton_Open = new QPushButton(widget_10);
        pushButton_Open->setObjectName("pushButton_Open");

        horizontalLayout_9->addWidget(pushButton_Open);

        pushButton_Close = new QPushButton(widget_10);
        pushButton_Close->setObjectName("pushButton_Close");

        horizontalLayout_9->addWidget(pushButton_Close);

        pushButton_Send = new QPushButton(widget_10);
        pushButton_Send->setObjectName("pushButton_Send");

        horizontalLayout_9->addWidget(pushButton_Send);

        pushButton_Clear = new QPushButton(widget_10);
        pushButton_Clear->setObjectName("pushButton_Clear");

        horizontalLayout_9->addWidget(pushButton_Clear);


        formLayout->setWidget(2, QFormLayout::FieldRole, widget_10);

        widget_11 = new QWidget(centralwidget);
        widget_11->setObjectName("widget_11");
        horizontalLayout_10 = new QHBoxLayout(widget_11);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        checkBox_HexDisplay = new QCheckBox(widget_11);
        checkBox_HexDisplay->setObjectName("checkBox_HexDisplay");

        horizontalLayout_10->addWidget(checkBox_HexDisplay);


        formLayout->setWidget(1, QFormLayout::LabelRole, widget_11);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        comboBox_BaudRate->setCurrentIndex(6);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\347\253\257\345\217\243\345\217\267", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", nullptr));
        comboBox_BaudRate->setItemText(0, QCoreApplication::translate("MainWindow", "2400", nullptr));
        comboBox_BaudRate->setItemText(1, QCoreApplication::translate("MainWindow", "4800", nullptr));
        comboBox_BaudRate->setItemText(2, QCoreApplication::translate("MainWindow", "9600", nullptr));
        comboBox_BaudRate->setItemText(3, QCoreApplication::translate("MainWindow", "19200", nullptr));
        comboBox_BaudRate->setItemText(4, QCoreApplication::translate("MainWindow", "38400", nullptr));
        comboBox_BaudRate->setItemText(5, QCoreApplication::translate("MainWindow", "57600", nullptr));
        comboBox_BaudRate->setItemText(6, QCoreApplication::translate("MainWindow", "115200", nullptr));
        comboBox_BaudRate->setItemText(7, QCoreApplication::translate("MainWindow", "128000", nullptr));
        comboBox_BaudRate->setItemText(8, QCoreApplication::translate("MainWindow", "230400", nullptr));
        comboBox_BaudRate->setItemText(9, QCoreApplication::translate("MainWindow", "256000", nullptr));
        comboBox_BaudRate->setItemText(10, QCoreApplication::translate("MainWindow", "460800", nullptr));

        label_3->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\346\265\201\346\216\247", nullptr));
        comboBox_FlowControl->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));
        comboBox_FlowControl->setItemText(1, QCoreApplication::translate("MainWindow", "Hard", nullptr));
        comboBox_FlowControl->setItemText(2, QCoreApplication::translate("MainWindow", "Soft", nullptr));

        label_4->setText(QCoreApplication::translate("MainWindow", "\346\240\241\351\252\214\344\275\215", nullptr));
        comboBox_Parity->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));
        comboBox_Parity->setItemText(1, QCoreApplication::translate("MainWindow", "Even", nullptr));
        comboBox_Parity->setItemText(2, QCoreApplication::translate("MainWindow", "Odd", nullptr));
        comboBox_Parity->setItemText(3, QCoreApplication::translate("MainWindow", "Space", nullptr));
        comboBox_Parity->setItemText(4, QCoreApplication::translate("MainWindow", "Mark", nullptr));

        label_5->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215\346\225\260", nullptr));
        comboBox_DataBits->setItemText(0, QCoreApplication::translate("MainWindow", "8", nullptr));
        comboBox_DataBits->setItemText(1, QCoreApplication::translate("MainWindow", "7", nullptr));
        comboBox_DataBits->setItemText(2, QCoreApplication::translate("MainWindow", "6", nullptr));
        comboBox_DataBits->setItemText(3, QCoreApplication::translate("MainWindow", "5", nullptr));

        label_6->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215\346\225\260", nullptr));
        comboBox_StopBits->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        comboBox_StopBits->setItemText(1, QCoreApplication::translate("MainWindow", "1.5", nullptr));
        comboBox_StopBits->setItemText(2, QCoreApplication::translate("MainWindow", "2", nullptr));

        pushButton_Update->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260\344\270\262\345\217\243", nullptr));
        pushButton_Open->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        pushButton_Close->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\344\270\262\345\217\243", nullptr));
        pushButton_Send->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        pushButton_Clear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        checkBox_HexDisplay->setText(QCoreApplication::translate("MainWindow", "16\350\277\233\345\210\266\346\230\276\347\244\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
