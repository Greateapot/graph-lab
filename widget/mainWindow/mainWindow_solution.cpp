#include "mainWindow.h"
#include "ui_mainWindow.h"

#include <algorithm>
#include <queue>
#include <fstream>

#include <QMessageBox>

#include "utils/utils.h"

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
            solve_DXTR(index);
            break;
        case 3:
            // TSP
            solve_TSP(index);
            break;
        }
        ui->statusbar->clearMessage();
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

void MainWindow::build_matrix(std::vector<std::vector<double>> &matrix)
{

    for (int i = 0; i < cities.size(); i++)
    {
        cities[i]->index_TSP = i;
        for (int j = 0; j < cities.size(); j++)
            matrix[i][j] = -1;
    }

    for (auto road : roads)
        matrix[road->A->index_TSP][road->B->index_TSP] = road->length;

    matrix.emplace_back();
    for (int i = 0; i < matrix.size() - 1; ++i)
    {
        matrix[i].emplace_back();
        matrix[matrix.size() - 1].emplace_back();
    }
    matrix[matrix.size() - 1].push_back(-1);
}

void MainWindow::reduce_matrix(std::vector<std::vector<double>> &matrix)
{
    // Стоблцы
    for (int i = 0; i < matrix.size() - 1; ++i)
    {
        double min = INF;
        for (int j = 0; j < matrix.size() - 1; ++j)
            if (matrix[i][j] != -1 && matrix[i][j] < min)
                min = matrix[i][j];
        matrix[i][matrix.size() - 1] = min;
    }

    for (int i = 0; i < matrix.size() - 1; ++i)
        for (int j = 0; j < matrix.size() - 1; ++j)
            if (matrix[i][j] != -1)
                matrix[i][j] -= matrix[i][matrix.size() - 1];

    // Строки
    for (int i = 0; i < matrix.size() - 1; ++i)
    {
        double min = INF;
        for (int j = 0; j < matrix.size() - 1; ++j)
            if (matrix[j][i] != -1 && matrix[j][i] < min)
                min = matrix[j][i];
        matrix[matrix.size() - 1][i] = min;
    }

    for (int i = 0; i < matrix.size() - 1; ++i)
        for (int j = 0; j < matrix.size() - 1; ++j)
            if (matrix[j][i] != -1)
                matrix[j][i] -= matrix[matrix.size() - 1][i];
}

void MainWindow::step(
    std::vector<std::pair<int, int>> &steps,
    std::vector<std::vector<double>> &matrix)
{
    std::pair<int, int> step;
    double max_sum = -1;
    for (int i = 0; i < matrix.size() - 1; i++)
        for (int j = 0; j < matrix.size() - 1; j++)
            if (matrix[i][j] == 0)
            {
                double min_row = INF, min_column = INF;
                for (int k = 0; k < matrix.size() - 1; k++)
                {
                    if (matrix[i][k] != -1 && k != j && matrix[i][k] < min_row)
                        min_row = matrix[i][k];
                    if (matrix[k][j] != -1 && k != i && matrix[k][j] < min_column)
                        min_column = matrix[k][j];
                }

                if (min_row + min_column > max_sum)
                {
                    step.first = i;
                    step.second = j;
                    max_sum = min_row + min_column;
                }
            }

    for (int i = 0; i < matrix.size() - 1; ++i)
    {
        matrix[step.first][i] = -1;
        matrix[i][step.second] = -1;
    }
    matrix[step.first][step.second] = -1;
    matrix[step.second][step.first] = -1;
    steps.push_back(step);
}

void MainWindow::solve_TSP(size_t index)
{
    std::vector<std::pair<int, int>> steps;
    std::vector<std::vector<double>> matrix(cities.size(), std::vector<double>(cities.size()));
    build_matrix(matrix);

    while (steps.size() < cities.size())
    {
        reduce_matrix(matrix);
        step(steps, matrix);
    }

    if (steps.back().first == steps.back().second) // Если что-то пойдет не так, последний ход всегда == pair(0,0)
        return ui->statusbar->showMessage("Невозможно решить");

    visit(cities[index]);

    for (int i = 0; i < matrix.size() - 1; i++)
        for (int j = 0; j < matrix.size() - 1; j++)
            if (steps[j].first == index)
            {
                index = steps[j].second;
                visit(cities[index]);
                delay(1000);
                break;
            }
}
