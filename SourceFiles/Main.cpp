#include <QApplication>
#include "MainWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("ImageViewer");
    app.setOrganizationName("ImageViewer");

    MainWindow mainWindow;
    mainWindow.show();

    return (app.exec());
}