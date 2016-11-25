#include "Control.h"

Control::Control(QWidget* parent)
    : QWidget(parent)
{
    m_capturing = false;
    m_layout = new QVBoxLayout(this);
    m_keyNextImageButton = new QPushButton(this);
    m_keyPreviousImageButton = new QPushButton(this);
    m_zoomStepLabel = new QLabel(this);
    m_zoomStepSlider = new QSlider(this);

    setup();
}

Control::~Control()
{
}

void Control::setup()
{
    setLayout(m_layout);
    setConnections();
    setWidgets();
}

void Control::setWidgets()
{
    m_zoomStepSlider->setOrientation(Qt::Orientation::Horizontal);
    m_zoomStepSlider->setRange(1, 100);
    m_layout->addWidget(m_zoomStepLabel);
    m_layout->addWidget(m_zoomStepSlider);
    m_layout->addLayout(keySettings());
}

void Control::setConnections()
{
    connect(m_keyNextImageButton, &QPushButton::clicked, this,
        &Control::grabKey);
    connect(m_keyPreviousImageButton, &QPushButton::clicked, this,
        &Control::grabKey);
    connect(m_zoomStepSlider, &QSlider::valueChanged, this,
        &Control::zoomStepChanged);
}

void Control::zoomStepChanged(int value)
{
    m_zoomStepValue = value;
    m_zoomStepLabel->setText("<b>Zoom Step</b> - " + QString::number(value));
}

int Control::zoomStep()
{
    return (m_zoomStepValue);
}

void Control::setZoomStep(int value)
{
    m_zoomStepSlider->setValue(value);
}

int Control::keyPreviousImage()
{
    return (m_keyPreviousImage);
}

QGridLayout* Control::keySettings()
{
    QGridLayout* layout = new QGridLayout(m_layout->widget());

    layout->addWidget(new QLabel("<b>Key Settings</b>", this), 0, 0);

    layout->addWidget(new QLabel("\tPrevious image", this), 1, 0);
    layout->addWidget(m_keyPreviousImageButton, 1, 1);

    layout->addWidget(new QLabel("\tNext image", this), 2, 0);
    layout->addWidget(m_keyNextImageButton, 2, 1);

    return (layout);
}

int Control::keyNextImage()
{
    return (m_keyNextImage);
}

void Control::keyPressEvent(QKeyEvent* event)
{
    if (m_capturing) {
        QString text = QKeySequence(event->key()).toString();
        if (m_keyPreviousImageButton->hasFocus()) {
            m_keyPreviousImage = event->key();
            m_keyPreviousImageButton->setText(text);
        } else if (m_keyNextImageButton->hasFocus()) {
            m_keyNextImage = event->key();
            m_keyNextImageButton->setText(text);
        }
    }

    QWidget::releaseKeyboard();
}

void Control::grabKey()
{
    QWidget::grabKeyboard();

    m_capturing = true;
}

void Control::setKeyNextImage(int value)
{
    m_keyNextImage = value;
    m_keyNextImageButton->setText(QKeySequence(value).toString());
}

void Control::setKeyPreviousImage(int value)
{
    m_keyPreviousImage = value;
    m_keyPreviousImageButton->setText(QKeySequence(value).toString());
}
