#include "solutionInputDialog.h"
#include "ui_solutionInputDialog.h"

#include <QPushButton>

SolutionInputDialog::SolutionInputDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SolutionInputDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::released, this, &SolutionInputDialog::on_pushButton_ok_clicked);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::released, this, &SolutionInputDialog::on_pushButton_cancel_clicked);
}

SolutionInputDialog::~SolutionInputDialog()
{
    delete ui;
}

void SolutionInputDialog::on_pushButton_cancel_clicked()
{
    cancel = true;
    close();
}

void SolutionInputDialog::on_pushButton_ok_clicked()
{
    city_name = ui->lineEdit->text();
    solution_method = ui->comboBox->currentIndex();
    close();
}
