#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
signals:
    void dlgreturn(int);
private:
    Ui::Form *ui;
private slots:
    void emitSlot();
};

#endif // FORM_H
