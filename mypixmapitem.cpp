
#include "mypixmapitem.h"
#include "QDebug"
Mypixmapitem::Mypixmapitem(QGraphicsPixmapItem *parent) : QGraphicsPixmapItem(parent),Rate(0.1)
{

}
//点击鼠标
void Mypixmapitem::mousePressEvent(QGraphicsSceneMouseEvent*event)
{
    qDebug()<<"press";
}
//拖拽
void Mypixmapitem::mouseMoveEvent(QGraphicsSceneMouseEvent*event)
{
    qDebug()<<"move";
    setPos(pos()+
           mapToParent(event->pos())-
           mapToParent(event->lastPos()));//重置位置：利用向量，过去的向量加移动了多少的向量。移动了多少，现在的向量减过去的向量
}
//滚动缩放
void Mypixmapitem::wheelEvent(QGraphicsSceneWheelEvent*event)
{
    qDebug()<<"wheel";
    int delta=event->delta();
    double factor=scale();
    //放大
    if(delta>0)
    {
        factor *=(1+Rate);
    }
    //缩小
    if(delta<0)
    {
        factor *=(1-Rate);
    }
    //以图像中心缩放
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(factor);
}
void Mypixmapitem::reset()
{
    setPos(0,0);
    setScale(1.0);
}
