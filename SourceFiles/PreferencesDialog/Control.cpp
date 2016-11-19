#include "Control.h"

Control::Control(QWidget* parent)
    : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
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
}

void Control::setConnections()
{
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
