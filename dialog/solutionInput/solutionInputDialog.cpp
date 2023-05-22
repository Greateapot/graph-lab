#include "solutionInputDialog.h"
#include "ui_solutionInputDialog.h"

#include <QPushButton>

InputDataDialog::InputDataDialog(QWidget *parent) : QDialog(parent), ui(new Ui::InputDataDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::released, this, &InputDataDialog::on_pushButton_ok_clicked);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::released, this, &InputDataDialog::on_pushButton_cancel_clicked);
}

InputDataDialog::~InputDataDialog()
{
    delete ui;
}

std::pair<QString, int> InputDataDialog::getValue()
{
    return value;
}

void InputDataDialog::on_pushButton_cancel_clicked()
{
    close();
}

void InputDataDialog::on_pushButton_ok_clicked()
{
    this->value.first = ui->lineEdit->text();
    this->value.second = ui->comboBox->currentIndex();
    this->close();
}
