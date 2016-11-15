#pragma once

#include <QMenu>

namespace Menu {

class View : public QMenu {
public:
    View(QWidget* parent = Q_NULLPTR);
    ~View();

    QAction* fullscreen();
    QAction* rotateLeft();
    QAction* rotateRight();
    QAction* showMenuBar();
    QAction* showStatusBar();
    QAction* showToolBar();

private:
    void setup();

    QAction* m_fullscreen;
    QAction* m_rotateLeft;
    QAction* m_rotateRight;
    QAction* m_showMenuBar;
    QAction* m_showStatusBar;
    QAction* m_showToolBar;
};

}