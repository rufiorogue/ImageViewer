#include "Slideshow.h"

Slideshow::Slideshow(QWidget* parent)
    : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    m_timeoutLabel = new QLabel(this);
    m_timeoutSlider = new QSlider(this);

    setup();
}

Slideshow::~Slideshow()
{
}

void Slideshow::setup()
{
    setLayout(m_layout);
    setSignals();
    setWidgets();
}

void Slideshow::setWidgets()
{
    m_timeoutSlider->setOrientation(Qt::Orientation::Horizontal);
    m_timeoutSlider->setRange(1, 100);
    m_layout->addWidget(m_timeoutLabel);
    m_layout->addWidget(m_timeoutSlider);
}

int Slideshow::timeout()
{
    return (m_timeoutValue);
}

void Slideshow::setTimeout(int value)
{
    m_timeoutSlider->setValue(value);
}

void Slideshow::setSignals()
{
    connect(m_timeoutSlider, &QSlider::valueChanged, this,
        &Slideshow::timeoutChanged);
}

void Slideshow::timeoutChanged(int value)
{
    m_timeoutValue = value;
    m_timeoutLabel->setText("<b>Timeout</b> - " + QString::number(value));
}
