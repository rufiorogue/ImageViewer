#pragma once

#include <QSettings>

class Preferences : public QSettings {
public:
    Preferences(QObject* parent = Q_NULLPTR);
    ~Preferences();

    void load();
    void save();

    bool showMenu();
    bool showStatusBar();
    bool showToolBar();
    int zoomStep();
    int timeout();

    void setShowMenuBar(bool value);
    void setShowStatusBar(bool value);
    void setShowToolBar(bool value);
    void setTimeout(int value);
    void setZoomStep(int value);

private:
    bool m_showMenuBar;
    bool m_showStatusBar;
    bool m_showToolBar;
    int m_timeout;
    int m_zoomStep;
};