#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "model/city/cityModel.h"

class QGraphicsSceneMouseEvent;
class QPointF;
class QColor;

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = 0);
    bool choosing_cities;
    void recheck_selected();

signals:
    void city_chosen(CityModel *);
    void item_selected(QGraphicsItem *);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    QPen *pen;
    QBrush *brush;
};
