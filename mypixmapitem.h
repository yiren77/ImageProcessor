
#ifndef MYPIXMAPITEM_H
#define MYPIXMAPITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>

class Mypixmapitem : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Mypixmapitem(QGraphicsPixmapItem *parent =0);
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void wheelEvent(QGraphicsSceneWheelEvent*);
    void reset();
private:
    double Rate;

signals:

public slots:
};

#endif // MYPIXMAPITEM_H

