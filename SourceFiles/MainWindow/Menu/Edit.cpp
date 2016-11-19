#include "Edit.h"

Menu::Edit::Edit(QWidget* parent)
    : QMenu(parent)
{
    m_preferences = new QAction(this);
    m_sortByDate = new QAction(this);
    m_sortByFileName = new QAction(this);
    m_sortGroup = new QActionGroup(this);

    setup();
}

Menu::Edit::~Edit()
{
}

void Menu::Edit::setup()
{
    // Edit
    setTitle("Edit");

    // Edit -> Sorting
    QMenu* sorting = addMenu("Sorting");

    // Edit -> Sorting -> Sort By Date
    m_sortByDate->setActionGroup(m_sortGroup);
    m_sortByDate->setCheckable(true);
    m_sortByDate->setText("Sort By Date");
    sorting->addAction(m_sortByDate);

    // Edit -> Sorting -> Sort By Filename
    m_sortByFileName->setActionGroup(m_sortGroup);
    m_sortByFileName->setCheckable(true);
    m_sortByFileName->setText("Sort By Filename");
    sorting->addAction(m_sortByFileName);

    // Edit -> Separator
    addSeparator();

    // Edit -> Preferences
    m_preferences->setText("Preferences");
    m_preferences->setIcon(QIcon("Images/preferences.png"));
    addAction(m_preferences);
}

QAction* Menu::Edit::preferences()
{
    return (m_preferences);
}

QAction* Menu::Edit::sortByDate()
{
    return (m_sortByDate);
}

QAction* Menu::Edit::sortByFileName()
{
    return (m_sortByFileName);
}
