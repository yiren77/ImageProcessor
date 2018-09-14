#include "imageprocessor.h"
#include<QImage>
#include<cmath>
#include<QDebug>
#include<iostream>
#include<algorithm>
#include<qmath.h>
imageprocessor::imageprocessor()
{

}
 QImage imageprocessor::rgb2gray(const QImage & img)
 {
     /*
     QImage ret(img);
     int w =ret.width();
     int h= ret.height();
     for( int i=0; i<w;++i)
     {
         for(int j=0;j<h;++j)
         {
             QRgb rgb=ret.pixel(i,j);
             int r=qRed(rgb);
             int g=qGreen(rgb);
             int b=qBlue(rgb);
             int gray= (r+g+b)/3;
             ret.setPixel(i,j,qRgb(gray,gray,gray));
         }
     }
     return ret;*/
     Matrix<double> Red=Matrix<double>::fromQImage(img,'r');
     Matrix<double> Green=Matrix<double>::fromQImage(img,'g');
     Matrix<double> Blue=Matrix<double>::fromQImage(img,'b');
     Matrix<double> Temp=(Red+Green+Blue);
     Matrix<double> Gray=Temp/3.;
     QImage ret=Matrix<double>::toQImage(Gray);
     return ret;

 }
QImage imageprocessor::inverse(const QImage &img)
{
    /*
    QImage ret(img);
    int w=ret.width();
    int h=ret.height();
    for(int i=0;i<w;++i)
    {
        for(int j=0;j<h;++j)
        {
            QRgb rgb=ret.pixel(i,j);
            int r=qRed(rgb);
            int g=qGreen(rgb);
            int b=qBlue(rgb);
            ret.setPixel(i,j,qRgb(255-r,255-g,255-b));
        }
    }
    return ret;
    */
    Matrix<double> TRed=Matrix<double>::fromQImage(img,'r');
    Matrix<double> TGreen=Matrix<double>::fromQImage(img,'g');
    Matrix<double> TBlue=Matrix<double>::fromQImage(img,'b');
    Matrix<double> Red=255.-TRed;
    Matrix<double> Green=255.-TGreen;
    Matrix<double> Blue=255.-TBlue;
    QImage ret=Matrix<double>::toQImage(Red,Green,Blue);
    return ret;

}
QImage imageprocessor::logTransformation(const QImage &img,double c)
{
/*
    QImage ret(img);
    int w =ret.width();
    int h= ret.height();
    for( int i=0; i<w;++i)
    {
        for(int j=0;j<h;++j)
        {
            QRgb rgb=ret.pixel(i,j);
            double r=qGray(rgb)/255.0;
            int res =c* std::log(1+r)*255;
            if(res>255) res=255;
            if(res<0) res=0;
            ret.setPixel(i,j,qRgb(res,res,res));
        }
    }
    return ret;
*/

     Matrix<double> Gray=Matrix<double>::fromQImage(img,'h');
     Matrix<double> NormGray=Gray/255.0;
     Matrix<double> log=Matrix<double>::logMatirx(NormGray);
     Matrix<double> res_double=255*c*log;
     Matrix<int> res_int=Matrix<int>::D2I(res_double);
     QImage ret=Matrix<double>::toQImage(res_int);
     return ret;

}
QImage imageprocessor::Histeq(const QImage & img)
{
    QImage ret(img);
    int w =ret.width();
    int h= ret.height();
    long N=w*h;
    int hist[256]={0},map[256];
    for(int i=0;i<w;++i)
        for(int j=0;j<h;j++)
            hist[qGray(img.pixel(i,j))]++;
    //calculate map function
    comulateHist(hist,map,N);
    for( int i=0; i<w;++i)
    {
        for(int j=0;j<h;++j)
        {
           int res=map[qGray(ret.pixel(i,j))];
            ret.setPixel(i,j,qRgb(res,res,res));
        }
    }
    return ret;
}
void imageprocessor::comulateHist(int *hist,int *map, double N)
{
    double sum=0;
    for(int i=0;i<256;i++)
    {
        sum+=hist[i];
        map[i]=round(255*sum/N);//四舍五入
    }
}
QImage imageprocessor::colorHisteq(const QImage &img)
{
    QImage ret(img);
    int w =ret.width();
    int h= ret.height();
    long N=w*h;
    int rhist[256]={0},rmap[256];
    int ghist[256]={0},gmap[256];
    int bhist[256]={0},bmap[256];
    for(int i=0;i<w;++i)
        for(int j=0;j<h;j++)
              rhist[qRed(img.pixel(i,j))]++;
    for(int i=0;i<w;++i)
        for(int j=0;j<h;j++)
              ghist[qGreen(img.pixel(i,j))]++;
    for(int i=0;i<w;++i)
        for(int j=0;j<h;j++)
              bhist[qBlue(img.pixel(i,j))]++;
    comulateHist(rhist,rmap,N);
    comulateHist(ghist,gmap,N);
    comulateHist(bhist,bmap,N);
    for( int i=0; i<w;++i)
    {
        for(int j=0;j<h;++j)
        {
            int r=rmap[qRed(ret.pixel(i,j))];
            int g=gmap[qGreen(ret.pixel(i,j))];
            int b=bmap[qBlue(ret.pixel(i,j))];
            ret.setPixel(i,j,qRgb(r,g,b));
        }
    }
    return ret;
}
QImage imageprocessor::colorHisteq1(const QImage & img)
{
    QImage ret(img);
    int w =ret.width();
    int h= ret.height();
    long N=w*h;
    //RGB 2 HSI
    HSI* Hsi=new HSI[N];
    for(int i=0;i<w;i++)
        for(int j=0;j<h;j++)
        {
            QRgb rgb=ret.pixel(i,j);
            Hsi[i*h+j]=HSI();
            Hsi[i*h+j]=rgb2hsi(rgb);
            //qDebug()<<"I = "<<Hsi[i*h+j].I;
        }
    int hist[256]={0};
    for(int i=0;i<N;++i)
        hist[int(Hsi[i].I*255)]++;


    int map[256] = {0};
    comulateHist(hist,map,N);

    for(int i=0;i<N;++i)
        Hsi[i].I= map[int(Hsi[i].I*255)]/255.;

    for(int i=0;i<w;i++)
        for(int j=0;j<h;j++)
        {
            QRgb rgb;
            rgb = hsi2rgb(Hsi[i*h+j]);
            ret.setPixel(i,j,rgb);
        }
    delete Hsi;
    return ret;
}
double imageprocessor::min(double var_R, double var_G, double var_B)
{
    double minimun=var_R;
    if(minimun>var_G)   minimun=var_G;
    if(minimun>var_B)   minimun=var_B;
    return minimun;
}
double imageprocessor::max(double var_R, double var_G, double var_B)
{
    double maximun=var_R;
    if(maximun<var_G)   maximun=var_G;
    if(maximun<var_B)   maximun=var_B;
    return maximun;
}
HSI imageprocessor::rgb2hsi(QRgb rgb)
{
    int R=qRed(rgb);
    int G=qGreen(rgb);
    int B=qBlue(rgb);
    double var_R = ( R / 255. );
    double var_G = ( G / 255. );
    double var_B = ( B / 255. );

    double var_Min = min( var_R, var_G, var_B ) ;   //Min. value of RGB
    double var_Max = max( var_R, var_G, var_B )  ;  //Max. value of RGB
    double del_Max = var_Max - var_Min;     //Delta RGB value
    double  del_R;
    double del_G;
    double del_B;
    double H,S,I;
    I = ( var_Max + var_Min )/ 2.;
    //qDebug()<<"I= "<<I;

    if ( del_Max == 0 )                     //This is a gray, no chroma...
    {
        H = 0;
        S= 0;
    }
    else                                    //Chromatic data...
    {
       if ( I < 0.5 )
           S = del_Max / ( var_Max + var_Min );
       else
           S = del_Max / ( 2. - var_Max - var_Min );

       del_R = ( ( ( var_Max - var_R ) / 6. ) + ( del_Max / 2. ) ) / del_Max;
       del_G = ( ( ( var_Max - var_G ) / 6. ) + ( del_Max / 2. ) ) / del_Max;
       del_B = ( ( ( var_Max - var_B ) / 6. ) + ( del_Max / 2. ) ) / del_Max;

       if      ( var_R == var_Max )
           H = del_B - del_G;
       else if ( var_G == var_Max )
           H = ( 1. / 3. ) + del_R - del_B;
       else if ( var_B == var_Max )
           H = ( 2. / 3. ) + del_G - del_R;
        if ( H < 0 )     H += 1;
        if ( H > 1 )    H -= 1;
    }

    HSI temp;
    temp.H=H;
    temp.S=S;
    temp.I=I;
    return temp;

}
QRgb imageprocessor::hsi2rgb( HSI & hsi)
{
    double L=hsi.I;
    double S=hsi.S;
    double H=hsi.H;
    double var_1;
    double var_2;
    int R,G,B;
    if ( S == 0 )
    {
          R = L * 255;
          G = L * 255;
          B = L * 255;
    }
    else
    {
       if ( L < 0.5 )
           var_2 = L * ( 1 + S );
       else
           var_2 = ( L + S ) - ( S * L );
       var_1 = 2 * L - var_2;
       R = 255 * Hue_2_RGB( var_1, var_2, H + ( 1 / 3. ) );
       G = 255 * Hue_2_RGB( var_1, var_2, H );
       B = 255 * Hue_2_RGB( var_1, var_2, H - ( 1 / 3. ) );
    }
    QRgb rgb=qRgb(R,G,B);
    return rgb;
}
double imageprocessor:: Hue_2_RGB( double v1, double v2, double vH )             //Function Hue_2_RGB
{
   if ( vH < 0 )     vH += 1;
   if( vH > 1 )      vH -= 1;
   if ( ( 6 * vH ) < 1 ) return ( v1 + ( v2 - v1 ) * 6 * vH );
   if ( ( 2 * vH ) < 1 ) return ( v2 );
   if ( ( 3 * vH ) < 2 ) return ( v1 + ( v2 - v1 ) * ( ( 2. / 3. ) - vH ) * 6 );
   return ( v1 );
}
//spatial
//线性滤波
QImage imageprocessor::LinearFilter(const QImage &img,std::vector<double>& kernel,int &nCol,QString pattern)
{
    kernelNormalization(kernel);
    int nRow=kernel.size()/nCol;
    if(0==nRow%2||0==nCol%2)    return img;
    qDebug()<<"padding";
    QImage padded=zeroPadding(img,nCol,nRow);//no errors
    qDebug()<<"filter";
    QImage filtered=filter(padded,kernel,nCol,nRow,pattern);//no errors
    qDebug()<<"crop";
    QImage cropped=crop(filtered,nCol,nRow);//no errors
    return cropped;
}
//补零
QImage imageprocessor::zeroPadding(const QImage & img, int nCol, int nRow)
{
    QImage ret(img.width()+nCol-1,img.height()+nRow-1,img.format());
    int width=ret.width();
    int height=ret.height();
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            if(i<nCol/2||i>=width-nCol/2||j<nRow/2||j>=height-nRow/2)
                ret.setPixel(i,j,qRgb(0,0,0));
            else
                ret.setPixel(i,j,img.pixel(i-nCol/2,j-nRow/2));
        }
    }
    return ret;
}
//正经滤波
QImage imageprocessor::filter(const QImage& img,std::vector<double>& kernel,int nCol,int nRow,QString pattern)
{
 //确定循环位置
    QImage ret(img);
    int width=img.width();
    int height=img.height();
   // for(int p=0;p<kernel.size();p++)
        //qDebug()<<"filter:"<<kernel[p];
    if(pattern=="RGB"){
        for(int i=nCol/2;i<width-nCol/2;++i)
        {
            for(int j=nRow/2;j<height-nRow/2;++j)
                {
                    std::vector<int> patchR=getPatch(img,i,j,nCol,nRow,'r');
                    std::vector<int> patchG=getPatch(img,i,j,nCol,nRow,'g');
                    std::vector<int> patchB=getPatch(img,i,j,nCol,nRow,'b');
                    //gai cheng pai xu qu zhongzhi//pengzhang zuida fushi zuixiao
                    double sumR=0,sumG=0,sumB=0;
                    for(int k=0;k<kernel.size();++k)
                    {
                        sumR +=kernel[k]*patchR[k];
                        sumG +=kernel[k]*patchG[k];
                        sumB +=kernel[k]*patchB[k];
                    }
                    int r =(int)sumR;
                    int g =(int)sumG;
                    int b =(int)sumB;
                    if(r>255)  r=255;
                    if(g>255)  g=255;
                    if(b>255)  b=255;
                    if(r<0)  r=0;
                    if(g<0)  g=0;
                    if(b<0)  b=0;
                    ret.setPixel(i,j,qRgb(r,g,b));
            }
        }
    }
    else if(pattern=="Gray") {
        for(int i=nCol/2;i<width-nCol/2;++i)
        {
            for(int j=nRow/2;j<height-nRow/2;++j)
                {
                    std::vector<int>patchG=getPatch(img,i,j,nCol,nRow,'y');
                    double sumG=0;
                    for(int k=0;k<kernel.size();k++)
                        sumG +=kernel[k]*patchG[k];
                    int gray=(int)sumG;
                    if(gray>255)   gray=255;
                    if(gray<0)     gray=0;
                   ret.setPixel(i,j,qRgb(gray,gray,gray));
            }
        }

    }

    return ret;
}
//图像复制
QImage imageprocessor::crop(const QImage & img, int nCol, int nRow)
{
    QImage ret(img.width()-nCol+1,img.height()-nRow+1,img.format());
    int width=ret.width();
    int height=ret.height();
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            ret.setPixel(i,j,img.pixel(i+nCol/2,j+nRow/2));
        }
    }
    return ret;
}
//提取每一块
std::vector<int> imageprocessor::getPatch(const QImage &img,int w,int h,int nCol,int nRow,char c)
{
    std:: vector<int> ret;
    for(int i=w-nCol/2;i<=w+nCol/2;++i)
    {
        for(int j=h-nRow/2;j<=h+nRow/2;++j)
        {
            switch(c) {
            case 'r':
                ret.push_back(qRed(img.pixel(i,j)));
                break;
            case 'g':
                ret.push_back(qGreen(img.pixel(i,j)));
                break;
            case 'b':
                ret.push_back(qBlue(img.pixel(i,j)));
                break;
            case 'y':
                ret.push_back(qGray(img.pixel(i,j)));
                break;
            default:
                break;
            }
        }
    }
    return ret;
}
//为了防止越界太大，所以对矩阵做归一化
void imageprocessor::kernelNormalization(std::vector<double> &kernel)
{
    double sum=0;
    for(int i=0;i<kernel.size();++i)
        sum+=kernel[i];
    if(0!=sum)
    {
        for(int i=0; i<kernel.size(); ++i){
            kernel[i]/=sum;
            //qDebug()<<kernel[i];
        }
    }
}
//中值滤波
QImage imageprocessor::MedianFilter(const QImage &img, int size,QString filterpattern,QString pattern)
{
    qDebug()<<"padding";
    QImage padded=zeroPadding(img,size,size);//no errors
    qDebug()<<"filter";
    QImage filtered=NonLinearFilter(padded,size,filterpattern,pattern);//no errors
    qDebug()<<"crop";
    QImage cropped=crop(filtered,size,size);//no errors
    return cropped;
}
QImage imageprocessor::ExpandFilter(const QImage &img, int size,QString filterpattern,QString pattern)
{
    qDebug()<<"expand";
    qDebug()<<"padding";
    QImage padded=zeroPadding(img,size,size);//no errors
    qDebug()<<"filter";
    QImage filtered=NonLinearFilter(padded,size,filterpattern,pattern);//no errors
    qDebug()<<"crop";
    QImage cropped=crop(filtered,size,size);//no errors
    return cropped;
}
QImage imageprocessor::CorrosionFilter(const QImage &img, int size,QString filterpattern,QString pattern)
{
    qDebug()<<"corrosion";
    qDebug()<<"padding";
    QImage padded=zeroPadding(img,size,size);//no errors
    qDebug()<<"filter";
    QImage filtered=NonLinearFilter(padded,size,filterpattern,pattern);//no errors
    qDebug()<<"crop";
    QImage cropped=crop(filtered,size,size);//no errors
    return cropped;
}
//非线性滤波过程
QImage imageprocessor::NonLinearFilter(const QImage &img, int size, QString filterpattern, QString pattern)
{
    QImage ret(img);
    int width=img.width();
    int height=img.height();
    int nRow=size;
    int nCol=size;
    if(pattern=="Gray")
    {
        qDebug()<<"enter gray";
        for(int i=nCol/2;i<width-nCol/2;++i)
        {
            for(int j=nRow/2;j<height-nRow/2;++j)
                {
                    std::vector<int>patchG=getPatch(img,i,j,nCol,nRow,'y');
                    std::sort(patchG.begin(),patchG.end());// order lowest
                    int gray;
                    if(filterpattern=="median"){
                        gray=patchG[patchG.size()/2];// median element
                    }else if(filterpattern=="expand"){
                        gray=patchG[patchG.size()-1];//max
                    }else if(filterpattern=="corrosion"){
                        gray=patchG[0];//min
                    }
                    ret.setPixel(i,j,qRgb(gray,gray,gray));
            }
        }
        return ret;
    }else if(pattern=="RGB"){
        for(int i=nCol/2;i<width-nCol/2;++i)
        {
            for(int j=nRow/2;j<height-nRow/2;++j)
                {
                    std::vector<int> patchR=getPatch(img,i,j,nCol,nRow,'r');
                    std::vector<int> patchG=getPatch(img,i,j,nCol,nRow,'g');
                    std::vector<int> patchB=getPatch(img,i,j,nCol,nRow,'b');
                    std::sort(patchR.begin(),patchR.end());// order lowest
                    std::sort(patchG.begin(),patchG.end());// order lowest
                    std::sort(patchB.begin(),patchB.end());// order lowest
                    int R,G,B;
                    if(filterpattern=="median"){
                        R=patchR[patchR.size()/2];// median element
                        G=patchG[patchG.size()/2];// median element
                        B=patchB[patchB.size()/2];// median element
                    }else if(filterpattern=="expand"){
                         R=patchR[patchR.size()-1];//max
                         G=patchG[patchG.size()-1];//max
                         B=patchB[patchB.size()-1];//max
                    }else if(filterpattern=="corrosion"){
                         R=patchR[0];//min
                         G=patchG[0];//min
                         B=patchB[0];//min
                    }
                    ret.setPixel(i,j,qRgb(R,G,B));
            }
        }
        return ret;
    }
}
//高斯滤波
QImage imageprocessor::GaussBlur(const QImage & img, int size, double sigma,QString pattern)
{
    qDebug()<<"1";
    std::vector<double> kernel=createGaussKernel(size,sigma);
    qDebug()<<"2";
    kernelNormalization(kernel);
    qDebug()<<"3";
    return LinearFilter(img,kernel,size,pattern);
}

QImage imageprocessor::BilaterialFilter(const QImage & img, int size, double sigmaColor, double sigmaSpace)
{
    //padding
    QImage padded=zeroPadding(img,size,size);
    //pre-calculate
    std::vector<double>kernelSpace=createGaussKernel(size,sigmaSpace);
    std::vector<double>kernelColor=creatBilateralKernel(sigmaColor);
    //filter
    QImage filtered(padded);
    int width=padded.width();
    int height=padded.height();
    for(int i=size/2;i<width-size/2;i++)
    {
        for(int j=size/2;j<height-size/2;j++)
        {

            std::vector<int>patch=getPatch(padded,i,j,size,size,'y');
            std::vector<double>kernel;
            for(int k=0;k<kernelSpace.size();k++)
            {
                int delta=abs(patch[k]-qGray(padded.pixel(i,j)));//patch[k]获取该k点的灰度值
                kernel.push_back(kernelColor[delta]*kernelSpace[k]);
            }
            kernelNormalization(kernel);
            double sum=0;
            for(int k=0;k<kernelSpace.size();k++)
            {
                sum+=kernel[k]*patch[k];
            }
            int y=(int)sum;
            if(y>255) y=255;
            filtered.setPixel(i,j,qRgb(y,y,y));
        }
    }
    //crop
    QImage cropped= crop(filtered,size,size);
    return cropped;
}
//算出所有可能的灰度值差点的e指数衰减的值
std::vector<double> imageprocessor::creatBilateralKernel(double sigmaColor)
{
    std::vector<double> ret;
    for(int i=0;i<256;i++)
    {
        double a =(-1)*(i*i)/(2*sigmaColor*sigmaColor);
        double b=exp(a);
        ret.push_back(b);
    }
    return ret;
}
//创建高斯矩阵
std::vector<double> imageprocessor::createGaussKernel(int size, double sigma)
{
    qDebug()<<"enter_create";
    std::vector<double> ret;
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            int deltaX=abs(i-size/2);
            int deltaY=abs(j-size/2);
            ret.push_back(exp((-deltaX*deltaX-deltaY*deltaY)/(2*sigma*sigma)));
        }
    }
    return ret;
}
QImage imageprocessor::rotation(const QImage &img, Matrix<double> matrix){
    bool is_inverted;
    Matrix<double>inverse = Matrix<double>::inverseMatrix(matrix,&is_inverted);//传&，因为可以修改is_inverted值
    if(!is_inverted){
        return img;
    }
    //计算新的区域
    int oldvertex[4][2]={{0,0},{img.width(),0},{0,img.height()},{img.width(),img.height()}};
    int newvertex[4][2];
    Matrix<int>::map(matrix,oldvertex[0][0],oldvertex[0][1],&newvertex[0][0],&newvertex[0][1]);
    Matrix<int>::map(matrix,oldvertex[1][0],oldvertex[1][1],&newvertex[1][0],&newvertex[1][1]);
    Matrix<int>::map(matrix,oldvertex[2][0],oldvertex[2][1],&newvertex[2][0],&newvertex[3][1]);
    Matrix<int>::map(matrix,oldvertex[3][0],oldvertex[3][1],&newvertex[3][0],&newvertex[3][1]);
    int X_max=max(newvertex[0][0],newvertex[1][0],newvertex[2][0],newvertex[3][0]);
    int X_min=min(newvertex[0][0],newvertex[1][0],newvertex[2][0],newvertex[3][0]);
    int Y_max=max(newvertex[0][1],newvertex[1][1],newvertex[2][1],newvertex[3][1]);
    int Y_min=min(newvertex[0][1],newvertex[1][1],newvertex[2][1],newvertex[3][1]);
    int width=X_max-X_min;
    int height=Y_max-Y_min;
    //map
    qDebug()<<"map image";
    QImage ret(width,height, QImage::Format_RGB32);
    int deltax=newvertex[0][0]-X_min;
    int deltay=newvertex[0][1]-Y_min;
    //find pixel
    for(int i = -deltax ; i < ret.width()-deltax; i++){
        for(int j = -deltay; j < ret.height()-deltay; j++){
            double x, y;
            //传&，可以直接修改新矩阵的值
            Matrix<double>::map(inverse, i, j, &x, &y);
            //qDebug()<<"start bilinearInterpolation";
            if(x >= 0 && x < img.width() - 1 && y >= 0 && y < img.height() - 1){
                ret.setPixel(i + deltax, j + deltay, imageprocessor::bilinearInterpolation(x,y,img));
            }else{
                ret.setPixel(i + deltax, j + deltay, qRgb(0, 0, 0));
            }
        }
    }

    return ret;
}
QRgb imageprocessor::bilinearInterpolation(double x, double y, const QImage &img)
{

    int r = 0, g = 0, b = 0;

    // four integer point near (x, y)
    QRgb rgb11 = img.pixel((int)x, (int)y);
    QRgb rgb12 = img.pixel((int)x+1, (int)y);
    QRgb rgb21 = img.pixel((int)x, (int)y+1);
    QRgb rgb22 = img.pixel((int)x+1, (int)y+1);
    r = ((1 - x + (int)x) * qRed(rgb21) + (x - (int)x) * qRed(rgb22)) * (1 - y + (int)y) + ((1 - x + (int)x) * qRed(rgb11) + (x - (int)x) * qRed(rgb12)) * (y -(int)y);
    g = ((1 - x + (int)x) * qGreen(rgb21) + (x - (int)x) * qGreen(rgb22)) * (1 - y + (int)y) + ((1 - x + (int)x) * qGreen(rgb11) + (x - (int)x) * qGreen(rgb12)) * (y -(int)y);
    b = ((1 - x + (int)x) * qBlue(rgb21) + (x - (int)x) * qBlue(rgb22)) * (1 - y + (int)y) + ((1 - x + (int)x) * qBlue(rgb11) + (x - (int)x) * qBlue(rgb12)) * (y -(int)y);
    return QRgb(qRgb(r, g, b));
}
int imageprocessor::max(int a, int b, int c, int d)
{
    int max=a;
    if(b>max)   max=b;
    if(c>max)   max=c;
    if(d>max)   max=d;
    return max;
}
int imageprocessor::min(int a, int b, int c, int d)
{
    int min=a;
    if(b<min)   min=b;
    if(c<min)   min=c;
    if(d<min)   min=d;
    return min;
}
