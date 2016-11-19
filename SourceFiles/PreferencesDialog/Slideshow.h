#pragma once

#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>

class Slideshow : public QWidget {
public:
    Slideshow(QWidget* parent = Q_NULLPTR);
    ~Slideshow();

    int timeout();

    void setTimeout(int value);

private:
    void setup();
    void setConnections();
    void setWidgets();

    void timeoutChanged(int value);

    int m_timeoutValue;

    QLabel* m_timeoutLabel;
    QSlider* m_timeoutSlider;
    QVBoxLayout* m_layout;
};