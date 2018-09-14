#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <Qstring>
#include <QMainWindow>
#include <QDebug>
#include <QStringList>
#include<QGraphicsScene>
#include<QGraphicsPixmapItem>
#include "mypixmapitem.h"
#include<QDir>
#include<QFileInfoList>
#include<dialoglog.h>
#include<bilateralfilterdialog.h>
#include<corrosiondialog.h>
#include<dialoggauss.h>
#include<dialoglinear.h>
#include<expanddialog.h>
#include<medianfilterdialog.h>
#include<vector>
#include<affinedialog.h>
#include<freqfilter.h>
#include<QKeyEvent>
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    bool readOneRow(QString row,std:: vector<double>&kernel,int &nCol);
    bool getDisplayImage(QImage &)const;
    ~MainWindow();

private slots:
    void on_open_clicked();

    void on_next_clicked();

    void on_reset_clicked();

    void on_last_clicked();
    void open();
    void resetImage();
    void next();
    void last();
    void showImage(QImage imag);
    void on_actionOpen_triggered();
    void on_actionsave_triggered();
    void on_actionReset_triggered();
    void on_actionNext1_triggered();
    void on_actionPrevious_triggered();
    void on_actionRgb2gray_triggered();
    bool getDisplayedImage(QImage&) const;
    void on_actionlogtransform_triggered();
    void on_Dialoglog_confirmed(double);
    void on_actioninverse_triggered();
    void on_actionColorHistEq_triggered();
    void on_actionHistEq_triggered();
    void on_actionColorHisteq1_triggered();
    void on_actionLinear_triggered();
    void on_actionGaussBlur_triggered();
    void on_actionBilateralFilter_triggered();
    void on_actionMedianFilter_triggered();
    void on_actionCorrosionFilter_triggered();
    void on_actionExpandFilter_triggered();
    void on_actionTransformation_triggered();
    void on_actionFFT_triggered();
    void on_actionLP_triggered();
    void on_actionHP_triggered();
    vector<double> parseMatrixl(QString txt,int& nCol);

    void on_save_clicked();
    void keyPressEvent(QKeyEvent *event);

public slots:
    void on_DialogLinear_confirmed(QString str, QString pattern);
    void on_DialogGauss_confirmed(int size,double sigma,QString pattern);
    void on_BilateralFilterDialog_confirmed(int size,double sigmaColor,double sigmaSpace);
    void on_MedianFilterDialog_confirmed(int size,QString pattern);
    void on_CorrosionDialog_confirmed(int size,QString pattern);
    void on_ExpandDialog_confirmed(int size,QString pattern);
    void on_AffineDialog_sendMatrix(Matrix<double>);
    void on_FreqFilter_confirmed(double n,double d );
private:
    Ui::MainWindow *ui;
    QFileDialog *fileDialog;
    QGraphicsScene *scene;
    Mypixmapitem *pixmapItem;
    QFileInfoList fileList;
    int curFileIndx;
    Dialoglog* dlgLog;
    DialogLinear *dlgLinear;
    DialogGauss *gbDlg;
    BilateralFilterDialog *bfDlg;
    MedianFilterDialog *mfDlg;
    CorrosionDialog *cDlg;
    ExpandDialog *eDlg;
    AffineDialog *aDlg;
    FreqFilter *FDlg;
    char FreFilter;


};

#endif // MAINWINDOW_H
