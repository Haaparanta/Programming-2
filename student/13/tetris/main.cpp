#include "mainwindow.hh"
#include <QApplication>

/*
 * name: Vesa Haaparanta
 * email: vesa.haaparanta@tuni.fi
 * student id: 290336
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
