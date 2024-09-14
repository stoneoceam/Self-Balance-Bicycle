#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSerialPort>
#include <QStringList>



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSerialPort * sericalPort;

private slots:
    void on_pushButton_Open_clicked();

    void on_pushButton_Close_clicked();

    void on_pushButton_Send_clicked();

    void on_pushButton_Clear_clicked();

    void serialPortReadyRead_Slot();

    void on_pushButton_Update_clicked();

    void on_checkBox_HexDisplay_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;

    QStringList * portNames;

    QByteArray * Recieve_buff;//数据接收缓冲队列

    bool target;

};
#endif // MAINWINDOW_H
