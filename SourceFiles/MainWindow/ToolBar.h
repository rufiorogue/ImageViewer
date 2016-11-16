#pragma once

#include <QToolBar>

class ToolBar : public QToolBar {
public:
    ToolBar(QWidget* parent = Q_NULLPTR);
    ~ToolBar();

    QAction* fullscreen();
    QAction* openFile();
    QAction* saveFile();
    QAction* playSlideshow();
    QAction* zoomFit();
    QAction* zoomOriginal();

private:
    void setup();
    void setActions();

    QAction* m_deleteFile;
    QAction* m_fullScreen;
    QAction* m_openFile;
    QAction* m_playSlideshow;
    QAction* m_saveFile;
    QAction* m_zoomFit;
    QAction* m_zoomOriginal;
    QWidget* m_spacerOne;
    QWidget* m_spacerTwo;
};
