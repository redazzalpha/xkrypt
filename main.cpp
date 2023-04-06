#include "mainwindow.h"
#include <QApplication>

using namespace std;
using namespace CryptoPP;

int main(int argc, char *argv[])
{
    using namespace CryptoPP;
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/assets/icon.ico"));
    MainWindow w;
    w.show();
    return a.exec();
}
