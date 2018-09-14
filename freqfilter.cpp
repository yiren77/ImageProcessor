#include "freqfilter.h"
#include "ui_freqfilter.h"

FreqFilter::FreqFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FreqFilter)
{
    ui->setupUi(this);
}

FreqFilter::~FreqFilter()
{
    delete ui;
}
void FreqFilter::accept()
{
    bool ok;
    double n=ui->lineEdit_2->text().toDouble(&ok);
    double d=ui->lineEdit->text().toDouble(&ok);
    if(ok){
        emit confirmed(n,d);
    }
    close();
}
