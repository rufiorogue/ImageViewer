#pragma once

#include <QDialog>
#include <QDialogButtonBox>
#include <QTabWidget>
#include <QVBoxLayout>

class Control;
class Preferences;
class Slideshow;

class PreferencesDialog : public QDialog {
public:
    PreferencesDialog(Preferences* preferences, QWidget* parent = Q_NULLPTR);
    ~PreferencesDialog();

    void load();
    void save();

private:
    void setup();
    void setSignals();
    void setWidgets();

    Control* m_control;
    Preferences* m_preferences;
    Slideshow* m_slideshow;
    QDialogButtonBox* m_buttonBox;
    QVBoxLayout* m_layout;
    QTabWidget* m_tabWidget;
};