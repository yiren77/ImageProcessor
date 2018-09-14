#ifndef DIALOGLINEAR_H
#define DIALOGLINEAR_H

#include <QDialog>

namespace Ui {
class DialogLinear;
}

class DialogLinear : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLinear(QWidget *parent = 0);
    ~DialogLinear();

private:
    Ui::DialogLinear *ui;
    QString pattern;
public slots:
    void on_buttonBox_accepted();
signals:
    void confirmed(QString,QString);


};

#endif // DIALOGLINEAR_H
