#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QString>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QStringList serialNamePorts;
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &portInfo : serialPortInfos)
    {
        serialNamePorts<<portInfo.portName();
    }
    ui->comboBox_PortNumber->addItems(serialNamePorts);

    sericalPort = new QSerialPort(this);

    connect(sericalPort,SIGNAL(readyRead()),this,SLOT(serialPortReadyRead_Slot()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_Open_clicked()
{
    QSerialPort::BaudRate baudRate;
    QSerialPort::FlowControl flowcontrol;
    QSerialPort::Parity parity;
    QSerialPort::DataBits dataBits;
    QSerialPort::StopBits stopBits;

    switch (ui->comboBox_BaudRate->currentIndex()) {
    case 0:
        baudRate = (QSerialPort::BaudRate)2400;
        break;
    case 1:
        baudRate = (QSerialPort::BaudRate)4800;
        break;
    case 2:
        baudRate = (QSerialPort::BaudRate)9600;
        break;
    case 3:
        baudRate = (QSerialPort::BaudRate)19200;
        break;
    case 4:
        baudRate = (QSerialPort::BaudRate)38400;
        break;
    case 5:
        baudRate = (QSerialPort::BaudRate)57600;
        break;
    case 6:
        baudRate = (QSerialPort::BaudRate)115200;
        break;
    case 7:
        baudRate = (QSerialPort::BaudRate)128000;
        break;
    case 8:
        baudRate = (QSerialPort::BaudRate)230400;
        break;
    case 9:
        baudRate = (QSerialPort::BaudRate)256000;
        break;
    case 10:
        baudRate = (QSerialPort::BaudRate)460800;
        break;
    default:
        break;
    }
    switch (ui->comboBox_FlowControl->currentIndex()) {
    case 0:
        flowcontrol = QSerialPort::NoFlowControl;
        break;
    case 1:
        flowcontrol = QSerialPort::HardwareControl;
        break;
    case 2:
        flowcontrol = QSerialPort::SoftwareControl;
        break;
    default:
        break;
    }
    switch (ui->comboBox_Parity->currentIndex()) {
    case 0:
        parity = QSerialPort::NoParity;
        break;
    case 1:
        parity = QSerialPort::EvenParity;
        break;
    case 2:
        parity = QSerialPort::OddParity;
        break;
    case 3:
        parity = QSerialPort::SpaceParity;
        break;
    case 4:
        parity = QSerialPort::MarkParity;
        break;
    default:
        break;
    }
    switch (ui->comboBox_DataBits->currentIndex()) {
    case 0:
        dataBits = QSerialPort::Data8;
        break;
    case 1:
        dataBits = QSerialPort::Data7;
        break;
    case 2:
        dataBits = QSerialPort::Data6;
        break;
    case 3:
        dataBits = QSerialPort::Data5;
        break;
    default:
        break;
    }
    switch (ui->comboBox_StopBits->currentIndex()) {
    case 0:
        stopBits = QSerialPort::OneStop;
        break;
    case 1:
        stopBits = QSerialPort::OneAndHalfStop;
        break;
    case 2:
        stopBits = QSerialPort::TwoStop;
        break;
    default:
        break;
    }

    sericalPort->setPortName(ui->comboBox_PortNumber->currentText());
    sericalPort->setBaudRate(baudRate);
    sericalPort->setFlowControl(flowcontrol);
    sericalPort->setParity(parity);
    sericalPort->setDataBits(dataBits);
    sericalPort->setStopBits(stopBits);

    if(sericalPort->open(QIODevice::ReadWrite) == true){
        QMessageBox::information(this,"提示","成功");
    }
    else{
        QMessageBox::critical(this,"提示","失败");
    }
}


void Widget::on_pushButton_Close_clicked()
{
    sericalPort->close();
}

void Widget::serialPortReadyRead_Slot()
{
    QString Recieve_buff;
    Recieve_buff = QString(sericalPort->readAll());
    ui->plainTextEdit_Recieve->insertPlainText(Recieve_buff);//用append会多一个换行
    ui->plainTextEdit_Recieve->moveCursor(QTextCursor::End);  //调整光标位置到最新接收的尾部，避免看不到最新接收的数据
}


void Widget::on_pushButton_Send_clicked()
{
    sericalPort->write(ui->lineEdit_Send->text().toLocal8Bit().data());
}


void Widget::on_pushButton_Clear_clicked()
{
    ui->plainTextEdit_Recieve->clear();

}

