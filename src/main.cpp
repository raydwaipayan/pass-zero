#include "passzero.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    passzero w;
    w.show();
    return a.exec();
}
