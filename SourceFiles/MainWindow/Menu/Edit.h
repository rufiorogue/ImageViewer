#pragma once

#include <QMenu>

namespace Menu {

class Edit : public QMenu {
public:
    Edit(QWidget* parent = Q_NULLPTR);
    ~Edit();

    QAction* preferences();
    QAction* sortAscending();
    QAction* sortByDate();
    QAction* sortByFileName();
    QAction* sortDescending();

private:
    void setup();

    QAction* m_preferences;
    QAction* m_sortAscending;
    QAction* m_sortByDate;
    QAction* m_sortByFileName;
    QAction* m_sortDescending;
    QActionGroup* m_sortGroup;
    QActionGroup* m_sortGroupAdvanced;
};

}