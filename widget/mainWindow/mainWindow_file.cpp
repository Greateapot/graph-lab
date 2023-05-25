#include "mainWindow.h"
#include "ui_mainWindow.h"

#include <QFileDialog>

// TODO: RW
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

// TODO: RW
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
