#pragma once

#include <vector>

#include <QMainWindow>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QDoubleValidator>

#include "model/city/cityModel.h"
#include "model/road/roadModel.h"
#include "widget/scene/scene.h"

const char GDLTR = '\1';
const int STATUS_MESSAGE_DELAY = 5000;
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

    void save();
    void load();

    void build_matrix(std::vector<std::vector<double>> &);
    void reduce_matrix(std::vector<std::vector<double>> &);

    void step(std::vector<std::pair<int, int>> &, std::vector<std::vector<double>> &);

    void showSolution();

    void solve_width(size_t);

    void solve_depth(size_t);
    void _solve_depth(CityModel *, QString, size_t);

    void solve_DXTR(size_t);
    void _solve_DXTR(CityModel *);

    void solve_TSP(size_t);

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
