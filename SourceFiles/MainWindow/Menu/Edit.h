#pragma once

#include <QMenu>

namespace Menu {

class Edit : public QMenu {
public:
    Edit(QWidget* parent = Q_NULLPTR);
    ~Edit();

    QAction* preferences();

private:
    void setup();

    QAction* m_preferences;
};

}