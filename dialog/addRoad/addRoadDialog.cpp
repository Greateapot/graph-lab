#include "addRoadDialog.h"
#include "ui_addRoadDialog.h"

#include <QPushButton>

AddRoadDialog::AddRoadDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AddRoadDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::released, this, &AddRoadDialog::on_pushButton_ok_clicked);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::released, this, &AddRoadDialog::on_pushButton_cancel_clicked);
}

AddRoadDialog::~AddRoadDialog()
{
    delete ui;
}

double AddRoadDialog::getValue()
{
    return value;
}

bool AddRoadDialog::getIsBidirectional()
{
    return isBidirectional;
}

void AddRoadDialog::on_pushButton_cancel_clicked()
{
    close();
}

void AddRoadDialog::on_pushButton_ok_clicked()
{
    this->value = ui->doubleSpinBox->value();
    this->isBidirectional = ui->checkBox->isChecked();
    this->close();
}
