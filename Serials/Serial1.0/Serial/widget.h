#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QSerialPort * sericalPort;
private slots:
    void on_pushButton_Open_clicked();

    void on_pushButton_Close_clicked();

    void serialPortReadyRead_Slot();

    void on_pushButton_Send_clicked();

    void on_pushButton_Clear_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
