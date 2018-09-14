#include "affinedialog.h"
#include "ui_affinedialog.h"
#include<QDebug>
AffineDialog::AffineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AffineDialog)
{
    ui->setupUi(this);
}

AffineDialog::~AffineDialog()
{
    delete ui;
}

void AffineDialog::on_buttonBox_accepted()
{
    bool flag[9];
    double a0=ui->lineEdit->text().toDouble(&flag[0]);
    double a1=ui->lineEdit_2->text().toDouble(&flag[1]);
    double a2=ui->lineEdit_3->text().toDouble(&flag[2]);
    double a3=ui->lineEdit_4->text().toDouble(&flag[3]);
    double a4=ui->lineEdit_5->text().toDouble(&flag[4]);
    double a5=ui->lineEdit_6->text().toDouble(&flag[5]);
    double a6=ui->lineEdit_7->text().toDouble(&flag[6]);
    double a7=ui->lineEdit_8->text().toDouble(&flag[7]);
    double a8=ui->lineEdit_9->text().toDouble(&flag[8]);
    for(int i = 0; i < 9 ; i++){
        if(!flag[i]){
            return;
        }
    }
    Matrix<double> mat(3,3,0);
    mat(0,0)=a0;
    mat(0,1)=a1;
    mat(0,2)=a2;
    mat(1,0)=a3;
    mat(1,1)=a4;
    mat(1,2)=a5;
    mat(2,0)=a6;
    mat(2,1)=a7;
    mat(2,2)=a8;
    emit(sendMatrix(mat));
    qDebug()<<"send";
    close();
}
