#include "mainwindow.h"
#include <QApplication>
#include <regex>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/assets/icon.ico"));
    MainWindow w;
    w.show();

    return a.exec();
}
