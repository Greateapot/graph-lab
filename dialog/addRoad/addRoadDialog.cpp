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

void AddRoadDialog::on_pushButton_cancel_clicked()
{
    cancel = true;
    close();
}

void AddRoadDialog::on_pushButton_ok_clicked()
{
    length = ui->doubleSpinBox->value();
    is_bidirectional = ui->checkBox->isChecked();
    close();
}
