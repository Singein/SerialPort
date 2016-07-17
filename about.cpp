#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->setWindowTitle("关于”ASA SerialPort APP”");
    this->setMaximumHeight(288);
    this->setMaximumWidth(530);
    QImage *logo = new QImage(":/new/prefix1/C:/Users/Fuerm/Desktop/ASA.png");
    ui->label->setPixmap(QPixmap::fromImage(*logo));
    ui->label->adjustSize();
}

About::~About()
{
    delete ui;
}
