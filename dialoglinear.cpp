#include "dialoglinear.h"
#include "ui_dialoglinear.h"
#include<QDebug>

DialogLinear::DialogLinear(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLinear)
{
    ui->setupUi(this);
}

DialogLinear::~DialogLinear()
{
    delete ui;
}
//线性滤波
void DialogLinear::on_buttonBox_accepted()
{
    qDebug()<<"accept:";
    QString str=ui->textEdit->toPlainText();
    if(!str.isEmpty())
    {
        if(ui->rBtnRGB->isChecked())    pattern="RGB";
        if(ui->rBtnGray->isChecked())   pattern="Gray";
        emit confirmed(str,pattern);
    }
    close();
}
