#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    mainWindow window(argv[1]);

    window.show();
    return app.exec();
}
