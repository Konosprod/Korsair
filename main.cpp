#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(rc);
    mainWindow w;
    w.setWindowTitle("Korsair");
    w.show();
    
    return a.exec();
}
