#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mypixmapitem.h"
#include <QFileDialog>
#include <QStringList>
#include <Qdebug>
#include <QImage>
#include<QGraphicsScene>
#include<QGraphicsPixmapItem>
#include<QPixmap>
#include<QDir>
#include<QFile>
#include<imageprocessor.h>
#include<matrixtemplate.h>
#include<fft.h>
#include<freqfilter.h>
using std::complex;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), scene(NULL),pixmapItem(NULL),
    dlgLinear(new DialogLinear),
    gbDlg(new DialogGauss),
    bfDlg(new BilateralFilterDialog),
    mfDlg(new MedianFilterDialog),
    cDlg(new CorrosionDialog),
    eDlg(new ExpandDialog),
    aDlg(new AffineDialog),
    FDlg(new FreqFilter)
    //fileDialog = new QFileDialog(this);

{
    dlgLog= new Dialoglog(this);
    fileDialog = new QFileDialog(this);//不是最好的
    fileDialog->setNameFilter("Image(*.bmp *.jpg *.png)");
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    connect(dlgLinear,SIGNAL(confirmed(QString,QString)),this,SLOT(on_DialogLinear_confirmed(QString,QString)));
    connect(gbDlg,SIGNAL(confirmed(int,double,QString)),this,SLOT(on_DialogGauss_confirmed(int,double,QString)));
    connect(bfDlg,SIGNAL(confirmed(int,double,double)),this,SLOT(on_BilateralFilterDialog_confirmed(int,double,double)));
    connect(mfDlg,SIGNAL(confirmed(int,QString)),this,SLOT(on_MedianFilterDialog_confirmed(int,QString)));
    connect(cDlg,SIGNAL(confirmed(int,QString)),this,SLOT(on_CorrosionDialog_confirmed(int,QString)));
    connect(eDlg,SIGNAL(send_info(int,QString)),this,SLOT(on_ExpandDialog_confirmed(int,QString)));
    connect(aDlg,SIGNAL(sendMatrix(Matrix<double>)),this,SLOT(on_AffineDialog_sendMatrix(Matrix<double>)));
    connect(FDlg,SIGNAL(confirmed(double,double)),this,SLOT(on_FreqFilter_confirmed(double,double)));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete fileDialog;
    delete pixmapItem;
    delete scene;
    delete dlgLog;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_A) last();
    if(event->key()==Qt::Key_D) next();
    if(event->key()==Qt::Key_S) on_actionsave_triggered();
    if(event->key()==Qt::Key_R) resetImage();
    if(event->key()==Qt::Key_O) open();

}
void MainWindow::on_open_clicked()
{
    open();
}


void MainWindow::on_reset_clicked()
{
    resetImage();
}void MainWindow::on_last_clicked()
{
    last();
}
void MainWindow::on_next_clicked()
{
    next();
}
void MainWindow::on_actionOpen_triggered()
{
    open();
}
void MainWindow::on_actionPrevious_triggered()
{
    last();
}
void MainWindow::on_actionNext1_triggered()
{
    next();
}
void MainWindow::on_actionReset_triggered()
{
    resetImage();
}
void MainWindow::on_actionsave_triggered()
{
    //待写
    QImage img;

    if(getDisplayImage(img)){

        QString filename = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("*.png;; *.jpg;;"));
        if(filename.isEmpty()){
            return;
        }else{
            if(!(img.save(filename))){
                return;
            }
        }
    }
}
void MainWindow::on_save_clicked()
{
    QImage img;

    if(getDisplayImage(img)){

        QString filename = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("*.png;; *.jpg;;"));
        if(filename.isEmpty()){
            return;
        }else{
            if(!(img.save(filename))){
                return;
            }
        }
    }
}

//重置
void MainWindow::resetImage()
{
    pixmapItem->reset();
    QRectF rect =pixmapItem->boundingRect();
    scene->setSceneRect(0,0,rect.width(),rect.height());
    ui->graphicsView->fitInView(rect,Qt::KeepAspectRatio);//保持纵横比
}
//打开图像
void MainWindow::open()
{
    qDebug()<<"test";
    if(fileDialog->exec())
    {
        QStringList files =fileDialog->selectedFiles();
        QDir dir=fileDialog->directory();
        QStringList filters;
        filters<<"*.bmp"<<"*.jpg"<<"*.png";
        fileList=dir.entryInfoList(filters);//获取过滤后得到文件夹下的信息列表
        for(int i=0;i<fileList.size();i++)
        {
            if(fileList[i].absoluteFilePath()==files[0])
            {
                curFileIndx=i;
            }
        }
        qDebug() << files[0]<<"\t"<<curFileIndx;//输出路径
        showImage(QImage(fileList[curFileIndx].absoluteFilePath()));
}
}
void MainWindow::showImage(QImage img)
{
    //防止打开多张图片浪费内存
    if(pixmapItem)
    {
        delete pixmapItem;
        pixmapItem=NULL;
    }
    if(scene)
    {
        delete scene;
        scene=NULL;
    }
    //
    pixmapItem =new Mypixmapitem();
    pixmapItem->setPixmap(QPixmap::fromImage(img));//显示图像
    scene = new QGraphicsScene(this);//显示画布
    scene->addItem(pixmapItem);
    ui->graphicsView->setScene(scene);

}
//上一张
void MainWindow::last()
{
    //判断是否是第一张
    if(curFileIndx==0)
    {
         curFileIndx= fileList.size();
     }
 showImage(QImage(fileList[--curFileIndx].absoluteFilePath()));
 resetImage();
}
//下一张
void MainWindow::next()
{
    //判断是否是最后一张
    if(curFileIndx==fileList.size()-1)
    {
        curFileIndx= -1;
    }
    showImage(QImage(fileList[++curFileIndx].absoluteFilePath()));
    resetImage();
}

void MainWindow::on_actionRgb2gray_triggered()
{

    QImage img;
    if(getDisplayedImage(img)){
        QImage res = imageprocessor::rgb2gray(img);
        showImage(res);
    }

}
void MainWindow::on_actioninverse_triggered()
{
    QImage img;
    if(getDisplayedImage(img)){
        QImage res = imageprocessor::inverse(img);
        showImage(res);
    }
}
void MainWindow::on_actionlogtransform_triggered()
{
    dlgLog->exec();
}
void MainWindow::on_Dialoglog_confirmed(double c)
{
    qDebug()<<"received c:"<<c;
    QImage img;
    if(getDisplayedImage(img)){
        QImage res = imageprocessor::logTransformation(img,c);
        showImage(res);

    }
}

void MainWindow::on_actionHistEq_triggered(){
    QImage img;
    if(getDisplayedImage(img)){
        QImage res = imageprocessor::Histeq(img);
        showImage(res);
    }
}
void MainWindow::on_actionColorHistEq_triggered(){
    QImage img;
    if(getDisplayedImage(img)){
        QImage res = imageprocessor::colorHisteq(img);
        showImage(res);
    }
}
void MainWindow::on_actionColorHisteq1_triggered(){
    QImage img;
    if(getDisplayedImage(img)){
        QImage res = imageprocessor::colorHisteq1(img);
        showImage(res);
    }
}
void MainWindow::on_actionFFT_triggered()
{
    QImage img;
    if(getDisplayImage(img)){

        Matrix<int> g = Matrix<int>::fromQImage(img,'h');
        Matrix<std::complex<double> > ff = fft2d(g, g.getNRow(), g.getNCol());
        Matrix<double> ffta = Matrix<double>::abs4complex(ff);
        Matrix<double> fftl = Matrix<double>::logtranslate(ffta, 1);
        Matrix<double>::fftshift(fftl);
        Matrix<int> fftres = Matrix<int>::normalization(fftl);
        QImage res = Matrix<int>::toQImage(fftres);
        showImage(res);
    }
}
void MainWindow::on_actionLP_triggered(){
    FreFilter='l';
    FDlg->exec();
}
void MainWindow::on_actionHP_triggered(){
    FreFilter='h';
    FDlg->exec();
}
void MainWindow::on_FreqFilter_confirmed(double n, double d){
    QImage img;
    if(getDisplayImage(img)){

        Matrix<int> g = Matrix<int>::fromQImage(img,'h');
        Matrix<double> filter(g.getNRow(),g.getNCol(),0);
        filter = Matrix<double>::ButterworthFilter(g.getNRow(),g.getNCol(),d,n,FreFilter);
        Matrix<double> butterfilter(g.getNRow(),g.getNCol(),0);
        Matrix<std::complex<double> > ff = fft2d(g, g.getNRow(), g.getNCol());
        Matrix<double> ffta = Matrix<double>::abs4complex(ff);
        Matrix<double> fftl = Matrix<double>::logtranslate(ffta, 1);
        Matrix<double>::fftshift(fftl);
        for(int i=0;i<g.getNRow();i++)
        {
            for(int j=0;j<g.getNCol();j++){

                butterfilter(i,j)=filter(i,j)*fftl(i,j);
            }
        }
        Matrix<int> fftres = Matrix<int>::normalization(butterfilter);
        QImage res = Matrix<int>::toQImage(fftres);
        showImage(res);
    }
}
bool MainWindow::getDisplayedImage(QImage &img) const
{
    QList<QGraphicsItem*> items =ui->graphicsView->scene()->items();
    if(items.size()==0) return false;
    QGraphicsPixmapItem* item =(QGraphicsPixmapItem*)items.at(0);
    img = item->pixmap().toImage();
    return true;
}
void MainWindow::on_actionTransformation_triggered()
{
    aDlg->exec();
}
void MainWindow::on_AffineDialog_sendMatrix(Matrix<double> matrix){
    QImage img;
    if(getDisplayedImage(img)){

        qDebug()<<" start to rotation";
        showImage(imageprocessor::rotation(img,matrix));
    }
}
void MainWindow::on_DialogLinear_confirmed(QString str,QString pattern)
{
    qDebug()<<"accept succeed";
    int nCol;
    QImage img;
    vector<double> kernel=parseMatrixl(str,nCol);
    qDebug()<<"accept nCol"<<nCol;
    if(getDisplayImage(img)){
        QImage res=imageprocessor::LinearFilter(img,kernel,nCol,pattern);
        showImage(res);
    }
}
void MainWindow::on_DialogGauss_confirmed(int size, double sigma,QString pattern)
{
    qDebug()<<"implement";
    QImage img;
    bool ok=getDisplayImage(img);
    if(ok)
        showImage(imageprocessor::GaussBlur(img,size,sigma,pattern));
}
void MainWindow::on_BilateralFilterDialog_confirmed(int size, double sigmaColor, double sigmaSpace)
{
    QImage img;
    bool ok=getDisplayImage(img);
    if(ok)
        showImage(imageprocessor::BilaterialFilter(img,size,sigmaColor,sigmaSpace));
}
void MainWindow::on_MedianFilterDialog_confirmed(int size,QString pattern)
{
    QImage img;
    bool ok=getDisplayImage(img);
    qDebug()<<"get";
    if(ok)
        showImage(imageprocessor::MedianFilter(img,size,"median",pattern));
}

void MainWindow::on_CorrosionDialog_confirmed(int size, QString pattern)
{
    QImage img;
    bool ok=getDisplayImage(img);
    qDebug()<<"get";
    if(ok)
        showImage(imageprocessor::CorrosionFilter(img,size,"corrosion",pattern));
}
void MainWindow::on_ExpandDialog_confirmed(int size, QString pattern){
    QImage img;
    bool ok=getDisplayImage(img);
    qDebug()<<"get";
    if(ok)
        showImage(imageprocessor::ExpandFilter(img,size,"expand",pattern));
}

void MainWindow::on_actionLinear_triggered()
{
    dlgLinear->exec();
}
void MainWindow::on_actionGaussBlur_triggered()
{
   gbDlg->exec();
}
void MainWindow::on_actionBilateralFilter_triggered()
{
    bfDlg->exec();
}
void MainWindow::on_actionMedianFilter_triggered()
{
    mfDlg->exec();
}
void MainWindow::on_actionCorrosionFilter_triggered()
{
    cDlg->exec();
}
void MainWindow::on_actionExpandFilter_triggered()
{
    eDlg->exec();
}
//解析矩阵
vector<double> MainWindow::parseMatrixl(QString txt, int &nCol)
{
    //split into row by
    QStringList rows =txt.replace("\n","").trimmed().split(QRegularExpression("\\s*;"));
    nCol = -1;
    vector<double> ret;
    //process each row
    for(int i=0;i<rows.size();++i)
    {
        bool ok;
        QString row = rows[i];
        if(row.trimmed().isEmpty())
            continue;
        //first row
        if(nCol == -1)
        {
            int temp;
            ok = readOneRow(row,ret,temp);
            if(ok)
                nCol= temp;
            else
                return vector<double>();

        }
        //other row
        else
        {
            int temp;
            ok=readOneRow(row,ret,temp);
            if(ok&&temp==nCol)
                continue;
            else
            {
                nCol=-1;
                return vector<double>();
            }
        }
    }
    imageprocessor::kernelNormalization(ret);
    return ret;
}
//解析每一行
bool MainWindow::readOneRow(QString row, std::vector<double> &kernel, int &nCol)
{
    nCol=0;
    //split into number by , and \s
    QStringList cols = row.trimmed().split(QRegularExpression("\\s*,|\\s+"));
    qDebug()<<"cols"<<cols;
    for(int j=0;j<cols.size();++j)
    {
        //parse each col
        bool ok;
        QString col = cols[j];
        if(col.trimmed().isEmpty())
            continue;
        double d=col.trimmed().toDouble(&ok);
        if(ok)
        {
            nCol++;
            qDebug()<<d;
            kernel.push_back(d);
        }
        else
            return false;
    }
    return true;
}
bool MainWindow::getDisplayImage(QImage &img) const
{
   QList<QGraphicsItem *> items = ui->graphicsView->scene()->items();
   if(items.size()==0) return false;
   QGraphicsPixmapItem*  item =(QGraphicsPixmapItem*)items.at(0);
   img = item->pixmap().toImage();
   return true;
}

