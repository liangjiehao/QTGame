#ifndef ANIMATIONPIXMAP_H
#define ANIMATIONPIXMAP_H

#include <QPointF>
#include <QObject>
#include <QPixmap>
#include <QPushButton>
#include <QRectF>
#include <QSize>

class animationPixmap : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QRectF geo READ geo WRITE setGeo)
    Q_PROPERTY(QSize zoom READ zoom WRITE setZoom)
public:
    animationPixmap() : QPushButton(){};
    animationPixmap(const animationPixmap &m) : QPushButton() { animatedMap = m.animatedMap; };
    void operator=(const animationPixmap &m) { animatedMap = m.animatedMap; };

    QRectF geo() const { return _pos; };
    void setGeo(QRectF writePos)
    {
        _pos = writePos;
        move(_pos.x(), _pos.y());
        setIconSize(QSize(_pos.width(), _pos.height()));
    };
    QSize zoom() const { return _zoom; };
    void setZoom(QSize writeZoom)
    {
        _zoom = writeZoom;
        move(300, 300);
        setIconSize(_zoom);
    }

private:
    QIcon animatedMap;
    QRectF _pos;
    QSize _zoom;
};

#endif // ANIMATIONPIXMAP_H
