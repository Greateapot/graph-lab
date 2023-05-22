#pragma once

#include <string>
#include <vector>
#include <fstream>

#include <QGraphicsItem>
#include <QPainter>

class CityModel : public QGraphicsItem
{
public:
    CityModel(QGraphicsItem *parent = nullptr);
    CityModel(QString, int, int, QGraphicsItem *parent = nullptr);
    CityModel(const CityModel &);

    QString name;
    bool isSelected = false;

    static const int radius = 25;

    friend bool operator==(const CityModel &, const CityModel &);
    friend std::fstream &operator>>(std::fstream &fin, CityModel &p);
    friend std::fstream &operator<<(std::fstream &fout, const CityModel &p);

private:
    int pos_x, pos_y;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
};
