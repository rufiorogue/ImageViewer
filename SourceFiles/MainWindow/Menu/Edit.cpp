#include "Edit.h"

Menu::Edit::Edit(QWidget* parent)
    : QMenu(parent)
{
    m_preferences = new QAction(this);

    setup();
}

Menu::Edit::~Edit()
{
}

void Menu::Edit::setup()
{
    // Edit
    setTitle("Edit");

    // Edit -> Preferences
    m_preferences->setText("Preferences");
    m_preferences->setIcon(QIcon("Images/preferences.png"));
    addAction(m_preferences);
}

QAction* Menu::Edit::preferences()
{
    return (m_preferences);
}
