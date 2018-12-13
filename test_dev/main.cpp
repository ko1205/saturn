#include <QCoreApplication>
#include "item.h"

int item::count = 0;
int aa = 0;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    item bb;
    item cc;
    for(int i = 0; i<100 ;i++){
        item *test = new item;
    }

    return a.exec();
}
