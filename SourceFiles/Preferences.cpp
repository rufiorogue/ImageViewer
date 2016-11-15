#include "Preferences.h"

Preferences::Preferences(QObject* parent)
    : QSettings(parent)
{
    load();
}

Preferences::~Preferences()
{
}

void Preferences::load()
{
    m_showMenuBar = value("showMenuBar", true).toBool();
    m_showStatusBar = value("showStatusBar", true).toBool();
    m_showToolBar = value("showToolBar", true).toBool();
    m_zoomStep = value("zoomStep", 25).toInt();
}

void Preferences::save()
{
    setValue("showMenuBar", m_showMenuBar);
    setValue("showStatusBar", m_showStatusBar);
    setValue("showToolBar", m_showToolBar);
    setValue("zoomStep", m_zoomStep);
}

void Preferences::setShowToolBar(bool value)
{
    m_showToolBar = value;
}

bool Preferences::showToolBar()
{
    return (m_showToolBar);
}

void Preferences::setShowStatusBar(bool value)
{
    m_showStatusBar = value;
}

bool Preferences::showStatusBar()
{
    return (m_showStatusBar);
}

int Preferences::zoomStep()
{
    return (m_zoomStep);
}

void Preferences::setZoomStep(int value)
{
    m_zoomStep = value;
}

bool Preferences::showMenu()
{
    return (m_showMenuBar);
}

void Preferences::setShowMenuBar(bool value)
{
    m_showMenuBar = value;
}
