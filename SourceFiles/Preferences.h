#pragma once

#include <QSettings>

class Preferences : public QSettings {
public:
    Preferences(QObject* parent = Q_NULLPTR);
    ~Preferences();

    void load();
    void save();

    QString bgColorSlideshow();
    QString bgColorView();
    bool showMenu();
    bool showStatusBar();
    bool showToolBar();
    QString sortBy();
    int zoomStep();
    int timeout();

    void setBgColorSlideshow(QString value);
    void setBgColorView(QString value);
    void setShowMenuBar(bool value);
    void setShowStatusBar(bool value);
    void setShowToolBar(bool value);
    void setSortBy(QString value);
    void setTimeout(int value);
    void setZoomStep(int value);

private:
    bool m_showMenuBar;
    bool m_showStatusBar;
    bool m_showToolBar;
    int m_timeout;
    int m_zoomStep;
    QString m_bgColorView;
    QString m_bgColorSlideshow;
    QString m_sortBy;
};