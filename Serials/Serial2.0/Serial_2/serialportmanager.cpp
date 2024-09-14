#include "serialportmanager.h"

SerialPortManager::SerialPortManager(QObject *parent)
    : QObject{parent}
{
    updateAvailablePorts();

    //定期检查可用串口列表
    timer_1s.setInterval(1000);//每秒检查一次
    connect(&timer_1s,SIGNAL(QTimer::timeout()),this,SLOT(SerialPortManager::updateAvailablePorts()));
    timer_1s.start();
}

QStringList SerialPortManager::availablePortNames()
{
    return serialPortNames;
}

QStringList SerialPortManager::availablePortDescription()
{
    return serialPortDescription;
}

void SerialPortManager::updateAvailablePorts()
{
    serialPortNames.clear();

    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &portInfo : serialPortInfos)
    {
        serialPortNames<<portInfo.portName();
        serialPortDescription<<portInfo.description();

    }
}
