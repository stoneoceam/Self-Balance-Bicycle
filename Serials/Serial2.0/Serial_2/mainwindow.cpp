#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QString>

#include "bluetooth.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sericalPort = new QSerialPort(this);

    portNames = new QStringList;

    Recieve_buff = new QByteArray;

    target = 0;

    connect(sericalPort,SIGNAL(readyRead()),this,SLOT(serialPortReadyRead_Slot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Open_clicked()
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
    }

    sericalPort->setPortName(portNames->value(ui->comboBox_PortNumber->currentIndex()));

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


void MainWindow::on_pushButton_Close_clicked()
{
    sericalPort->close();
}


void MainWindow::on_pushButton_Send_clicked()
{
    sericalPort->write(ui->lineEdit_Send->text().toLocal8Bit().data());
}


void MainWindow::on_pushButton_Clear_clicked()
{
    ui->plainTextEdit_Recieve->clear();
}

void MainWindow::serialPortReadyRead_Slot()
{

    *Recieve_buff += sericalPort->readAll();
    QVector<uint8_t> dataVector(Recieve_buff->begin(), Recieve_buff->end());
    if(dataVector[0] == 0xa5) qDebug()<<"111";
    // QByteArray data = sericalPort->readAll();
    // QVector<uint8_t> dataVector(data.begin(), data.end());

    // if(target)
    // {
    //     ui->plainTextEdit_Recieve->insertPlainText(*Recieve_buff_hex);//用append会多一个换行
    //     ui->plainTextEdit_Recieve->moveCursor(QTextCursor::End);  //调整光标位置到最新接收的尾部，避免看不到最新接收的数据
    // }
    // else
    // {
    //     ui->plainTextEdit_Recieve->insertPlainText(*Recieve_buff);//用append会多一个换行
    //     ui->plainTextEdit_Recieve->moveCursor(QTextCursor::End);  //调整光标位置到最新接收的尾部，避免看不到最新接收的数据
    // }
}

void MainWindow::on_pushButton_Update_clicked()
{
    ui->comboBox_PortNumber->clear();
    portNames->clear();
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        ui->comboBox_PortNumber->addItem(info.portName() + " " + info.description());
        portNames->append(info.portName());
    }

    int mxa_len = 0, v_len = 0;
    for(int idx = 0; idx < ui->comboBox_PortNumber->count(); idx++)
    {
        v_len = ui->comboBox_PortNumber->itemText(idx).length();
        if(mxa_len <= v_len) mxa_len = v_len;					// 得到下拉框中内容最长值的长度
    }
    qDebug()<<mxa_len;
    int pt_val = ui->comboBox_PortNumber->font().pointSize();                // 获取字体的磅值
    qDebug()<<mxa_len * pt_val * 0.75;
    ui->comboBox_PortNumber->setFixedWidth(mxa_len * pt_val * 1.67); // 设置自适应宽度

}


void MainWindow::on_checkBox_HexDisplay_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        target = 1;
    }
    else
    {
        target = 0;
    }
}

