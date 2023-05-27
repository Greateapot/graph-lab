#include "addCityDialog.h"
#include "ui_addCityDialog.h"

#include <QPushButton>

AddCityDialog::AddCityDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AddCityDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::released, this, &AddCityDialog::on_pushButton_ok_clicked);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::released, this, &AddCityDialog::on_pushButton_cancel_clicked);
}

AddCityDialog::~AddCityDialog()
{
    delete ui;
}

void AddCityDialog::on_pushButton_cancel_clicked()
{
    cancel = true;
    close();
}

void AddCityDialog::on_pushButton_ok_clicked()
{
    city_name = ui->lineEdit->text();
    close();
}
