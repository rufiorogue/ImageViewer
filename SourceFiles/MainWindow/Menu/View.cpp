#include "View.h"

Menu::View::View(QWidget* parent)
    : QMenu(parent)
{
    m_fullscreen = new QAction(this);
    m_rotateLeft = new QAction(this);
    m_rotateRight = new QAction(this);
    m_showMenuBar = new QAction(this);
    m_showStatusBar = new QAction(this);
    m_showToolBar = new QAction(this);

    setup();
}

Menu::View::~View()
{
}

void Menu::View::setup()
{
    // View
    setTitle("View");

    // View -> Show Menu
    m_showMenuBar->setCheckable(true);
    m_showMenuBar->setText("Show Menu Bar");
    addAction(m_showMenuBar);

    // View -> Show Tool Bar
    m_showToolBar->setCheckable(true);
    m_showToolBar->setText("Show Tool Bar");
    addAction(m_showToolBar);

    // View -> Show Status Bar
    m_showStatusBar->setCheckable(true);
    m_showStatusBar->setText("Show Status Bar");
    addAction(m_showStatusBar);

    // View -> Separator
    addSeparator();

    // View -> Rotation
    QMenu* rotation = addMenu("Rotation");

    // View -> Rotation -> Rotate Left
    m_rotateLeft->setIcon(QIcon("Images/rotate-left.png"));
    m_rotateLeft->setText("Rotate Left");
    rotation->addAction(m_rotateLeft);

    // View -> Rotation -> Rotate Right
    m_rotateRight->setIcon(QIcon("Images/rotate-right.png"));
    m_rotateRight->setText("Rotate Right");
    rotation->addAction(m_rotateRight);

    // View -> Separator
    addSeparator();

    // View -> Fullscreen
    m_fullscreen->setIcon(QIcon("Images/fullscreen.png"));
    m_fullscreen->setText("Fullscreen");
    addAction(m_fullscreen);
}

QAction* Menu::View::showToolBar()
{
    return (m_showToolBar);
}

QAction* Menu::View::showStatusBar()
{
    return (m_showStatusBar);
}

QAction* Menu::View::rotateLeft()
{
    return (m_rotateLeft);
}

QAction* Menu::View::rotateRight()
{
    return (m_rotateRight);
}

QAction* Menu::View::fullscreen()
{
    return (m_fullscreen);
}

QAction* Menu::View::showMenuBar()
{
    return (m_showMenuBar);
}
