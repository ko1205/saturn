#include "../../src/dirselector.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DirSelector w;
    w.show();

    return a.exec();
}
