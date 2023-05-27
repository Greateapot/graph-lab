#pragma once

#include <string>
#include <vector>
#include <fstream>

#include <QGraphicsItem>
#include <QPainter>

const double INF = 10E10;
const char DLTR = '\0';

class CityModel : public QGraphicsItem
{
public:
    CityModel(QGraphicsItem *parent = nullptr);
    CityModel(QString, double radius = 25, QGraphicsItem *parent = nullptr);
    CityModel(const CityModel &);

    friend bool operator==(const CityModel &, const CityModel &);
    friend std::fstream &operator>>(std::fstream &, CityModel &);
    friend std::fstream &operator<<(std::fstream &, const CityModel &);

    double radius = 25;

    QString name;

    size_t index_TSP = INF; // это поле используется один раз, можно обойтись и без него, но так проще ;)
    double mark_DXTR = INF;
    bool is_selected = 0;
    bool is_visited = 0;

private:
    void update();

protected:
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
};
