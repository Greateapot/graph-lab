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
    CityModel(QString, double x = 0, double y = 0, double radius = 25, QGraphicsItem *parent = nullptr);
    CityModel(const CityModel &);

    friend bool operator==(const CityModel &, const CityModel &);
    friend std::fstream &operator>>(std::fstream &fin, CityModel &p);
    friend std::fstream &operator<<(std::fstream &fout, const CityModel &p);

    double pos_x = 0;
    double pos_y = 0;
    double radius = 25;

    QString name;
    std::size_t mark_DXTR = 10E10; // 100 млрд по умолчанию
    bool is_selected = 0;
    bool is_visited = 0;

private:
    void update();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
};
