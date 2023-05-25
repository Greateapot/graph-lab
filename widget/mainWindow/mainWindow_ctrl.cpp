#include "mainWindow.h"
#include "ui_mainWindow.h"

#include "utils/utils.h"

void MainWindow::unselectAll()
{
    // clear all
    for (auto i : cities)
        i->is_selected = 0;
    for (auto i : roads)
        i->is_selected = 0;
}

void MainWindow::select(QGraphicsItem *item)
{
    if (!solving)
        unvisitAll();
    unselectAll();
    CityModel *city = dynamic_cast<CityModel *>(item);
    if (city != nullptr)
    {
        city->is_selected = true;
        for (auto i : roads)
            i->is_selected = (*i->A == *city || *i->B == *city);
    }
}

void MainWindow::unvisitAll()
{
    for (auto i : cities)
        i->is_visited = 0;
}

void MainWindow::visit(CityModel *city)
{
    ui->statusbar->showMessage("City " + city->name + " visited!");
    for (CityModel *c : cities)
        if (c == city)
        {
            c->is_visited = 1;
            break;
        }
    scene->QGraphicsScene::update();
    delay(1000);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape && scene->choosing_cities)
    {
        scene->choosing_cities = false;
        add_road_first_city = nullptr;
        ui->statusbar->clearMessage();
    }
    else if (e->key() == Qt::Key_Delete || e->key() == Qt::Key_Minus)
    {
        QGraphicsItem *item = scene->QGraphicsScene::focusItem();
        CityModel *city = dynamic_cast<CityModel *>(item);
        if (city)
        {
            for (auto i = cities.begin(); i != cities.end(); i++)
                if ((*i)->name == city->name)
                {
                    delete *i;
                    cities.erase(i);
                    break;
                }

            for (auto i = roads.begin(); i != roads.end(); i++)
                if ((*i)->A == city || (*i)->B == city)
                {
                    RoadModel *to_del = (*i);
                    *i = nullptr;
                    delete to_del;
                }

            roads.erase(std::remove(roads.begin(), roads.end(), nullptr), roads.end());
        }
    }
    else if (e->key() == Qt::Key_Plus)
        addCity();
    scene->QGraphicsScene::update();
}
