#include "cityModel.h"

CityModel::CityModel(QGraphicsItem *parent)
    : QGraphicsItem(parent), name("CityModel")
{
    update();
}

CityModel::CityModel(
    QString name, double x, double y,
    double radius, QGraphicsItem *parent)
    : QGraphicsItem(parent),
      name(name), pos_x(x),
      pos_y(y), radius(radius)
{
    update();
}

CityModel::CityModel(const CityModel &c)
    : QGraphicsItem(c.parentItem()), name(c.name),
      pos_x(c.pos_x), pos_y(c.pos_y), radius(c.radius)
{
    update();
}

bool operator==(const CityModel &c1, const CityModel &c2)
{
    return c1.name == c2.name;
}

void CityModel::update()
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void CityModel::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setPen(is_visited ? Qt::green : (is_selected ? Qt::cyan : Qt::blue));

    painter->drawEllipse(boundingRect());

    QFontMetrics fm(painter->font());
    const int tw = fm.width(name),
              th = fm.height();
    painter->drawText(radius - tw / 2, radius + th / 2, name);
}
QRectF CityModel::boundingRect() const
{
    return QRectF(pos_x, pos_y, radius * 2, radius * 2);
}

// TODO: RW
std::fstream &operator<<(std::fstream &fout, const CityModel &c)
{
    fout << '\n'
         << c.name.toStdString() << '\n'
         << c.pos().x() << '\n'
         << c.pos().y() << '\n';
    return fout;
}

// TODO: RW
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
