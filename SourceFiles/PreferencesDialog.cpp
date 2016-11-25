#include "PreferencesDialog.h"

#include "PreferencesDialog/Control.h"
#include "PreferencesDialog/Display.h"
#include "PreferencesDialog/Slideshow.h"

#include "Preferences.h"

PreferencesDialog::PreferencesDialog(Preferences* preferences, QWidget* parent)
    : QDialog(parent)
{
    m_buttonBox = new QDialogButtonBox(this);
    m_display = new Display(this);
    m_control = new Control(this);
    m_layout = new QVBoxLayout(this);
    m_preferences = preferences;
    m_slideshow = new Slideshow(this);
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
    m_tabWidget->addTab(m_display, "Display");
    m_tabWidget->addTab(m_slideshow, "Slideshow");
    m_layout->addWidget(m_tabWidget);

    m_buttonBox->setStandardButtons(QDialogButtonBox::Ok
        | QDialogButtonBox::Cancel);
    m_layout->addWidget(m_buttonBox);
}

void PreferencesDialog::load()
{
    m_control->setKeyNextImage(m_preferences->keyNextImage());
    m_control->setKeyPreviousImage(m_preferences->keyPreviousImage());
    m_control->setZoomStep(m_preferences->zoomStep());
    m_display->setBgColorSlideshow(m_preferences->bgColorSlideshow());
    m_display->setBgColorView(m_preferences->bgColorView());
    m_slideshow->setTimeout(m_preferences->timeout());
}

void PreferencesDialog::save()
{
    m_preferences->setBgColorSlideshow(m_display->bgColorSlideshow());
    m_preferences->setBgColorView(m_display->bgColorView());
    m_preferences->setKeyNextImage(m_control->keyNextImage());
    m_preferences->setKeyPreviousImage(m_control->keyPreviousImage());
    m_preferences->setTimeout(m_slideshow->timeout());
    m_preferences->setZoomStep(m_control->zoomStep());
}

void PreferencesDialog::setSignals()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted, this,
        &PreferencesDialog::accept);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this,
        &PreferencesDialog::reject);
}
