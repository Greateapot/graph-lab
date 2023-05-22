#pragma once

// #include <vector>

#include <QDialog>

namespace Ui
{
    class SolutionDialog;
}

class SolutionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SolutionDialog(std::string, QWidget *parent = nullptr);
    ~SolutionDialog();

    //    void solve(std::vector<std::vector<double>>, int);
    //    QString double_to_str(double);
    //    void print_matrix(std::vector<std::vector<double>>);

private slots:
    void on_pushButton_close_clicked();

private:
    Ui::SolutionDialog *ui;
    //    std::vector<QString> city_names;
    //    std::vector<std::vector<double>> matrix;
    //    QString solution_text;
};
