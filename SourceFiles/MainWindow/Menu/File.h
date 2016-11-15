#pragma once

#include <QMenu>

namespace Menu {

class File : public QMenu {
public:
    File(QWidget* parent = Q_NULLPTR);
    ~File();

    QAction* open();
    QAction* quit();

private:
    void setup();

    QAction* m_open;
    QAction* m_quit;
};

}