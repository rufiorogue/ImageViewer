#include "MainWindow.h"

#include "MainWindow/ImageView.h"
#include "MainWindow/StatusBar.h"
#include "MainWindow/ToolBar.h"
#include "MainWindow/Menu/Edit.h"
#include "MainWindow/Menu/File.h"
#include "MainWindow/Menu/View.h"

#include "File.h"
#include "Preferences.h"
#include "PreferencesDialog.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    m_file = new File();
    m_imageView = new ImageView(m_file, this);
    m_menuBar = menuBar();
    m_menuEdit = new Menu::Edit(this);
    m_menuFile = new Menu::File(this);
    m_menuView = new Menu::View(this);
    m_preferences = new Preferences(this);
    m_statusBar = new StatusBar(this);
    m_toolBar = new ToolBar(this);

    setup();
}

MainWindow::~MainWindow()
{
    m_preferences->save();

    delete m_file;
}

void MainWindow::setup()
{
    addToolBar(m_toolBar);
    setCentralWidget(m_imageView);
    setConnections();
    setMenu();
    setPreferences();
    setSize();
    setStatusBar(m_statusBar);
    setWindowIcon(QIcon("Images/application.svg"));
    setWindowTitle("Image Viewer");
}

void MainWindow::setSize()
{
    QRect screen = QApplication::desktop()->screenGeometry();
    int width = (int) (screen.width() / 100.0 * WIDTH);
    int height = (int) (screen.height() / 100.0 * HEIGHT);

    resize(width, height);
}

void MainWindow::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image",
        QString(), "Images (*.bmp *.jpg *.png)");
    if (fileName.isNull()) {
        return;
    }

    m_file->current(fileName);
    m_imageView->loadImage(fileName);
}

void MainWindow::setConnections()
{
    // File
    connect(m_file, &File::updateTitleBar, this, &MainWindow::updateTitleBar);

    // Menu -> Edit
    connect(m_menuEdit->preferences(), &QAction::triggered, this,
        &MainWindow::openPreferences);
    connect(m_menuEdit->sortByDate(), &QAction::triggered, this,
        &MainWindow::sortBy);
    connect(m_menuEdit->sortByFileName(), &QAction::triggered, this,
        &MainWindow::sortBy);

    // Menu -> File
    connect(m_menuFile->open(), &QAction::triggered, this,
        &MainWindow::openImage);
    connect(m_menuFile->quit(), &QAction::triggered, this, &MainWindow::close);

    // Menu -> View
    connect(m_menuView->fullscreen(), &QAction::triggered, this,
        &MainWindow::toggleFullscreen);
    connect(m_menuView->rotateLeft(), &QAction::triggered, m_imageView,
        &ImageView::rotateLeft);
    connect(m_menuView->rotateRight(), &QAction::triggered, m_imageView,
        &ImageView::rotateRight);
    connect(m_menuView->showMenuBar(), &QAction::triggered, this,
        &MainWindow::showMenuBar);
    connect(m_menuView->showStatusBar(), &QAction::triggered, this,
        &MainWindow::showStatusBar);
    connect(m_menuView->showToolBar(), &QAction::triggered, this,
        &MainWindow::showToolBar);
    connect(m_imageView, &ImageView::updateStatusBar, m_statusBar,
        &StatusBar::update);

    // ToolBar
    connect(m_toolBar->deleteFile(), &QAction::triggered, this,
        &MainWindow::deleteImage);
    connect(m_toolBar->fullscreen(), &QAction::triggered, this,
        &MainWindow::toggleFullscreen);
    connect(m_toolBar->nextFile(), &QAction::triggered, m_imageView,
        &ImageView::nextImage);
    connect(m_toolBar->openFile(), &QAction::triggered, this,
        &MainWindow::openImage);
    connect(m_toolBar->previousFile(), &QAction::triggered, m_imageView,
        &ImageView::previousImage);
    connect(m_toolBar->saveFile(), &QAction::triggered, this,
        &MainWindow::saveImage);
    connect(m_toolBar->zoomFit(), &QAction::triggered, m_imageView,
        &ImageView::zoomFit);
    connect(m_toolBar->zoomOriginal(), &QAction::triggered, m_imageView,
        &ImageView::zoomOriginal);
}

void MainWindow::openPreferences()
{
    PreferencesDialog preferences(m_preferences, this);
    preferences.load();

    if (preferences.exec()) {
        preferences.save();
        setPreferences();
    }
}

void MainWindow::setMenu()
{
    m_menuBar->addMenu(m_menuFile);
    m_menuBar->addMenu(m_menuEdit);
    m_menuBar->addMenu(m_menuView);
}

void MainWindow::setPreferences()
{
    // Menu
    bool showMenu = m_preferences->showMenu();
    m_menuView->showMenuBar()->setChecked(showMenu);
    (showMenu) ? m_menuBar->show() : m_menuBar->hide();

    QString sortBy = m_preferences->sortBy();
    if (sortBy == "date") {
        m_menuEdit->sortByDate()->setChecked(true);
        m_file->setSorting(QDir::Time);
    } else if (sortBy == "filename") {
        m_menuEdit->sortByFileName()->setChecked(true);
        m_file->setSorting(QDir::Name);
    }

    // Tool Bar
    bool showToolBar = m_preferences->showToolBar();
    m_menuView->showToolBar()->setChecked(showToolBar);
    (showToolBar) ? m_toolBar->show() : m_toolBar->hide();


    // Status Bar
    bool showStatusBar = m_preferences->showStatusBar();
    m_menuView->showStatusBar()->setChecked(showStatusBar);
    (showStatusBar) ? m_statusBar->show() : m_statusBar->hide();


    // Image View
    int zoomStep = m_preferences->zoomStep();
    m_imageView->setZoomStep(zoomStep);

    QString bgColorView = m_preferences->bgColorView();
    m_imageView->setBgColor(bgColorView);
}

void MainWindow::showToolBar(bool value)
{
    (value) ? m_toolBar->show() : m_toolBar->hide();
    m_menuView->showToolBar()->setChecked(value);
    m_preferences->setShowToolBar(value);
}

void MainWindow::showStatusBar(bool value)
{
    (value) ? m_statusBar->show() : m_statusBar->hide();
    m_menuView->showStatusBar()->setChecked(value);
    m_preferences->setShowStatusBar(value);

    if (value) {
        m_statusBar->update(m_imageView);
    }
}

void MainWindow::toggleFullscreen()
{
    if (!isFullScreen()) {
        m_menuBar->hide();
        m_statusBar->hide();
        m_toolBar->hide();
        showFullScreen();
    } else {
        if (m_menuView->showStatusBar()->isChecked()) {
            m_statusBar->show();
        }
        if (m_menuView->showToolBar()->isChecked()) {
            m_toolBar->show();
        }

        showNormal();
    }
}

void MainWindow::showMenuBar(bool value)
{
    (value) ? m_menuBar->show() : m_menuBar->hide();
    m_menuView->showMenuBar()->setChecked(value);
    m_preferences->setShowMenuBar(value);
}

void MainWindow::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Image",
        m_imageView->fileName(), "Images (*.bmp *.jpg *.png)");
    if (fileName.isNull()) {
        return;
    }

    m_imageView->saveImage(fileName);
}

void MainWindow::deleteImage()
{
    QFileInfo fileInfo(m_imageView->fileName());

    int answer = QMessageBox::question(this, QString(),
        "Are you sure you want to send image '" + fileInfo.fileName()
            + "' to trash?",
        QMessageBox::Cancel | QMessageBox::Ok);

    if (answer == QMessageBox::Ok) {
        QFile::remove(fileInfo.absoluteFilePath());
    }

    m_imageView->closeImage();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape) {
        if (isFullScreen()) {
            toggleFullscreen();
        }
    }

    QWidget::keyPressEvent(event);
}

void MainWindow::updateTitleBar(QString string)
{
    setWindowTitle("Image Viewer - " + string);
}

void MainWindow::sortBy()
{
    if (m_menuEdit->sortByDate()->isChecked()) {
        m_preferences->setSortBy("date");
    } else if (m_menuEdit->sortByFileName()->isChecked()) {
        m_preferences->setSortBy("filename");
    }

    setPreferences();
}
