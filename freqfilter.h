#ifndef FREQFILTER_H
#define FREQFILTER_H

#include <QDialog>

namespace Ui {
class FreqFilter;
}

class FreqFilter : public QDialog
{
    Q_OBJECT

public:
    explicit FreqFilter(QWidget *parent = 0);
    ~FreqFilter();

private:
    Ui::FreqFilter *ui;
public slots:
    void accept();

signals:
    void confirmed(double,double);
};

#endif // FREQFILTER_H
