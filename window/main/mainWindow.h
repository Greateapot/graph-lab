#pragma once

#include <vector>

#include <QMainWindow>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QDoubleValidator>

#include "model/city/cityModel.h"
#include "model/road/roadModel.h"
#include "utils/scene/scene.h"

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
    void start_addRoad();
    void continue_addRoad(CityModel *);
    void addRoad(RoadModel *);
    void select(QGraphicsItem *);
    void unselectAll();
    void save_to_file();
    void open_file();
    void showSolution();
    void solveDepth(std::size_t);
    void cb(std::string, std::size_t);

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::MainWindow *ui;
    Scene *scene;

    std::vector<CityModel *> cities;
    std::vector<RoadModel *> roads;

    CityModel *addRoadFirstCity = nullptr;
};
