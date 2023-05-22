#include "scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    pen = new QPen(Qt::black);
    brush = new QBrush(Qt::blue);
    choosing_cities = false;
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::update();
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
    emit item_selected(QGraphicsScene::focusItem());
    if (choosing_cities)
        if (QGraphicsScene::focusItem())
        {
            QGraphicsItem *item = QGraphicsScene::focusItem();
            CityModel *c = dynamic_cast<CityModel *>(item);
            if (c)
                emit city_chosen(c);
        }
    QGraphicsScene::update();
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
    emit item_selected(QGraphicsScene::focusItem());
}

void Scene::recheck_selected()
{
    emit item_selected(QGraphicsScene::focusItem());
}
