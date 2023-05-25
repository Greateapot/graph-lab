#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "model/city/cityModel.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Scene(QObject *parent = nullptr);

    bool choosing_cities = 0;

    void update_selected();

signals:
    void city_chosen(CityModel *);
    void item_selected(QGraphicsItem *);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;
};
