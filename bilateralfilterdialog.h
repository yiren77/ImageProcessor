#ifndef BILATERALFILTERDIALOG_H
#define BILATERALFILTERDIALOG_H

#include <QDialog>

namespace Ui {
class BilateralFilterDialog;
}

class BilateralFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BilateralFilterDialog(QWidget *parent = 0);
    ~BilateralFilterDialog();

private:
    Ui::BilateralFilterDialog *ui;
public slots:
    void on_buttonBox_accepted();
signals:
    void confirmed(int,double,double);


};

#endif // BILATERALFILTERDIALOG_H
