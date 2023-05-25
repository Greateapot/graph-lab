#include "utils/utils.h"

#include <string>
#include <cmath>

#include <QApplication>
#include <QTime>

QString double2QString(double in)
{
    QString out = QString::fromStdString(std::to_string(in));
    double intpart;
    while (out.back() == '0')
        out.remove(out.length() - 1, 1);

    if (modf(in, &intpart) == 0.0) // {int}. <-- точка
        out.remove(out.length() - 1, 1);

    return out;
}

// stackoverflow code (3752742)
void delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}