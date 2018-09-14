#include "medianfilterdialog.h"
#include "ui_medianfilterdialog.h"
#include<QDebug>
MedianFilterDialog::MedianFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MedianFilterDialog)
{
    ui->setupUi(this);
}

MedianFilterDialog::~MedianFilterDialog()
{
    delete ui;
}
//中值滤波
void MedianFilterDialog::on_buttonBox_accepted()
{
    qDebug()<<"accept";
    bool ok;
    int size=ui->lineEdit->text().toInt(&ok);
    if(ok)
    {
        if(ui->rBtnGray->isChecked())   pattern="Gray";
        if(ui->rBtnRGB->isChecked())    pattern="RGB";
        qDebug()<<"confirmed:"<<size<<" "<<pattern;
        emit confirmed(size,pattern);
        qDebug()<<"confirmed:"<<size<<" "<<pattern;
    }
    close();
}
