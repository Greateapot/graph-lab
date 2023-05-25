#include "scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent) {}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent); // super
    QGraphicsScene::update();
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent); // super
    QGraphicsScene::update();
    emit item_selected(QGraphicsScene::focusItem());
    if (!choosing_cities)
        return;

    QGraphicsItem *item = QGraphicsScene::focusItem();
    if (item)
    {
        CityModel *city = dynamic_cast<CityModel *>(item);
        if (city)
            emit city_chosen(city);
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent); // super
    QGraphicsScene::update();
    emit item_selected(QGraphicsScene::focusItem());
}

void Scene::update_selected()
{
    emit item_selected(QGraphicsScene::focusItem());
}
