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
    m_bgColorSlideshow = value("bgColorSlideshow", "#ffffff").toString();
    m_bgColorView = value("bgColorView", "#ffffff").toString();
    m_keyNextImage = value("keyNextImage", Qt::Key_Right).toInt();
    m_keyPreviousImage = value("keyPreviousImage", Qt::Key_Left).toInt();
    m_showMenuBar = value("showMenuBar", true).toBool();
    m_showStatusBar = value("showStatusBar", true).toBool();
    m_showToolBar = value("showToolBar", true).toBool();
    m_sortBy = value("sortBy", "filename").toString();
    m_sortByAdvanvced = value("sortByAdvanced", "ascending").toString();
    m_timeout = value("timeout", 5).toInt();
    m_zoomStep = value("zoomStep", 25).toInt();
}

void Preferences::save()
{
    setValue("bgColorSlideshow", m_bgColorSlideshow);
    setValue("bgColorView", m_bgColorView);
    setValue("keyNextImage", m_keyNextImage);
    setValue("keyPreviousImage", m_keyPreviousImage);
    setValue("showMenuBar", m_showMenuBar);
    setValue("showStatusBar", m_showStatusBar);
    setValue("showToolBar", m_showToolBar);
    setValue("sortBy", m_sortBy);
    setValue("sortByAdvanced", m_sortByAdvanvced);
    setValue("timeout", m_timeout);
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

int Preferences::timeout()
{
    return (m_timeout);
}

void Preferences::setTimeout(int value)
{
    m_timeout = value;
}

QString Preferences::bgColorView()
{
    return (m_bgColorView);
}

void Preferences::setBgColorView(QString value)
{
    m_bgColorView = value;
}

QString Preferences::bgColorSlideshow()
{
    return (m_bgColorSlideshow);
}

void Preferences::setBgColorSlideshow(QString value)
{
    m_bgColorSlideshow = value;
}

QString Preferences::sortBy()
{
    return (m_sortBy);
}

void Preferences::setSortBy(QString value)
{
    m_sortBy = value;
}

QString Preferences::sortByAdvanced()
{
    return (m_sortByAdvanvced);
}

void Preferences::setSortByAdvanced(QString value)
{
    m_sortByAdvanvced = value;
}

int Preferences::keyNextImage()
{
    return (m_keyNextImage);
}

int Preferences::keyPreviousImage()
{
    return (m_keyPreviousImage);
}

void Preferences::setKeyNextImage(int value)
{
    m_keyNextImage = value;
}

void Preferences::setKeyPreviousImage(int value)
{
    m_keyPreviousImage = value;
}
