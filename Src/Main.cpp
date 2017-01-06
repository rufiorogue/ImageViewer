
#include "MainWindow.h"

#include <QApplication>
#include <QDebug>
#include <QIcon>
#include <QStyle>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("ImageViewer");
    app.setOrganizationName("ImageViewer");

    qDebug() << "Widget style:" << app.style()->objectName();

    //QIcon::setThemeName("Flattr");
    //QIcon::setThemeName("Papirus");
    //QIcon::setThemeName("la-capitaine-icon-theme");

    qDebug() << "Icon theme:" << QIcon::themeName();



    // load initial image provided as argument
    QString initialImage;
    if (app.arguments().size() > 1 )
    {
        initialImage = app.arguments().at(1);
    }

    MainWindow mainWindow(initialImage);
    mainWindow.show();


    return (app.exec());
}
