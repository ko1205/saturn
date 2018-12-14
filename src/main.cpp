#include <QApplication>
#include "mainwindow.h"
#include <QHeaderView>

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
//    app.setStyle("windows");
//    app.setStyleSheet("* {color:black;} QHeaderView { background-color:gray;}");
    MainWindow w;
    w.show();

    return app.exec();
}
