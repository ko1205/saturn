#include "../../src/plateviewcontroller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlateViewController w;
    w.show();

    return a.exec();
}
