#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort\QtSerialPort>
#include <QtSerialPort\QSerialPortInfo>
#include <QTimer>
#include <form.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void PortScan();
    void connectPort();
    void sendData();
    void recevieData();
    void rCountClear();
    void sCountClear();
    void r_Cls();
    void s_Cls();
    void autoSend();
    void AOR();
    void getTime(int i);
    void aboutSlot();
    void helpSlot();



private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    bool serialStatus,AutoSend;
    int bytes_recevied,bytes_sent;
    QTimer *timer;
    Form *w;
    int time;
};

#endif // MAINWINDOW_H
