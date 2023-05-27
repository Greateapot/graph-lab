#pragma once

#include <fstream>

#include <QGraphicsItem>

#include "model/city/cityModel.h"

class RoadModel : public QGraphicsItem
{
public:
    RoadModel(CityModel *, CityModel *, double, QGraphicsItem *parent = nullptr);
    RoadModel(const RoadModel &);

    CityModel *A, *B;
    double length;
    bool is_selected = false;

    friend bool operator==(const RoadModel &, const RoadModel &);

private:
    void update();

protected:
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
};
