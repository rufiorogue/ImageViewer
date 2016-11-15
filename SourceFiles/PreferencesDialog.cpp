#include "PreferencesDialog.h"

#include "PreferencesDialog/Control.h"

#include "Preferences.h"

PreferencesDialog::PreferencesDialog(Preferences* preferences, QWidget* parent)
    : QDialog(parent)
{
    m_buttonBox = new QDialogButtonBox(this);
    m_control = new Control(this);
    m_layout = new QVBoxLayout(this);
    m_preferences = preferences;
    m_tabWidget = new QTabWidget(this);

    setup();
}

PreferencesDialog::~PreferencesDialog()
{
}

void PreferencesDialog::setup()
{
    setLayout(m_layout);
    setSignals();
    setWidgets();
}

void PreferencesDialog::setWidgets()
{
    m_tabWidget->addTab(m_control, "Control");
    m_layout->addWidget(m_tabWidget);

    m_buttonBox->setStandardButtons(QDialogButtonBox::Ok
        | QDialogButtonBox::Cancel);
    m_layout->addWidget(m_buttonBox);
}

void PreferencesDialog::load()
{
    m_control->setZoomStep(m_preferences->zoomStep());
}

void PreferencesDialog::save()
{
    m_preferences->setZoomStep(m_control->zoomStep());
}

void PreferencesDialog::setSignals()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted, this,
        &PreferencesDialog::accept);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this,
        &PreferencesDialog::reject);
}
