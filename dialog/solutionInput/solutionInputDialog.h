#pragma once

#include <QDialog>

namespace Ui
{
    class InputDataDialog;
}

class InputDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDataDialog(QWidget *parent = nullptr);
    ~InputDataDialog();

    QString city_name;
    int solution_method;

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_cancel_clicked();

private:
    Ui::InputDataDialog *ui;
};
