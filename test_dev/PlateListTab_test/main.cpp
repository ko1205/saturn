#include "../../src/platelisttab.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlateListTab w;
    w.show();

    return a.exec();
}
