#include "roadModel.h"

#define _USE_MATH_DEFINES

#include "model/city/cityModel.h"
#include "utils/utils.h"

#include <cmath>

RoadModel::RoadModel(
    CityModel *A, CityModel *B,
    double length, QGraphicsItem *parent)
    : QGraphicsItem(parent), A(A), B(B), length(length)
{
    update();
}

RoadModel::RoadModel(const RoadModel &r)
    : QGraphicsItem(r.parentItem()),
      A(r.A), B(r.B), length(r.length)
{
    update();
}

void RoadModel::update()
{
    setFlag(QGraphicsItem::ItemIsFocusable);
}

void RoadModel::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setPen(is_selected ? Qt::cyan : Qt::blue);

    qreal Ax = A->pos().x() + A->radius,
          Ay = A->pos().y() + A->radius,
          Bx = B->pos().x() + B->radius,
          By = B->pos().y() + B->radius,
          angle = -atan(abs(By - Ay) / abs(Bx - Ax));

    // Адское сокращение if'ов
    angle = (Bx - Ax < 0)
                ? (M_PI + (By - Ay < 0 ? 1 : -1) * angle)
                : ((By - Ay < 0 ? -1 : 1) * angle);

    qreal del_x = 15 * sin(angle),
          del_y = 15 * cos(angle);

    QLineF line = QLineF(Ax - del_x, Ay - del_y, Bx - del_x, By - del_y);
    QLineF vector = line.unitVector();
    vector.setLength(20);

    QPointF point1 = vector.p2();
    vector.setLength(line.length() - 20);
    QPointF point2 = vector.p2();
    painter->drawLine(QLineF(point1, point2));
    vector.setLength(line.length() - 30);

    /* Arrow */
    QLineF arrow_left = QLineF(point2, vector.p2()),
           arrow_right = QLineF(point2, vector.p2());

    arrow_left.setAngle(arrow_left.angle() - 30);
    arrow_right.setAngle(arrow_right.angle() + 30);

    painter->drawLine(arrow_left);
    painter->drawLine(arrow_right);
    /* Arrow */

    QFontMetrics fm(painter->font());
    qreal rotate_angle = -line.angle();
    QPointF center = line.center();

    QString text = double2QString(length);
    int tw = fm.width(text);
    int th = fm.height();

    qreal text_x = center.x() * cos(M_PI * rotate_angle / 180) + center.y() * sin(M_PI * rotate_angle / 180),
          text_y = -center.x() * sin(M_PI * rotate_angle / 180) + center.y() * cos(M_PI * rotate_angle / 180);

    painter->rotate(rotate_angle);
    painter->drawText(text_x - tw / 2, text_y - th / 2, text);
    painter->rotate(-rotate_angle);
}

QRectF RoadModel::boundingRect() const
{
    return QRectF(0, 0, 30, 30);
}

bool operator==(const RoadModel &r1, const RoadModel &r2)
{
    return r1.A == r2.A && r1.B == r2.B;
}
