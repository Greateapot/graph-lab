#include "mainWindow.h"
#include "ui_mainWindow.h"

#include "dialog/addCity/addCityDialog.h"
#include "dialog/addRoad/addRoadDialog.h"

void MainWindow::addCity()
{
    AddCityDialog dialog(this);
    dialog.exec();
    if (dialog.cancel)
        return;

    QString city_name = dialog.city_name;
    if (city_name.isEmpty())
        return ui->statusbar->showMessage("Нельзя добавить город с пустым названием!", STATUS_MESSAGE_DELAY);

    CityModel *new_city = new CityModel(city_name);
    for (auto i : cities)
        if (*new_city == *i)
        {
            delete new_city;
            ui->statusbar->showMessage("Этот город уже построен, строй другой.", STATUS_MESSAGE_DELAY);
            return;
        }

    cities.push_back(new_city);
    scene->addItem(new_city);
    scene->QGraphicsScene::update();
}

void MainWindow::addRoad()
{
    _addRoad(nullptr); // Тупо обертка
}

void MainWindow::_addRoad(CityModel *city)
{
    if (add_road_first_city == nullptr && city == nullptr)
    {
        // Начало создания дороги, нет ни первого города, ни выбранного
        scene->choosing_cities = true;
        ui->statusbar->showMessage("Выберите первый город (тык по нему).", STATUS_MESSAGE_DELAY);
    }
    else if (add_road_first_city == nullptr)
    {
        // Если мы здесь, значит первый город еще не выбран, зато есть выбранный город, его и назначем первым
        add_road_first_city = city;
        ui->statusbar->showMessage("Выберите второй город (тоже тык).", STATUS_MESSAGE_DELAY);
    }
    else if (city == add_road_first_city)
    {
        // Если мы здесь, значит первый город уже выбран, а так же есть выбранный город, но это тот же город, что и первый. Шлём пользователя выбирать другой.
        ui->statusbar->showMessage("Выберите другой город!", STATUS_MESSAGE_DELAY);
    }
    else
    {
        // Если мы здесь, значит первый город уже выбран, а так же есть выбранный ДРУГОЙ город, его берем за второй город. Вызываем диалог для получения длины дороги и направления.
        AddRoadDialog dialog(this);
        dialog.exec();
        if (dialog.cancel)
            return;

        if (dialog.length == 0)
            return ui->statusbar->showMessage("Нельзя добавить дорогу длинной 0!", STATUS_MESSAGE_DELAY);

        {
            // Изоляция чтоб код повторить
            RoadModel *new_road = new RoadModel(add_road_first_city, city, dialog.length);
            for (auto i : roads)
                if (*new_road == *i)
                {
                    delete new_road;
                    ui->statusbar->showMessage("Эту дорогу уже проложили, перекладывать - дорого.", STATUS_MESSAGE_DELAY);
                    scene->QGraphicsScene::update();
                    return;
                }
            roads.push_back(new_road);
            scene->addItem(new_road);
        }
        if (dialog.is_bidirectional)
        {
            // дорога обратно
            RoadModel *new_road = new RoadModel(city, add_road_first_city, dialog.length);
            for (auto i : roads)
                if (*new_road == *i)
                {
                    delete new_road;
                    ui->statusbar->showMessage("Эту дорогу уже проложили, перекладывать - дорого.", STATUS_MESSAGE_DELAY);
                    scene->QGraphicsScene::update();
                    return;
                }
            roads.push_back(new_road);
            scene->addItem(new_road);
        }

        add_road_first_city = nullptr;
        scene->choosing_cities = false;
        scene->update_selected();
    }
    scene->QGraphicsScene::update();
}