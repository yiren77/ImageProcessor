#include "expanddialog.h"
#include "ui_expanddialog.h"

ExpandDialog::ExpandDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExpandDialog)
{

    ui->setupUi(this);
}

ExpandDialog::~ExpandDialog()
{
    delete ui;
}
//膨胀

void ExpandDialog::on_ButtonBox_accepted()
{
    bool ok;
    int size=ui->lineEdit->text().toInt(&ok);
    if(ok)
    {
        if(ui->rBtnGray->isChecked())   pattern="Gray";
        if(ui->rBtnRGB->isChecked())    pattern="RGB";
        emit send_info(size,pattern);
    }
    close();
}
