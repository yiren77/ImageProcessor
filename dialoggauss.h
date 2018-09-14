#ifndef DIALOGGAUSS_H
#define DIALOGGAUSS_H

#include <QDialog>

namespace Ui {
class DialogGauss;
}

class DialogGauss : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGauss(QWidget *parent = 0);
    ~DialogGauss();

private:
    Ui::DialogGauss *ui;
    QString pattern;
public slots:
    void on_buttonBox_accepted();
signals:
    void confirmed(int,double,QString);

};

#endif // DIALOGGAUSS_H
