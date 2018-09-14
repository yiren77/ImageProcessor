#ifndef CORROSIONDIALOG_H
#define CORROSIONDIALOG_H

#include <QDialog>
#include<QString>
namespace Ui {
class CorrosionDialog;
}

class CorrosionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CorrosionDialog(QWidget *parent = 0);
    ~CorrosionDialog();

private:
    Ui::CorrosionDialog *ui;
    QString pattern;
public slots:
    void on_buttonBox_accepted();
signals:
    void confirmed(int,QString);
};

#endif // CORROSIONDIALOG_H
