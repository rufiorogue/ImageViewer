#pragma once

#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>

class Control : public QWidget {
public:
    Control(QWidget* parent = Q_NULLPTR);
    ~Control();

    int zoomStep();

    void setZoomStep(int value);

private:
    void setup();
    void setSignals();
    void setWidgets();

    void zoomStepChanged(int value);

    int m_zoomStepValue;

    QLabel* m_zoomStepLabel;
    QSlider* m_zoomStepSlider;
    QVBoxLayout* m_layout;
};