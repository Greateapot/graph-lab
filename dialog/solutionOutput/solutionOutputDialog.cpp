#include "solutionOutputDialog.h"
#include "ui_solutionOutputDialog.h"

#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>

#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>


SolutionDialog::SolutionDialog(std::string message, QWidget *parent) : QDialog(parent), ui(new Ui::SolutionDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Close), &QPushButton::released, this, &SolutionDialog::on_pushButton_close_clicked);
    ui->textBrowser->setText(QString(message.c_str()));

    // int n = 0;
    // for (auto i : cities)
    // {
    //     city_names.push_back(i->name);
    //     matrix.emplace_back();
    //     for (int j = 0; j < n; j++)
    //         matrix[n].push_back(-1);

    //     for (int j = 0; j < n + 1; j++)
    //         matrix[j].push_back(-1);

    //     n++;
    // }

    // for (auto i : roads)
    // {
    //     int first_city_index = distance(city_names.begin(),
    //                                     std::find(city_names.begin(),
    //                                               city_names.end(),
    //                                               i->A->name));
    //     int second_city_index = distance(city_names.begin(),
    //                                      std::find(city_names.begin(),
    //                                                city_names.end(),
    //                                                i->B->name));
    //     matrix[first_city_index][second_city_index] = i->length;
    // }
    // size_t s_city_num = 0;
    // for (; s_city_num < city_names.size(); s_city_num++)
    //     if (city_names[s_city_num] == starting_city)
    //         break;

    // print_matrix(matrix);

    // solve(matrix, s_city_num);
}

/* s.txt:
X, 7, X, X, 3, X, 6, 3,
7, X, 2, 4, X, X, X, X,
X, 2, X, X, X, X, X, 1,
X, 4, X, X, 6, 9, X, X,
3, X, X, 6, X, 7, X, X,
X, X, X, 9, 7, X, 4, X,
6, X, X, X, X, 4, X, 1,
3, X, 1, X, X, X, 1, X,
*/

// void SolutionDialog::print_matrix(std::vector<std::vector<double>> matrix)
// {
//     for (size_t i = 0; i < matrix.size(); i++)
//     {
//         for (size_t j = 0; j < matrix[i].size(); j++)
//             if (matrix[i][j] < 0)
//                 std::cout << "X, ";
//             else
//                 std::cout << matrix[i][j] << ", ";
//         std::cout << "\n";
//     }
// }

// QString SolutionDialog::double_to_str(double in)
// {
//     QString result = QString::fromStdString(std::to_string(in));
//     double intpart;
//     while (result.back() == '0')
//         result.remove(result.length() - 1, 1);

//     if (modf(in, &intpart) == 0.0)
//         result.remove(result.length() - 1, 1);

//     return result;
// }

// void SolutionDialog::solve(std::vector<std::vector<double>> matrix, int starting_city)
// {
//     std::priority_queue<std::pair<double, int>> queue;
//     std::vector<std::vector<int>> came_from;
//     queue.push(std::make_pair(0, starting_city));
//     std::vector<double> cost;

//     for (size_t i = 0; i < matrix.size(); i++)
//     {
//         cost.push_back(INFINITY);
//         came_from.emplace_back();
//     }
//     cost[starting_city] = 0;
//     while (!queue.empty())
//     {
//         int cur = queue.top().second;
//         queue.pop();
//         for (size_t i = 0; i < matrix.size(); i++)
//         {
//             if (matrix[cur][i] != -1)
//             {
//                 double ncost = cost[cur] + matrix[cur][i];
//                 if (ncost < cost[i])
//                 {
//                     cost[i] = ncost;
//                     queue.push(std::make_pair(ncost, i));
//                     came_from[i] = came_from[cur];
//                     came_from[i].push_back(i);
//                 }
//             }
//         }
//     }
//     solution_text = "";
//     for (size_t i = 0; i < cost.size(); i++)
//         if (int(i) != starting_city)
//         {
//             if (cost[i] == INFINITY)
//             {
//                 solution_text += "До города " + city_names[i] + " добраться нельзя.\n";
//                 continue;
//             }
//             solution_text += "Расстояние до города " + city_names[i] + " равно: " + double_to_str(cost[i]);
//             solution_text += ". Путь: ";
//             for (auto city : came_from[i])
//                 solution_text += "->" + city_names[city];
//             solution_text += '\n';
//         }
// }

SolutionDialog::~SolutionDialog()
{
    delete ui;
}

void SolutionDialog::on_pushButton_close_clicked()
{
    close();
}
