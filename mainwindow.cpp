#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <form.h>
#include <about.h>
#include <QFile>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)//构造函数
{
    ui->setupUi(this);
    ui->groupBox_4->setMaximumHeight(150);
    //ui->label_recive->setMaximumHeight(20);
    this->setWindowTitle("ASA SeriaPort App");
    serial = new QSerialPort;
    serialStatus = false;
    AutoSend = false;
    PortScan();
    connect(ui->OpenButton,SIGNAL(clicked()),this,SLOT(connectPort()));//打开串口槽连接
    connect(serial,SIGNAL(readyRead()),this,SLOT(recevieData()));//接受数据槽连接
    connect(ui->SendButton,SIGNAL(clicked()),this,SLOT(AOR()));//发送数据槽连接
    connect(ui->ScanButton,SIGNAL(clicked()),this,SLOT(PortScan()));//扫描串口槽连接
    connect(ui->R_ClearButton,SIGNAL(clicked()),this,SLOT(rCountClear()));//已接受清0
    connect(ui->S_ButtonClear,SIGNAL(clicked()),this,SLOT(sCountClear()));//已发送清0
    connect(ui->r_Cls,SIGNAL(clicked()),this,SLOT(r_Cls()));//清空接受区
    connect(ui->s_Cls,SIGNAL(clicked()),this,SLOT(s_Cls()));//清空发送区
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(aboutSlot()));
    connect(ui->actionInstrument,SIGNAL(triggered()),this,SLOT(helpSlot()));

}

MainWindow::~MainWindow()//析构函数
{
    delete ui;
}

void MainWindow::PortScan()//扫描串口
{
    ui->comboBox_Port->clear();
    QList<QSerialPortInfo> coms = QSerialPortInfo::availablePorts();

    for(int i = 0;i < coms.length();i++)
    {
        ui->comboBox_Port->addItem(coms.at(i).portName());
    }
    bytes_recevied = 0;
    bytes_sent = 0;
}

void MainWindow::connectPort()//连接串口
{

    int baudRate = ui->comboBox_Baud->currentIndex();
    int checkBit = ui->comboBox_CheckBit->currentIndex();
    int dataBit = ui->comboBox_DataBit->currentIndex();
    int stopBit = ui->comboBox_StopBit->currentIndex();


    if(serialStatus == false)
    {

        serial->setPortName(ui->comboBox_Port->currentText());

        switch (baudRate) {
        case 0:serial->setBaudRate(QSerialPort::Baud1200);break;
        case 1:serial->setBaudRate(QSerialPort::Baud2400);break;
        case 2:serial->setBaudRate(QSerialPort::Baud4800);break;
        case 3:serial->setBaudRate(QSerialPort::Baud9600);break;
        case 4:serial->setBaudRate(QSerialPort::Baud19200);break;
        case 5:serial->setBaudRate(QSerialPort::Baud38400);break;
        case 6:serial->setBaudRate(QSerialPort::Baud57600);break;
        case 7:serial->setBaudRate(QSerialPort::Baud115200);break;
        default:break;
        }

        switch (dataBit) {
        case 0:serial->setDataBits(QSerialPort::Data5);break;
        case 1:serial->setDataBits(QSerialPort::Data6);break;
        case 2:serial->setDataBits(QSerialPort::Data7);break;
        case 3:serial->setDataBits(QSerialPort::Data8);break;
        default:break;
        }

        switch (stopBit) {
        case 0:serial->setStopBits(QSerialPort::OneStop);break;
        case 1:serial->setStopBits(QSerialPort::OneAndHalfStop);break;
        case 2:serial->setStopBits(QSerialPort::TwoStop);break;
        default:break;
        }

        switch (checkBit) {
        case 0:serial->setParity(QSerialPort::NoParity);break;
        case 1:serial->setParity(QSerialPort::OddParity);break;
        case 2:serial->setParity(QSerialPort::EvenParity);break;
        case 3:serial->setParity(QSerialPort::SpaceParity);break;
        case 4:serial->setParity(QSerialPort::MarkParity);break;
        default:break;
        }

        if(!serial->open(QIODevice::ReadWrite))
        {
            serialStatus = false;
            QMessageBox::information(this,"Error",serial->errorString());
        }
        else
        {
            serialStatus = true;
            ui->comboBox_Baud->setEnabled(false);
            ui->comboBox_CheckBit->setEnabled(false);
            ui->comboBox_DataBit->setEnabled(false);
            ui->comboBox_Port->setEnabled(false);
            ui->comboBox_StopBit->setEnabled(false);
            ui->ScanButton->setEnabled(false);
            ui->OpenButton->setText("断开连接");
        }
    }

    else
    {
        if(serial->isOpen())
        {
            serial->close();
            serialStatus = false;
            ui->comboBox_Baud->setEnabled(true);
            ui->comboBox_CheckBit->setEnabled(true);
            ui->comboBox_DataBit->setEnabled(true);
            ui->comboBox_Port->setEnabled(true);
            ui->comboBox_StopBit->setEnabled(true);
            ui->ScanButton->setEnabled(true);
            ui->OpenButton->setText("打开串口");
        }
    }
}

void MainWindow::sendData()//发送数据
{

    QString message = ui->textEdit_send->toPlainText();

    bytes_sent += message.length();
    ui->label_send->setText("已发送:"+QString::number(bytes_sent)+"字节");
    if(ui->S_checkBox_Hex->isChecked())
        serial->write(message.toLatin1().toHex(),message.length());
    else
        serial->write(message.toUtf8(),message.length());
}

void MainWindow::recevieData()//接受数据
{
    QByteArray message = serial->readAll();
    bytes_recevied += message.length();
    ui->label_recive->setText("已接收:"+QString::number(bytes_recevied)+"字节");

        if(ui->R_checkBox_Hex->isChecked())
            ui->textBrowser->insertPlainText(message.toHex()+" ");//setText(ui->textBrowser->toPlainText()+" "+message.toHex());
        else
            ui->textBrowser->insertPlainText(QString(message)+" ");
}

void MainWindow::rCountClear()//已接收计数清零
{
    ui->label_recive->setText("已接收:0字节");
    bytes_recevied = 0;
}

void MainWindow::sCountClear()//已发送计数清零
{
    ui->label_send->setText("已发送:0字节");
    bytes_sent = 0;
}

void MainWindow::r_Cls()//清空接收区
{
    ui->textBrowser->clear();
}

void MainWindow::s_Cls()//清空发送区
{
    ui->textEdit_send->clear();
}

void MainWindow::autoSend()
{
    if(AutoSend == false)
    {

        w = new Form;
        timer = new QTimer(this);

        connect(w,SIGNAL(dlgreturn(int)),this,SLOT(getTime(int)));
        w->show();

        connect(timer,SIGNAL(timeout()),this,SLOT(sendData()));
        ui->SendButton->setText("停止");
        AutoSend = true;
    }
    else
    {
        timer->stop();
        ui->SendButton->setText("发送");
        AutoSend = false;
    }
}

void MainWindow::getTime(int i)
{
    time = i ;

    timer->start(time);
}

void MainWindow::AOR()
{
    if(ui->checkBox_timer->isChecked())
    {
        autoSend();
    }
    else
        sendData();
}

void MainWindow::aboutSlot()
{
    About *w = new About;
    w->show();
}

void MainWindow::helpSlot()
{
    QUrl *url = new QUrl("http://www.jianshu.com/p/6285612ce147");
    ShellExecuteA(NULL,"open",url->toString().toStdString().c_str(),"","",SW_SHOW);
}
