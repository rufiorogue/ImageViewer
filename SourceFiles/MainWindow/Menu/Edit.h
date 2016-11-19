#pragma once

#include <QMenu>

namespace Menu {

class Edit : public QMenu {
public:
    Edit(QWidget* parent = Q_NULLPTR);
    ~Edit();

    QAction* preferences();
    QAction* sortByDate();
    QAction* sortByFileName();

private:
    void setup();

    QAction* m_preferences;
    QAction* m_sortByDate;
    QAction* m_sortByFileName;
    QActionGroup* m_sortGroup;
};

}