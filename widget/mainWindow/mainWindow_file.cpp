#include "mainWindow.h"
#include "ui_mainWindow.h"

#include <QFileDialog>

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        tr("Save"), "",
        tr("Text Files (*.txt)"));

    if (fileName.isEmpty())
        return ui->statusbar->showMessage("Имя файла не может быть пустым!", STATUS_MESSAGE_DELAY);

    std::fstream file(fileName.toStdString(), std::ios::out | std::ios::binary);
    if (!file)
        return ui->statusbar->showMessage("Не удается открыть файл!", STATUS_MESSAGE_DELAY);

    for (auto city : cities)
        file << *city;

    file << GDLTR;

    for (auto road : roads)
        file << road->length << DLTR
             << road->A->name.toStdString() << DLTR
             << road->B->name.toStdString() << DLTR;

    file << GDLTR;

    file.close();
}

void MainWindow::load()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Load"), "",
        tr("Text Files (*.txt)"));

    if (fileName.isEmpty())
        return ui->statusbar->showMessage("Имя файла не может быть пустым!", STATUS_MESSAGE_DELAY);

    std::fstream file(fileName.toStdString(), std::ios::in | std::ios::binary);
    if (!file)
        return ui->statusbar->showMessage("Не удается открыть файл!", STATUS_MESSAGE_DELAY);

    roads.clear();
    cities.clear();
    scene->clear();

    while (file.peek() != GDLTR)
    {
        CityModel *new_city = new CityModel();
        file >> *new_city;
        cities.push_back(new_city);
        scene->addItem(new_city);
    }
    file.get(); // skip GDLTR

    while (file.peek() != GDLTR)
    {
        std::string name_raw, length_raw;
        double length;
        CityModel *A, *B;

        getline(file, length_raw, DLTR);
        length = stod(length_raw);

        getline(file, name_raw, DLTR);
        for (auto city : cities)
            if (city->name.toStdString() == name_raw)
            {
                A = city;
                break;
            }

        getline(file, name_raw, DLTR);
        for (auto city : cities)
            if (city->name.toStdString() == name_raw)
            {
                B = city;
                break;
            }

        RoadModel *new_road = new RoadModel(A, B, length);
        roads.push_back(new_road);
        scene->addItem(new_road);
    }
    file.get(); // skip GDLTR

    scene->update();
    file.close();
}
