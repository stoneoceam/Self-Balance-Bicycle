/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPlainTextEdit *plainTextEdit_Recieve;
    QLineEdit *lineEdit_Send;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_PortNumber;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *comboBox_BaudRate;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *comboBox_FlowControl;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *comboBox_Parity;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *comboBox_DataBits;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QComboBox *comboBox_StopBits;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton_Open;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Close;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_Send;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_Clear;
    QLabel *label_7;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 480);
        plainTextEdit_Recieve = new QPlainTextEdit(Widget);
        plainTextEdit_Recieve->setObjectName("plainTextEdit_Recieve");
        plainTextEdit_Recieve->setGeometry(QRect(240, 0, 541, 281));
        plainTextEdit_Recieve->setStyleSheet(QString::fromUtf8("border-left: 4px solid rgb(0, 118, 177);\n"
"border-right: 4px solid  rgb(0, 118, 177);\n"
"border-top: 4px solid  rgb(0, 118, 177);\n"
"border-bottom: 4px solid  rgb(0, 118, 177);\n"
"border-radius:5px;"));
        plainTextEdit_Recieve->setReadOnly(true);
        lineEdit_Send = new QLineEdit(Widget);
        lineEdit_Send->setObjectName("lineEdit_Send");
        lineEdit_Send->setGeometry(QRect(240, 300, 541, 41));
        lineEdit_Send->setMinimumSize(QSize(0, 0));
        lineEdit_Send->setStyleSheet(QString::fromUtf8("border-left: 4px solid rgb(0, 118, 177);\n"
"border-right: 4px solid  rgb(0, 118, 177);\n"
"border-top: 4px solid  rgb(0, 118, 177);\n"
"border-bottom: 4px solid  rgb(0, 118, 177);\n"
"border-radius:5px;"));
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 50, 191, 281));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        comboBox_PortNumber = new QComboBox(groupBox);
        comboBox_PortNumber->setObjectName("comboBox_PortNumber");
        comboBox_PortNumber->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(comboBox_PortNumber);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        comboBox_BaudRate = new QComboBox(groupBox);
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

        horizontalLayout_2->addWidget(comboBox_BaudRate);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        comboBox_FlowControl = new QComboBox(groupBox);
        comboBox_FlowControl->addItem(QString());
        comboBox_FlowControl->addItem(QString());
        comboBox_FlowControl->addItem(QString());
        comboBox_FlowControl->setObjectName("comboBox_FlowControl");

        horizontalLayout_3->addWidget(comboBox_FlowControl);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        horizontalLayout_4->addWidget(label_4);

        comboBox_Parity = new QComboBox(groupBox);
        comboBox_Parity->addItem(QString());
        comboBox_Parity->addItem(QString());
        comboBox_Parity->addItem(QString());
        comboBox_Parity->addItem(QString());
        comboBox_Parity->addItem(QString());
        comboBox_Parity->setObjectName("comboBox_Parity");

        horizontalLayout_4->addWidget(comboBox_Parity);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");

        horizontalLayout_5->addWidget(label_5);

        comboBox_DataBits = new QComboBox(groupBox);
        comboBox_DataBits->addItem(QString());
        comboBox_DataBits->addItem(QString());
        comboBox_DataBits->addItem(QString());
        comboBox_DataBits->addItem(QString());
        comboBox_DataBits->setObjectName("comboBox_DataBits");

        horizontalLayout_5->addWidget(comboBox_DataBits);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");

        horizontalLayout_6->addWidget(label_6);

        comboBox_StopBits = new QComboBox(groupBox);
        comboBox_StopBits->addItem(QString());
        comboBox_StopBits->addItem(QString());
        comboBox_StopBits->addItem(QString());
        comboBox_StopBits->setObjectName("comboBox_StopBits");

        horizontalLayout_6->addWidget(comboBox_StopBits);


        verticalLayout->addLayout(horizontalLayout_6);

        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(240, 360, 541, 91));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        pushButton_Open = new QPushButton(layoutWidget);
        pushButton_Open->setObjectName("pushButton_Open");

        horizontalLayout_7->addWidget(pushButton_Open);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        pushButton_Close = new QPushButton(layoutWidget);
        pushButton_Close->setObjectName("pushButton_Close");

        horizontalLayout_7->addWidget(pushButton_Close);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        pushButton_Send = new QPushButton(layoutWidget);
        pushButton_Send->setObjectName("pushButton_Send");

        horizontalLayout_7->addWidget(pushButton_Send);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);

        pushButton_Clear = new QPushButton(layoutWidget);
        pushButton_Clear->setObjectName("pushButton_Clear");

        horizontalLayout_7->addWidget(pushButton_Clear);

        label_7 = new QLabel(Widget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(40, 10, 167, 31));

        retranslateUi(Widget);

        comboBox_BaudRate->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        groupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("Widget", "\347\253\257\345\217\243\345\217\267", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\346\263\242\347\211\271\347\216\207", nullptr));
        comboBox_BaudRate->setItemText(0, QCoreApplication::translate("Widget", "2400", nullptr));
        comboBox_BaudRate->setItemText(1, QCoreApplication::translate("Widget", "4800", nullptr));
        comboBox_BaudRate->setItemText(2, QCoreApplication::translate("Widget", "9600", nullptr));
        comboBox_BaudRate->setItemText(3, QCoreApplication::translate("Widget", "19200", nullptr));
        comboBox_BaudRate->setItemText(4, QCoreApplication::translate("Widget", "38400", nullptr));
        comboBox_BaudRate->setItemText(5, QCoreApplication::translate("Widget", "57600", nullptr));
        comboBox_BaudRate->setItemText(6, QCoreApplication::translate("Widget", "115200", nullptr));
        comboBox_BaudRate->setItemText(7, QCoreApplication::translate("Widget", "128000", nullptr));
        comboBox_BaudRate->setItemText(8, QCoreApplication::translate("Widget", "230400", nullptr));
        comboBox_BaudRate->setItemText(9, QCoreApplication::translate("Widget", "256000", nullptr));
        comboBox_BaudRate->setItemText(10, QCoreApplication::translate("Widget", "460800", nullptr));

        label_3->setText(QCoreApplication::translate("Widget", "\346\225\260\346\215\256\346\265\201\346\216\247", nullptr));
        comboBox_FlowControl->setItemText(0, QCoreApplication::translate("Widget", "None", nullptr));
        comboBox_FlowControl->setItemText(1, QCoreApplication::translate("Widget", "Hard", nullptr));
        comboBox_FlowControl->setItemText(2, QCoreApplication::translate("Widget", "Soft", nullptr));

        label_4->setText(QCoreApplication::translate("Widget", "\346\240\241\351\252\214\344\275\215", nullptr));
        comboBox_Parity->setItemText(0, QCoreApplication::translate("Widget", "None", nullptr));
        comboBox_Parity->setItemText(1, QCoreApplication::translate("Widget", "Even", nullptr));
        comboBox_Parity->setItemText(2, QCoreApplication::translate("Widget", "Odd", nullptr));
        comboBox_Parity->setItemText(3, QCoreApplication::translate("Widget", "Space", nullptr));
        comboBox_Parity->setItemText(4, QCoreApplication::translate("Widget", "Mark", nullptr));

        label_5->setText(QCoreApplication::translate("Widget", "\346\225\260\346\215\256\344\275\215\346\225\260", nullptr));
        comboBox_DataBits->setItemText(0, QCoreApplication::translate("Widget", "8", nullptr));
        comboBox_DataBits->setItemText(1, QCoreApplication::translate("Widget", "7", nullptr));
        comboBox_DataBits->setItemText(2, QCoreApplication::translate("Widget", "6", nullptr));
        comboBox_DataBits->setItemText(3, QCoreApplication::translate("Widget", "5", nullptr));

        label_6->setText(QCoreApplication::translate("Widget", "\345\201\234\346\255\242\344\275\215\346\225\260", nullptr));
        comboBox_StopBits->setItemText(0, QCoreApplication::translate("Widget", "1", nullptr));
        comboBox_StopBits->setItemText(1, QCoreApplication::translate("Widget", "1.5", nullptr));
        comboBox_StopBits->setItemText(2, QCoreApplication::translate("Widget", "2", nullptr));

        pushButton_Open->setText(QCoreApplication::translate("Widget", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        pushButton_Close->setText(QCoreApplication::translate("Widget", "\345\205\263\351\227\255\344\270\262\345\217\243", nullptr));
        pushButton_Send->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
        pushButton_Clear->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272", nullptr));
        label_7->setText(QCoreApplication::translate("Widget", "\344\270\262\345\217\243\346\250\241\345\274\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
