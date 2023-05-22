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
    bool isSelected = false;

    friend bool operator==(const RoadModel &, const RoadModel &);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    QString double_to_str(double);
};

