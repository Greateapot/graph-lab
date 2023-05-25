#pragma once

#include <vector>

#include <QMainWindow>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QDoubleValidator>

#include "model/city/cityModel.h"
#include "model/road/roadModel.h"
#include "widget/scene/scene.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addCity();
    void addRoad();
    void _addRoad(CityModel *);

    void unselectAll();
    void select(QGraphicsItem *);

    void unvisitAll();
    void visit(CityModel *);

    void save_to_file();
    void open_file();

    void showSolution();

    void solve_depth(size_t);

    void _solve_depth(
        CityModel *city,
        QString message,
        size_t road_length);

    void solve_width(size_t);

protected:
    void keyPressEvent(QKeyEvent *);

private:
    Ui::MainWindow *ui;
    Scene *scene;

    std::vector<CityModel *> cities;
    std::vector<RoadModel *> roads;

    CityModel *add_road_first_city = nullptr;

    bool solving = false;
};
