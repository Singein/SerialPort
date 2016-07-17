#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    this->setWindowTitle("SET TIME (ms)");
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(emitSlot()));
}

Form::~Form()
{
    delete ui;
}

void Form::emitSlot()
{
    int i = ui->lineEdit->text().toInt();
    emit dlgreturn(i);
    this->close();
}
