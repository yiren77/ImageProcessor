#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H
#include<QImage>
#include<QRgb>
#include<matrixtemplate.h>
struct HSI
{
    double H;
    double S;
    double I;

};
class imageprocessor
{
public:
    imageprocessor();
    static QImage rgb2gray(const QImage&);
    static QImage logTransformation(const QImage&,double c);
    static QImage inverse(const QImage&);
    static QImage Histeq(const QImage&);
    static QImage colorHisteq(const QImage&);
    static QImage colorHisteq1(const QImage&);
    static void comulateHist(int*hist,int *map,double N);
    static HSI rgb2hsi(QRgb);
    static QRgb hsi2rgb( HSI &);
    static double min( double var_R, double var_G, double var_B );
    static double max( double var_R, double var_G, double var_B );
    static double Hue_2_RGB(double v1, double v2, double vH);
    //spatial
    static QImage LinearFilter(const QImage&,std::vector<double> &,int & nCol,const QString pattern);
    static QImage filter(const QImage &,std::vector<double> &,int nCol,int nRow,QString pattern);
    static QImage GaussBlur(const QImage &,int size,double sigma,QString pattern);
    static QImage BilaterialFilter(const QImage&,int size,double sigmaColor,double sigmaSpace);
    static QImage MedianFilter(const QImage&,int size,QString filterpattern,QString pattern);
    static QImage ExpandFilter(const QImage&,int size,QString filterpattern,QString pattern);
    static QImage CorrosionFilter(const QImage&,int size,QString filterpattern,QString pattern);
    static QImage NonLinearFilter(const QImage&,int size, QString filterpattern,QString pattern);
    static QImage  zeroPadding(const QImage&,int nCol,int nRow);
    static QImage  crop(const QImage&,int nCol,int nRow);
    static std::vector<int> getPatch(const QImage &img,int w,int h,int nCol,int nRow,char c);
    static void kernelNormalization(std::vector<double> &);
    static std::vector<double> createGaussKernel(int size,double sigma);
    static std::vector<double> creatBilateralKernel(double sigmaColor);
    static QImage rotation(const QImage &img, Matrix<double> matrix);
    static QRgb bilinearInterpolation(double x, double y, const QImage & img);
    static int max(int,int,int,int);
    static int min(int,int,int,int);
};

#endif // IMAGEPROCESSOR_H
