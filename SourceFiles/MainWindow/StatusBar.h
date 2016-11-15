#pragma once

#include <QFileInfo>
#include <QLabel>
#include <QStatusBar>

class ImageView;

class StatusBar : public QStatusBar {
public:
    StatusBar(QWidget* parent = Q_NULLPTR);
    ~StatusBar();

    void update(ImageView* imageView);

private:
    QLabel* m_message;
};