#include "widget/mainWindow/mainWindow.h"

#include <QApplication>

/*
Я тут к такому выводу пришел, что эта функция по факту просто
обертка для первого диалога/окна, которое будет вызывать остальные.
К 6-ой версии Qt могли бы уже и runApp сделать.
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
