#ifndef DIALOG_CONTRAST_H
#define DIALOG_CONTRAST_H

#include <QDialog>

namespace Ui {
class dialog_contrast;
}

class dialog_contrast : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_contrast(QWidget *parent = 0);
    ~dialog_contrast();

private:
    Ui::dialog_contrast *ui;
};

#endif // DIALOG_CONTRAST_H
