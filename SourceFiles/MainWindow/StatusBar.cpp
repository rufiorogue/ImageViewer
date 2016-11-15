#include "StatusBar.h"

#include "ImageView.h"

StatusBar::StatusBar(QWidget* parent)
    : QStatusBar(parent)
{
    m_message = new QLabel(this);
}

StatusBar::~StatusBar()
{
}

void StatusBar::update(ImageView* imageView)
{
    if (imageView->fileName().isNull()) {
        return;
    }

    QFileInfo file(imageView->fileName());

    QString message;
    message += file.fileName();
    message += "    ";
    message += QString::number(imageView->zoom()) + "%";

    m_message->setText(message);
    m_message->update();

    addWidget(m_message);
}
