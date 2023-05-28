#include "mainWindow.h"
#include "ui_mainWindow.h"

#include <algorithm>
#include <queue>
#include <fstream>

#include <QMessageBox>

#include "utils/utils.h"
#include "dialog/solutionInput/solutionInputDialog.h"

void MainWindow::showSolution()
{
    SolutionInputDialog dialog(this);
    dialog.exec();

    if (dialog.cancel)
        return;

    QString city_name = dialog.city_name;
    int index = -1;

    for (int i = 0; index < 0 && i < cities.size(); i++)
        if (cities[i]->name == city_name)
            index = i;

    if (index < 0)
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Ошибка", "Нет города с таким названием!");
    }
    else
    {
        solving = 1;
        switch (dialog.solution_method)
        {
        case 0:
            // в глубину
            solve_depth(index);
            break;
        case 1:
            // в ширину
            solve_width(index);
            break;
        case 2:
            // дейкстра
            solve_DXTR(index);
            break;
        }
        solving = 0;
    }
}

void MainWindow::solve_width(size_t index)
{
    std::queue<CityModel *> process;
    CityModel *city = cities[index];

    while (city != nullptr)
    {
        visit(city);
        for (RoadModel *road : roads)
            if (road->A == city || road->B == city)
            {
                CityModel *neighbor = road->A == city ? road->B : road->A;
                if (!neighbor->is_visited)
                    process.push(neighbor);
            }
        while (!process.empty())
        {
            city = process.front();
            process.pop();
            if (!city->is_visited)
                break;
            else
                city = nullptr;
        }
    }
}

void MainWindow::solve_depth(size_t index)
{
    CityModel *city = cities[index];
    _solve_depth(city, city->name, 0);
}

void MainWindow::_solve_depth(
    CityModel *city,
    QString message,
    size_t road_length)
{
    visit(city);

    for (RoadModel *road : roads)
        if (road->A == city || road->B == city)
        {
            CityModel *neighbor = road->A == city ? road->B : road->A;
            if (!neighbor->is_visited)
                _solve_depth(
                    neighbor,
                    message + " -> " + neighbor->name,
                    road_length + road->length);
        }
}

void MainWindow::solve_DXTR(size_t index)
{
    for (CityModel *c : cities)
        c->mark_DXTR = INF;

    CityModel *city = cities[index];
    city->mark_DXTR = 0;

    _solve_DXTR(city);
}

void MainWindow::_solve_DXTR(CityModel *city)
{
    visit(city);

    CityModel *nearest_city = nullptr;
    size_t min_road_length = INF;

    for (RoadModel *road : roads)
        if (road->A == city || road->B == city)
        {
            CityModel *neighbor = road->A == city ? road->B : road->A;
            if (!neighbor->is_visited)
            {
                if (city->mark_DXTR + road->length < neighbor->mark_DXTR)
                    neighbor->mark_DXTR = city->mark_DXTR + road->length;
                if (road->length < min_road_length)
                {
                    min_road_length = road->length;
                    nearest_city = neighbor;
                }
            }
        }

    if (nearest_city != nullptr)
        _solve_DXTR(nearest_city);
}
