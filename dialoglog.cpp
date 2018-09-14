#include "dialoglog.h"
#include "ui_dialoglog.h""
#include<QDebug>
Dialoglog::Dialoglog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialoglog)
{
    ui->setupUi(this);
}

Dialoglog::~Dialoglog()
{
    delete ui;
}
void Dialoglog::accept()
{
    qDebug()<<"dialog accept";
    bool ok;
    double c= ui->lineEdit->text().toDouble(&ok);
    if(ok){
        emit confirmed(c);
}
    close();
}
