#ifndef MEDIANFILTERDIALOG_H
#define MEDIANFILTERDIALOG_H

#include <QDialog>
#include<QString>
namespace Ui {
class MedianFilterDialog;
}

class MedianFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MedianFilterDialog(QWidget *parent = 0);
    ~MedianFilterDialog();

private:
    Ui::MedianFilterDialog *ui;
    QString pattern;
public slots:
    void on_buttonBox_accepted();
signals:
    void confirmed(int,QString);

};

#endif // MEDIANFILTERDIALOG_H
