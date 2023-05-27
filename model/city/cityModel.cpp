#include "cityModel.h"

#include "utils/utils.h"

CityModel::CityModel(QGraphicsItem *parent)
    : QGraphicsItem(parent), name("CityModel")
{
    update();
}

CityModel::CityModel(QString name, double radius, QGraphicsItem *parent)
    : QGraphicsItem(parent), name(name), radius(radius)
{
    update();
}

CityModel::CityModel(const CityModel &c)
    : QGraphicsItem(c.parentItem()), name(c.name), radius(c.radius)
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

    { // name
        QFontMetrics fm(painter->font());
        const int tw = fm.width(name),
                  th = fm.height();
        painter->drawText(radius - tw / 2, radius - th / 4, name);
    }

    if (mark_DXTR < INF)
    { // DXTR
        QFontMetrics fm(painter->font());
        QString v = double2QString(mark_DXTR);
        const int tw = fm.width(v),
                  th = fm.height();
        painter->drawText(radius - tw / 2, radius + th, v);
    }
}
QRectF CityModel::boundingRect() const
{
    return QRectF(0, 0, radius * 2, radius * 2);
}

std::fstream &operator<<(std::fstream &fout, const CityModel &city)
{
    fout << city.name.toStdString() << DLTR
         << city.pos().x() << DLTR
         << city.pos().y() << DLTR
         << city.radius << DLTR;
    return fout;
}

std::fstream &operator>>(std::fstream &fin, CityModel &city)
{
    std::string name_raw, x_raw, y_raw, radius_raw;
    std::getline(fin, name_raw, DLTR);
    std::getline(fin, x_raw, DLTR);
    std::getline(fin, y_raw, DLTR);
    std::getline(fin, radius_raw, DLTR);

    city.name = QString::fromStdString(name_raw);
    city.moveBy(stod(x_raw), stod(y_raw));
    city.radius = stod(radius_raw);

    return fin;
}
