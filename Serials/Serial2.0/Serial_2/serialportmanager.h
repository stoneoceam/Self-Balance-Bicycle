#ifndef SERIALPORTMANAGER_H
#define SERIALPORTMANAGER_H

#include <QObject>
#include <QSerialPortInfo>
#include <QTimer>
#include <QString>

class SerialPortManager : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortManager(QObject *parent = nullptr);

    QStringList availablePortNames();

    QStringList availablePortDescription();
signals:

private:
    void updateAvailablePorts();

private:
    QStringList serialPortNames;
    QStringList serialPortDescription;
    QTimer timer_1s;
};

#endif // SERIALPORTMANAGER_H
