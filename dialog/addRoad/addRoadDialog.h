#pragma once

#include <QDialog>

namespace Ui
{
    class AddRoadDialog;
}

class AddRoadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRoadDialog(QWidget *parent = nullptr);
    ~AddRoadDialog();

    double length = 1.0;
    bool is_bidirectional = false;
    bool cancel = false;

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_cancel_clicked();

private:
    Ui::AddRoadDialog *ui;
};
