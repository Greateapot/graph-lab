#include "mainWindow.h"
#include "ui_mainWindow.h"

#include <algorithm>
#include <fstream>
#include <iostream>

#include <QThread>
#include <QMessageBox>
#include <QFileDialog>

#include "utils/graph/graph.h" // TODO: RW for Qt (QString, template<T = double>)

// dialogs
#include "dialog/addCity/addCityDialog.h"
#include "dialog/addRoad/addRoadDialog.h"
#include "dialog/solutionInput/solutionInputDialog.h" // TODO: RN class
#include "dialog/solutionOutput/solutionOutputDialog.h" // TODO: RN class

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new Scene(ui->graphicsView);
    ui->graphicsView->setScene(scene);

    connect(ui->addButton_City, &QPushButton::released, this, &MainWindow::addCity);
    connect(ui->addButton_Road, &QPushButton::released, this, &MainWindow::start_addRoad);
    connect(ui->solveButton, &QPushButton::released, this, &MainWindow::showSolution);

    connect(scene, &Scene::city_chosen, this, &MainWindow::continue_addRoad);
    connect(scene, &Scene::item_selected, this, &MainWindow::select);

    connect(ui->actionsave, &QAction::triggered, this, &MainWindow::save_to_file);
    connect(ui->actionload, &QAction::triggered, this, &MainWindow::open_file);
}

void MainWindow::addCity()
{
    AddCityDialog dialog(this);
    dialog.exec();
    QString value = dialog.getValue();
    if (value.isEmpty())
        return; // TODO: message

    CityModel *new_city = new CityModel(value, 0, 0);
    for (auto i : cities)
        if (*new_city == *i)
        {
            delete new_city;
            ui->statusbar->showMessage("Этот город уже построен, строй другой.");
            return;
        }

    cities.push_back(new_city);
    scene->addItem(new_city);
    scene->QGraphicsScene::update();
}

void MainWindow::start_addRoad()
{
    scene->choosing_cities = true;
    ui->statusbar->showMessage("Выберите первый город (тык по нему).");
    scene->QGraphicsScene::update();
}

void MainWindow::continue_addRoad(CityModel *c)
{
    if (addRoadFirstCity == nullptr)
    {
        addRoadFirstCity = c;
        ui->statusbar->showMessage("Выберите второй город (тоже тык).");
        scene->QGraphicsScene::update();
    }
    else if (c == addRoadFirstCity)
        scene->QGraphicsScene::update();
    else
    {
        AddRoadDialog dialog(this);
        dialog.exec();
        bool isBidirectional = dialog.getIsBidirectional();
        double value = dialog.getValue();
        if (value == 0)
            return; // TODO: message

        addRoad(new RoadModel(addRoadFirstCity, c, value));
        if (isBidirectional) // дорога обратно
            addRoad(new RoadModel(c, addRoadFirstCity, value));

        scene->choosing_cities = false;
        ui->statusbar->clearMessage();
        scene->QGraphicsScene::update();
        addRoadFirstCity = nullptr;
        scene->recheck_selected();
    }
}

void MainWindow::addRoad(RoadModel *new_road)
{
    for (auto i : roads)
        if (*new_road == *i)
        {
            delete new_road;
            ui->statusbar->showMessage("Эту дорогу уже проложили, перекладывать - дорого.");
            scene->QGraphicsScene::update();
            return;
        }

    roads.push_back(new_road);
    scene->addItem(new_road);
}

void MainWindow::unselectAll()
{
    // clear all
    for (auto i : cities)
        i->isSelected = false;
    for (auto i : roads)
        i->isSelected = false;
}

void MainWindow::select(QGraphicsItem *item)
{
    unselectAll();
    CityModel *c = dynamic_cast<CityModel *>(item);
    if (c != nullptr)
    {
        c->isSelected = true;
        for (auto i : roads)
            i->isSelected = (*i->A == *c || *i->B == *c);
    }
}

void MainWindow::showSolution()
{
    InputDataDialog inputDialog(this);
    inputDialog.exec();
    std::pair<QString, int> value = inputDialog.getValue();
    bool contains = false;
    std::size_t index = 0;
    for (auto it = cities.begin(); !contains && it != cities.end(); it++, index++)
        contains = (*it)->name == value.first;

    if (!contains)
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Ошибка", "Нет города с таким названием!");
        messageBox.setFixedSize(500, 200);
        messageBox.show();
    }
    else
    {
        switch (value.second)
        {
        case 0:
            // в глубину
            solveDepth(index);
            break;
        case 1:
            // в ширину
            break;
        case 2:
            // дейкстра
            break;
        default:
            QMessageBox messageBox;
            messageBox.critical(0, "Ошибка", "Как ты это выбрал?");
            messageBox.setFixedSize(500, 200);
            messageBox.show();
            break;
        }
    }
}

void MainWindow::cb(std::string a, std::size_t b)
{
    std::cout << a << " : " << b << std::endl;
    ui->statusbar->showMessage(QString((a + ": " + std::to_string(b)).c_str()));
    for (auto it = cities.begin(); it != cities.end(); it++)
        if ((*it)->name.toStdString() == a)
            (*it)->setSelected(true);
    QThread::sleep(1);
}

void MainWindow::solveDepth(size_t index)
{
    Graph graph;
    for (CityModel *c : cities)
        graph.cities.push_back(new GCity(c->name.toStdString()));
    for (RoadModel *r : roads)
    {
        GCity *A = nullptr, *B = nullptr;
        for (auto it = graph.cities.begin(); A == nullptr && B == nullptr && it != graph.cities.end(); it++)
            if ((*it)->name == r->A->name.toStdString())
                A = *it;
            else if ((*it)->name == r->B->name.toStdString())
                B = *it;
        graph.roads.push_back(new GRoad(A, B, r->length));
    }
    std::string message = graph.solve_depth(index, [this](std::string a, std::size_t b)
                                            { cb(a, b); });
    std::cout << message << std::endl;
    SolutionDialog dialog(message);
    dialog.exec();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
    {
        scene->choosing_cities = false;
        addRoadFirstCity = nullptr;
        ui->statusbar->clearMessage();
    }
    else if (e->key() == Qt::Key_Delete)
    {
        QGraphicsItem *item = scene->QGraphicsScene::focusItem();
        CityModel *c = dynamic_cast<CityModel *>(item);
        if (c)
        {
            for (auto i = cities.begin(); i != cities.end(); i++)
                if ((*i)->name == c->name)
                {
                    delete *i;
                    cities.erase(i);
                    break;
                }

            for (auto i = roads.begin(); i != roads.end(); i++)
                if ((*i)->A == c || (*i)->B == c)
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

void MainWindow::save_to_file()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        tr("Save graph"), "",
        tr("Text Files (*.txt)"));
    if (fileName.isEmpty())
        return;
    std::fstream file(fileName.toStdString(), std::ios::out);
    if (!file)
        return;

    file << cities.size();
    for (auto i : cities)
        file << *i;

    for (auto i : roads)
        file << i->length << '\n'
             << i->A->name.toStdString() << '\n'
             << i->B->name.toStdString() << '\n';

    file.close();
}

void MainWindow::open_file()
{
    roads.clear();
    cities.clear();
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open Address Book"), "",
        tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    std::fstream file(fileName.toStdString(), std::ios::in);
    if (!file)
    {
        return;
    }
    int n;
    file >> n;
    for (int i = 0; i < n; ++i)
    {
        CityModel *new_city = new CityModel();
        file >> *new_city;
        cities.push_back(new_city);
        scene->addItem(new_city);
    }
    while (file)
    {
        double l;
        std::string name;
        CityModel *first_city, *second_city;
        file >> l >> name;
        for (auto i : cities)
            if (i->name.toStdString() == name)
                first_city = i;
        file >> name;
        for (auto i : cities)
            if (i->name.toStdString() == name)
                second_city = i;

        RoadModel *new_road = new RoadModel(first_city, second_city, l);
        roads.push_back(new_road);
        scene->addItem(new_road);
    }
    scene->update();
    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
