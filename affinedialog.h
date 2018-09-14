#ifndef AFFINEDIALOG_H
#define AFFINEDIALOG_H

#include <QDialog>
#include<matrixtemplate.h>
namespace Ui {
class AffineDialog;
}

class AffineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AffineDialog(QWidget *parent = 0);
    ~AffineDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AffineDialog *ui;

signals:
     void sendMatrix(Matrix<double>);
};

#endif // AFFINEDIALOG_H
