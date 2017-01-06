#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "MainWindow/ImageView.h"

#include "File.h"
#include "Preferences.h"
#include "PreferencesDialog.h"
#include "AboutDialog.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QToolBar>
#include <QLineEdit>
#include <QDebug>



MainWindow::MainWindow(const QString &initialImage, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_file(new File)
    , m_timer(new QTimer)
    , m_slideshowRunning(false)
{
    ui->setupUi(this);

    m_preferences = new Preferences(this);
    m_actionFullscreen = new QAction(this);

    ui->imageView->setFileObject(m_file.get());
    ui->imageView->installEventFilter(this);

    setup();

    openImageFilename(initialImage);
}

MainWindow::~MainWindow()
{
    m_preferences->save();

    delete ui;
}

void MainWindow::setup()
{
    setWindowIcon(QIcon::fromTheme("image-viewer"));
    setupMenu();
    setupToolbar();
    setShortcuts();
    setConnections();
    setPreferences();
}

void MainWindow::setupMenu()
{
    auto agSortOrder = new QActionGroup(this);
    agSortOrder->addAction(ui->actionSortAscending);
    agSortOrder->addAction(ui->actionSortDescending);

    auto agSortCriteria = new QActionGroup(this);
    agSortCriteria->addAction(ui->actionSortName);
    agSortCriteria->addAction(ui->actionSortDate);
}

void MainWindow::setupToolbar()
{
    m_editZoom = new QLineEdit(ui->toolBar);
    m_editZoom->setMaximumWidth(m_editZoom->fontMetrics().width("0000.00%")+10);
    QAction *actionEditZoom = ui->toolBar->insertWidget(ui->actionZoomOriginal, m_editZoom);

    QWidget *spacer1 = new QWidget(ui->toolBar);
    spacer1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->toolBar->insertWidget(actionEditZoom, spacer1);

    QWidget *spacer2 = new QWidget(ui->toolBar);
    spacer2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->toolBar->addWidget(spacer2);
}

void MainWindow::setShortcuts()
{
    m_actionFullscreen->setShortcut(Qt::Key_Escape);

    // these actions must be added to the MainWindow
    // otherwise they are not triggered in fullscreen mode.
    QList<QAction*> actions{
        ui->actionFirstImage,
        ui->actionLastImage,
        ui->actionNextImage,
        ui->actionPreviousImage,
        ui->actionSlideshow,
        ui->actionZoomFit,
        ui->actionZoomOriginal,
        m_actionFullscreen,
    };
    addActions(actions);
}

void MainWindow::setConnections()
{
    // slideshow timer
    connect(m_timer.get(), &QTimer::timeout, this, &MainWindow::slideshowStep);

    // exits fullscreen mode
    connect(m_actionFullscreen, &QAction::triggered, [=] {
        if (isFullScreen())
        {
            fullscreen();
        }});


    connect(ui->imageView, &ImageView::zoomChanged, [=]() {
        m_editZoom->setText(QString::number(ui->imageView->zoom())+"%" ); } ) ;

    connect(ui->imageView, &ImageView::zoomFitCanceled, [=] {
        ui->actionZoomFit->setChecked(false); });

    connect(ui->actionZoomFit, &QAction::toggled, m_preferences,  &Preferences::set_zoomFit);

    connect(m_editZoom, &QLineEdit::editingFinished, [=]{
        QString percentStr = m_editZoom->text();
        qreal zoom = percentStr.left(percentStr.size()-1).toDouble()*0.01;
        ui->imageView->zoomArbitrary(zoom); } );
}


void MainWindow::options()
{
//    PreferencesDialog preferences(m_preferences, this);
//    preferences.load();

//    if (preferences.exec()) {
//        preferences.save();
//        setPreferences();
//    }
}

void MainWindow::about()
{
    AboutDialog dialog(this);
    dialog.exec();
}


void MainWindow::setPreferences()
{
    resize(m_preferences->windowSize());


    const QString &sortCriteria = m_preferences->sortCriteria();
    if (sortCriteria == "date") {
        ui->actionSortDate->setChecked(true);
        //ui->actionSortName->setChecked(false);
        m_file->setSorting(QDir::Time);
    } else if (sortCriteria == "filename") {
        //ui->actionSortDate->setChecked(false);
        ui->actionSortName->setChecked(true);
        m_file->setSorting(QDir::Name);
    }

    const QString &sortOrder = m_preferences->sortOrder();
    if (sortOrder == "ascending") {
        ui->actionSortAscending->setChecked(true);
        //ui->actionSortDescending->setChecked(false);
        m_file->setSorting(m_file->sorting() & ~QDir::Reversed);
    } else if (sortOrder == "descending") {
        //ui->actionSortAscending->setChecked(false);
        ui->actionSortDescending->setChecked(true);
        m_file->setSorting(m_file->sorting() | QDir::Reversed);
    }


    const QString &bgColorNormal = m_preferences->bgColorNormal();
    ui->imageView->setBgColor(bgColorNormal);
    updateToolbarBg(bgColorNormal);

    m_timer->setInterval(m_preferences->timeout() * 1000);

    //ui->imageView->setZoomStep( m_preferences->zoomStep());


    ui->actionZoomFit->setChecked(m_preferences->zoomFit());
    ui->imageView->zoomFit(m_preferences->zoomFit());
}



void MainWindow::openImage()
{
    const QString filter = "Images (" + File::supportedExtensions().join(" ") + ")";
    openImageFilename(QFileDialog::getOpenFileName(this, "Open Image",
                                                   QString(),
                                                   filter));
}


void MainWindow::openImageFilename(const QString& fileName)
{
    if (!fileName.isNull())
    {
        m_file->current(fileName);
        ui->imageView->loadImage(fileName);
    }
}

void MainWindow::saveImage()
{
    ui->imageView->saveImage(QString());
}


void MainWindow::saveImageAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Image",
        ui->imageView->fileName(), "Images (*.bmp *.jpg *.png)");
    if (fileName.isNull()) {
        return;
    }

    ui->imageView->saveImage(fileName);
}

void MainWindow::deleteImage()
{
    QFileInfo fileInfo(ui->imageView->fileName());

    int answer = QMessageBox::question(this, QString(),
        "Are you sure you want to send image '" + fileInfo.fileName()
            + "' to trash?",
        QMessageBox::Cancel | QMessageBox::Ok);

    if (answer == QMessageBox::Ok) {
        QFile::remove(fileInfo.absoluteFilePath());
        ui->imageView->closeImage();

        // try to switch to next image
        ui->imageView->nextImage();
    }
}



void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_preferences->set_windowSize(event->size());
}


void MainWindow::sortName()
{
    m_preferences->set_sortCriteria("filename");
    setPreferences();
}

void MainWindow::sortDate()
{
    m_preferences->set_sortCriteria("date");
    setPreferences();
}

void MainWindow::sortAscending()
{
    m_preferences->set_sortOrder("ascending");
    setPreferences();
}

void MainWindow::sortDescending()
{
    m_preferences->set_sortOrder("descending");
    setPreferences();
}


void MainWindow::slideshow()
{
    if (m_slideshowRunning)
    {
        m_timer->stop();
    }
    else
    {
        m_timer->start();
    }

    m_slideshowRunning = !m_slideshowRunning;

    ui->actionSlideshow->setIcon(QIcon::fromTheme(m_slideshowRunning ? "media-playback-stop" : "media-playback-start"));

}


void MainWindow::fullscreen()
{
    if (!isFullScreen())
    {
        ui->menuBar->hide();
        ui->toolBar->hide();

        showFullScreen();

        ui->imageView->setBgColor(m_preferences->bgColorFullscreen());
        updateToolbarBg(m_preferences->bgColorFullscreen());
    }
    else
    {
        ui->menuBar->show();
        ui->toolBar->show();

        showNormal();

        ui->imageView->setBgColor(m_preferences->bgColorNormal());
        updateToolbarBg(m_preferences->bgColorNormal());
    }
}


void MainWindow::zoomFit(bool value)
{
    m_preferences->set_zoomFit(value);
}

void MainWindow::slideshowStep()
{
    ui->imageView->nextImage();
}

void MainWindow::updateToolbarBg(const QString &color)
{
    ui->toolBar->setStyleSheet("QToolBar { border: 0px; padding: 10px; background-color: " + color + "; }");
}


void MainWindow::fileChanged(const QString &fileName, const QImage &image)
{
    QString title;

    if (fileName.isNull())
    {
        title = tr("Image Viewer");
    }
    else
    {
        QFileInfo fileInfo(fileName);
        title.sprintf("[%d/%d] %s (%dx%d) - %s",
                      m_file->index(),
                      m_file->size(),
                      fileInfo.fileName().toUtf8().data(),
                      image.width(),
                      image.height(),
                      tr("Image Viewer").toUtf8().data()
                      );
    }
    qDebug() << "set title to:" << title;
    setWindowTitle(title);
}



