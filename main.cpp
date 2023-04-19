#include "mainwindow.h"
#include <QApplication>

using namespace std;
namespace kkk{
    QMetaType type = QMetaType::fromName("std::vector<std::string>&");

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/assets/icon.ico"));
    MainWindow w;
    w.show();

    return a.exec();
}
