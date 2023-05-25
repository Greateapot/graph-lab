#include "mainWindow.h"
#include "ui_mainWindow.h"

#include <queue>

#include <QMessageBox>

// dialogs
#include "dialog/solutionInput/solutionInputDialog.h"   // TODO: RN class
#include "dialog/solutionOutput/solutionOutputDialog.h" // TODO: RN class

void MainWindow::showSolution()
{
    InputDataDialog inputDialog(this);
    inputDialog.exec();

    QString city_name = inputDialog.city_name;
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
        switch (inputDialog.solution_method)
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
            break;
        }
        ui->statusbar->clearMessage();
        solving = 0;
    }
}

void MainWindow::solve_depth(size_t index)
{
    CityModel *city = cities[index];
    _solve_depth(city, city->name, 0);

    // vector<pair<string, size_t>> results;
    // string output = "";
    // for (pair<string, size_t> &p : results)
    //     output += p.first + " : " + to_string(p.second) + '\n';
    // return output;
    // std::cout << message << std::endl;
    // SolutionDialog dialog(message);
    // dialog.exec();
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
        if (!process.empty())
        {
            city = process.front();
            process.pop();
        }
        else
            city = nullptr;
    }
}
