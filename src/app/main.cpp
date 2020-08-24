#include "passzero.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication   a(argc, argv);
    zero::Passzero w;

    w.show();
    return a.exec();
}
