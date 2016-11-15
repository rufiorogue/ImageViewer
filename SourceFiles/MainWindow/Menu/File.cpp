#include "File.h"

Menu::File::File(QWidget* parent)
    : QMenu(parent)
{
    m_open = new QAction(this);
    m_quit = new QAction(this);

    setup();
}

Menu::File::~File()
{
}

void Menu::File::setup()
{
    // File
    setTitle("File");

    // File -> Open
    m_open->setIcon(QIcon("Images/open-file.png"));
    m_open->setText("Open");
    addAction(m_open);

    // File -> Separator
    addSeparator();

    // File -> Quit
    m_quit->setIcon(QIcon("Images/quit.png"));
    m_quit->setText("Quit");
    addAction(m_quit);
}

QAction* Menu::File::open()
{
    return (m_open);
}

QAction* Menu::File::quit()
{
    return (m_quit);
}
