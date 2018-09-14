#ifndef EXPANDDIALOG_H
#define EXPANDDIALOG_H

#include <QDialog>
#include<QString>
namespace Ui {
class ExpandDialog;
}

class ExpandDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExpandDialog(QWidget *parent = 0);
    ~ExpandDialog();

private:
    Ui::ExpandDialog *ui;
    QString pattern;
public:
    void on_ButtonBox_accept();
signals:
    void send_info(int,QString);
private slots:
    void on_ButtonBox_accepted();
};

#endif // EXPANDDIALOG_H
