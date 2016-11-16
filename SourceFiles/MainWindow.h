#pragma once

#include <QApplication>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QMainWindow>
#include <QMenuBar>

class ImageView;
class Preferences;
class StatusBar;
class ToolBar;

namespace Menu {
    class Edit;
    class File;
    class View;
}

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget* parent = Q_NULLPTR);
    ~MainWindow();

private:
    void setup();
    void setConnections();
    void setMenu();
    void setPreferences();
    void setSize();

    void openImage();
    void openPreferences();
    void saveImage();
    void showMenuBar(bool value);
    void showStatusBar(bool value);
    void showToolBar(bool value);
    void toggleFullscreen();

    const int WIDTH = 30; // %
    const int HEIGHT = 30; // %

    ImageView* m_imageView;
    Preferences* m_preferences;
    QMenuBar* m_menuBar;
    StatusBar* m_statusBar;
    ToolBar* m_toolBar;
    Menu::Edit* m_menuEdit;
    Menu::File* m_menuFile;
    Menu::View* m_menuView;
};