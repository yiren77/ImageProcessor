#include "corrosiondialog.h"
#include "ui_corrosiondialog.h"
#include<QDebug>
CorrosionDialog::CorrosionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CorrosionDialog)
{
    ui->setupUi(this);
}

CorrosionDialog::~CorrosionDialog()
{
    delete ui;
}
//腐蚀
void CorrosionDialog::on_buttonBox_accepted()
{
    bool ok;
    int size=ui->lineEdit->text().toInt(&ok);
    if(ok)
    {
        if(ui->rBtnRGB->isChecked())    pattern="RGB";
        if(ui->rBtnGray->isChecked())   pattern="Gray";
        emit confirmed(size,pattern);
    }
    close();
}
