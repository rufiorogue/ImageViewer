#pragma once

#include <QSettings>
#include <QSize>

class Preferences : public QSettings
{
public:
    Preferences(QObject *parent = Q_NULLPTR);
    ~Preferences();

    void load();
    void save();
    void restoreDefaults();

#define PARAMETER(type, name)\
    public:\
        const type & name()const { return m_##name; }\
        void set_##name(const type &value) { m_##name = value; }\
    private:\
        type m_##name;

    PARAMETER(QString, bgColorNormal)
    PARAMETER(QString, bgColorFullscreen)
    PARAMETER(int, keyNextImage)
    PARAMETER(int, keyPreviousImage)
    PARAMETER(bool, showMenu)
    PARAMETER(bool, showStatusBar)
    PARAMETER(bool, showToolBar)
    PARAMETER(bool, zoomFit)
    PARAMETER(QString, sortOrder)
    PARAMETER(QString, sortCriteria)
    PARAMETER(int, zoomStep)
    PARAMETER(int, timeout)
    PARAMETER(QSize, windowSize)

};


