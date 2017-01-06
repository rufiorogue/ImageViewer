#pragma once

#include <QKeyEvent>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QSlider>
#include <QWidget>

class Control : public QWidget {
public:
    Control(QWidget* parent = Q_NULLPTR);
    ~Control();

    int zoomStep();
    int keyNextImage();
    int keyPreviousImage();

    void setKeyNextImage(int value);
    void setKeyPreviousImage(int value);
    void setZoomStep(int value);

private:
    void setup();
    void setConnections();
    void setWidgets();

    QGridLayout* keySettings();

    void grabKey();
    void zoomStepChanged(int value);

    void keyPressEvent(QKeyEvent* event);

    bool m_capturing;

    int m_keyNextImage;
    int m_keyPreviousImage;
    int m_zoomStepValue;

    QLabel* m_zoomStepLabel;
    QPushButton* m_keyNextImageButton;
    QPushButton* m_keyPreviousImageButton;
    QSlider* m_zoomStepSlider;
    QVBoxLayout* m_layout;
};