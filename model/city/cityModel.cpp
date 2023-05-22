#include "cityModel.h"

CityModel::CityModel(QGraphicsItem *parent) : QGraphicsItem(parent), name("CityModel"), pos_x(0), pos_y(0)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

CityModel::CityModel(QString name, int x, int y, QGraphicsItem *parent) : QGraphicsItem(parent), name(name), pos_x(x), pos_y(y)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

CityModel::CityModel(const CityModel &c)
{
    name = c.name;
    pos_x = c.pos_x;
    pos_y = c.pos_y;
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

QRectF CityModel::boundingRect() const
{
    return QRectF(pos_x, pos_y, radius * 2, radius * 2);
}

void CityModel::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setPen(isSelected ? Qt::cyan : Qt::blue);
    painter->drawEllipse(0, 0, radius * 2, radius * 2);
    QFontMetrics fm(painter->font());
    const int tw = fm.width(name), th = fm.height();
    painter->drawText(radius - tw / 2, radius + th / 2, name);
}

bool operator==(const CityModel &c1, const CityModel &c2)
{
    return c1.name == c2.name;
}

std::fstream &operator<<(std::fstream &fout, const CityModel &c)
{
    fout << '\n'
         << c.name.toStdString() << '\n'
         << c.pos().x() << '\n'
         << c.pos().y() << '\n';
    return fout;
}

std::fstream &operator>>(std::fstream &fin, CityModel &c)
{
    std::string name;
    fin >> name;
    c.name = QString::fromStdString(name);
    int x, y;
    fin >> x;
    fin >> y;
    c.moveBy(x, y);
    return fin;
}
