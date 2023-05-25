#include "mainWindow.h"
#include "ui_mainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new Scene(ui->graphicsView);
    ui->graphicsView->setScene(scene);

    connect(ui->addButton_City, &QPushButton::released, this, &MainWindow::addCity);
    connect(ui->addButton_Road, &QPushButton::released, this, &MainWindow::addRoad);
    connect(ui->solveButton, &QPushButton::released, this, &MainWindow::showSolution);

    connect(scene, &Scene::city_chosen, this, &MainWindow::_addRoad);
    connect(scene, &Scene::item_selected, this, &MainWindow::select);

    connect(ui->actionsave, &QAction::triggered, this, &MainWindow::save_to_file);
    connect(ui->actionload, &QAction::triggered, this, &MainWindow::open_file);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete add_road_first_city;
}
