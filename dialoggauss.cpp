#include "dialoggauss.h"
#include "ui_dialoggauss.h"
#include<QDebug>
DialogGauss::DialogGauss(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGauss)
{
    ui->setupUi(this);
}

DialogGauss::~DialogGauss()
{
    delete ui;
}
//高斯滤波
void DialogGauss::on_buttonBox_accepted()
{
    qDebug()<<"accept";
    bool OkSize,OkSigma;
    int size =ui->lineEditSize->text().toInt(&OkSize);
    double sigma=ui->lineEditSigma->text().toDouble(&OkSigma);
    if(OkSigma&&OkSize)
    {
        if(ui->rBtnRGB->isChecked())    pattern="RGB";
        if(ui->rBtnGray->isChecked())   pattern="Gray";
        emit confirmed(size,sigma,pattern);
    }
    close();
}
