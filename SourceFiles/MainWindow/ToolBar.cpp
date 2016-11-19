#include "ToolBar.h"

ToolBar::ToolBar(QWidget* parent)
    : QToolBar(parent)
{
    m_deleteFile = new QAction(this);
    m_fullScreen = new QAction(this);
    m_openFile = new QAction(this);
    m_playSlideshow = new QAction(this);
    m_saveFile = new QAction(this);
    m_spacerOne = new QWidget(this);
    m_spacerTwo = new QWidget(this);
    m_zoomFit = new QAction(this);
    m_zoomOriginal = new QAction(this);

    setup();
}

ToolBar::~ToolBar()
{
}

void ToolBar::setup()
{
    setActions();
    setContextMenuPolicy(Qt::ContextMenuPolicy::PreventContextMenu);
    setMovable(false);
    setStyleSheet("QToolBar { border: 0px; }");
}

void ToolBar::setActions()
{
    // Open Image
    m_openFile->setIcon(QIcon("Images/open-file.png"));
    m_openFile->setText("Open an Image");
    addAction(m_openFile);

    // Separator
    addSeparator();

    // Save Image As
    m_saveFile->setIcon(QIcon("Images/save-file-as.png"));
    m_saveFile->setText("Save a copy of the image");
    addAction(m_saveFile);

    // Delete Image
    m_deleteFile->setIcon(QIcon("Images/delete-file.png"));
    m_deleteFile->setText("Delete this image from disk");
    addAction(m_deleteFile);

    // Spacer
    m_spacerOne->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addWidget(m_spacerOne);

    // Play Slideshow
    m_playSlideshow->setIcon(QIcon("Images/play-slideshow.png"));
    m_playSlideshow->setText("Play slideshow");
    addAction(m_playSlideshow);

    // Spacer
    m_spacerTwo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addWidget(m_spacerTwo);

    // Zoom Original
    m_zoomOriginal->setIcon(QIcon("Images/zoom-original.png"));
    m_zoomOriginal->setText("Zoom to original");
    addAction(m_zoomOriginal);

    // Zoom Fit
    m_zoomFit->setIcon(QIcon("Images/zoom-fit.png"));
    m_zoomFit->setText("Zoom to fit window");
    addAction(m_zoomFit);

    // Separator
    addSeparator();

    // Fullscreen
    m_fullScreen->setIcon(QIcon("Images/fullscreen.png"));
    m_fullScreen->setText("Switch to fullscreen");
    addAction(m_fullScreen);
}

QAction* ToolBar::openFile()
{
    return (m_openFile);
}

QAction* ToolBar::zoomFit()
{
    return (m_zoomFit);
}

QAction* ToolBar::zoomOriginal()
{
    return (m_zoomOriginal);
}

QAction* ToolBar::fullscreen()
{
    return (m_fullScreen);
}

QAction* ToolBar::playSlideshow()
{
    return (m_playSlideshow);
}

QAction* ToolBar::saveFile()
{
    return (m_saveFile);
}

QAction* ToolBar::deleteFile()
{
    return (m_deleteFile);
}
