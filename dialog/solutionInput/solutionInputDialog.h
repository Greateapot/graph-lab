#pragma once

#include <QDialog>

namespace Ui
{
    class SolutionInputDialog;
}

class SolutionInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SolutionInputDialog(QWidget *parent = nullptr);
    ~SolutionInputDialog();

    QString city_name;
    int solution_method;
    bool cancel = false;

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_cancel_clicked();

private:
    Ui::SolutionInputDialog *ui;
};
