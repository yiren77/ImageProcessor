#include "dialog_contrast.h"
#include "ui_dialog_contrast.h"

dialog_contrast::dialog_contrast(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_contrast)
{
    ui->setupUi(this);
}

dialog_contrast::~dialog_contrast()
{
    delete ui;
}
