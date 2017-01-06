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
    m_bgColorNormal = value("bgColorNormal", "#ffffff").toString();
    m_bgColorFullscreen = value("bgColorFullscreen", "#222222").toString();
    m_keyPreviousImage = value("keyPreviousImage", Qt::Key_A).toInt();
    m_keyNextImage = value("keyNextImage", Qt::Key_D).toInt();
    m_showMenu = value("showMenu", true).toBool();
    m_showStatusBar = value("showStatusBar", true).toBool();
    m_showToolBar = value("showToolBar", true).toBool();
    m_sortCriteria = value("sortCriteria", "filename").toString();
    m_sortOrder = value("sortOrder", "ascending").toString();
    m_timeout = value("timeout", 5).toInt();
    m_zoomStep = value("zoomStep", 25).toInt();
    m_zoomFit = value("zoomFit", true).toBool();
    m_windowSize = value("windowSize", QSize(800,700)).toSize();
}

void Preferences::save()
{
    setValue("bgColorFullscreen", m_bgColorFullscreen);
    setValue("bgColorNormal", m_bgColorNormal);
    setValue("keyPreviousImage", m_keyPreviousImage);
    setValue("keyNextImage", m_keyNextImage);
    setValue("showMenu", m_showMenu);
    setValue("showStatusBar", m_showStatusBar);
    setValue("showToolBar", m_showToolBar);
    setValue("sortCriteria", m_sortCriteria);
    setValue("sortOrder", m_sortOrder);
    setValue("timeout", m_timeout);
    setValue("zoomStep", m_zoomStep);
    setValue("zoomFit", m_zoomFit);
    setValue("windowSize", m_windowSize);
}

void Preferences::restoreDefaults()
{
    clear();
    load();
}
