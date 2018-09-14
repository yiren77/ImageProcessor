#include "bilateralfilterdialog.h"
#include "ui_bilateralfilterdialog.h"
#include<QDebug>
BilateralFilterDialog::BilateralFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BilateralFilterDialog)
{
    ui->setupUi(this);
}

BilateralFilterDialog::~BilateralFilterDialog()
{
    delete ui;
}
//双边滤波
void BilateralFilterDialog::on_buttonBox_accepted()
{
    qDebug()<<"accept";
    bool OkSize,OkSigmaColor,OkSigmaSpace;
    int size =ui->size->text().toInt(&OkSize);
    double sigmaColor=ui->sigmaColor->text().toDouble(&OkSigmaColor);
    double sigmaSpace=ui->sigmaSpace->text().toDouble(&OkSigmaSpace);
    if(OkSigmaColor&&OkSize&&OkSigmaSpace)
    {
        emit confirmed(size,sigmaColor,sigmaSpace);
    }
    close();
}

