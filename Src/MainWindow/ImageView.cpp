#include "ImageView.h"
#include "../File.h"
#include <QMovie>
#include <QLabel>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>


namespace
{
    /// @return true if file is an animated GIF
    /// @return false if file is not an animated GIF or could not be opened
    bool isAnimatedGIF(const QString &fileName)
    {
        QImageReader reader(fileName);
        return reader.supportsAnimation() && (reader.imageCount() > 1);
    }
}

ImageView::ImageView( QWidget* parent)
    : QGraphicsView(parent)
{
    m_scene = new QGraphicsScene(this);

    setup();
}

ImageView::~ImageView()
{
}


void ImageView::setup()
{
    setScene(m_scene);
    setStyleSheet("QGraphicsView { border: 0px; padding: 0px -4px -4px 0px }");
    setTransformationAnchor(ViewportAnchor::NoAnchor);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

void ImageView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton) {
        setDragMode(QGraphicsView::ScrollHandDrag);
    }

    QGraphicsView::mousePressEvent(event);
}

void ImageView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton) {
        setDragMode(QGraphicsView::NoDrag);
    }

    QGraphicsView::mouseReleaseEvent(event);
}


namespace
{
    qreal clamp(const qreal &value, const qreal &minimum, const qreal &maximum)
    {
        return qMax(minimum, qMin(value, maximum));
    }

    bool qrealEq(const qreal &a, const qreal &b)
    {
        return qAbs(a - b) < 0.0001;
    }
}

void ImageView::scaleAtPoint(const qreal &scaleFactor, const QPoint &viewPoint)
{
    const QPointF scenePoint1 = mapToScene(viewPoint);
    scale(scaleFactor, scaleFactor);
    const QPointF scenePoint2 = mapToScene(viewPoint);

    // calculate such coordinate to center on so that scenePoint2 becomes equal to scenePoint1
    // after the view is scrolled.

    // current view center in scene coordinates
    const QPointF sceneCenterOfView = mapToScene(rect().center());

    // difference between scene coordinate of point under the mouse before scale and after scale
    const QPointF d = scenePoint2 - scenePoint1;

    centerOn(sceneCenterOfView - d);
}


void ImageView::zoomIn(const QPoint &viewPoint)
{
    if (m_image.isNull()) {
        return;
    }

    const qreal nextZoom =  clamp(m_zoom / m_zoomFactor, m_minZoom, m_maxZoom);

    if (!qrealEq(m_zoom, nextZoom))
    {
        scaleAtPoint(nextZoom / m_zoom, viewPoint);
        recalculate(nextZoom);

        emit zoomChanged(zoom());
        emit zoomFitCanceled();
    }
}

void ImageView::zoomOut(const QPoint &viewPoint)
{
    if (m_image.isNull()) {
        return;
    }

    const qreal nextZoom =  clamp(m_zoom * m_zoomFactor, m_minZoom, m_maxZoom);

    if (!qrealEq(m_zoom, nextZoom))
    {
        scaleAtPoint(nextZoom / m_zoom, viewPoint);
        recalculate(nextZoom);

        emit zoomChanged(zoom());
        emit zoomFitCanceled();
    }
}

void ImageView::zoomArbitrary(const qreal &zoomValue)
{
    if (m_image.isNull()) {
        return;
    }

    const qreal nextZoom =  clamp(zoomValue, m_minZoom, m_maxZoom);

    if (!qrealEq(m_zoom, nextZoom))
    {
        scale(nextZoom / m_zoom, nextZoom / m_zoom);
        recalculate(nextZoom);

        emit zoomChanged(zoom());
        emit zoomFitCanceled();
    }
}


void ImageView::zoomFit(bool value)
{
    m_zoomFit = value;

    // update zoom of an image if we are already displaying one
    if ((!m_image.isNull()) && value)
    {
        const qreal imageW = m_image.width();
        const qreal imageH = m_image.height();
        const qreal vpW = width();
        const qreal vpH = height();

        const qreal hfactor = vpW / imageW;
        const qreal vfactor = vpH / imageH;

        // ensure factor is < 1.0 so that we only scale down
        const qreal factor = qMin(1.0, qMin(hfactor, vfactor));

        //qDebug()<< "zoom fit: factor=" << factor << " ";

        resetTransform();
        scale(factor, factor);
        recalculate(factor);

        emit zoomChanged(zoom());
    }
}

void ImageView::zoomOriginal()
{
    if (!m_fileName.isNull())
    {
        scale(1 / m_zoom, 1 / m_zoom);
        recalculate();

        emit zoomChanged(zoom());
        emit zoomFitCanceled();
    }
}

void ImageView::recalculate(double zoom)
{
    m_zoom = qAbs(zoom);
}


void ImageView::wheelEvent(QWheelEvent* event)
{
//    qDebug()<<"wheel delta"<<event->delta();
    if (event->delta() > 0)
    {
        zoomIn(event->pos());
    }
    else if (event->delta() < 0)
    {
        zoomOut(event->pos());
    }
}

void ImageView::resizeEvent(QResizeEvent */*event*/)
{
    if (!m_image.isNull())
    {
        setSceneRect(m_image.rect());

        if (m_zoomFit)
        {
            zoomFit(true);
        }
    }
    else
    {
        // even if no image is loaded, still update scene viewport
        // because we are displaying "no image" label there which must be centered
        setSceneRect(m_scene->itemsBoundingRect());
    }

}


void ImageView::rotateLeft()
{
    rotate(-90);
    m_editState.rotationAngle -= 90.0;
}

void ImageView::rotateRight()
{
    rotate(90);
    m_editState.rotationAngle += 90.0;
}


void ImageView::updateNoImageLabelTextColor()
{
    if (m_gtiNoImage)
    {
        QColor bg(m_scene->backgroundBrush().color());
        m_gtiNoImage->setDefaultTextColor(QColor( bg.lightnessF() > 0.5 ? "#cccccc" : "#555555"  ));
    }
}

void ImageView::loadImage(const QString &fileName)
{
    if (fileName.isNull()) {
        return;
    }

//    if (!m_fileName.isNull()) {
//        closeImage();
//    }

    m_fileName = fileName;


    m_scene->clear();
    QPixmap pixmap;
    if (m_image.load(fileName) && pixmap.convertFromImage(m_image))
    {
        if (isAnimatedGIF(fileName))
        {
            m_gifMovie.reset(new QMovie(fileName));
            m_gifMovie->start();

            QLabel *processLabel = new QLabel;
            processLabel->setMovie(m_gifMovie.get());

            m_scene->addWidget(processLabel);
        }
        else
        {
            auto item = m_scene->addPixmap(pixmap);
            item->setTransformationMode(Qt::SmoothTransformation);
        }
        m_scene->setSceneRect(m_image.rect());
        setSceneRect(m_image.rect());
        qDebug() << "scene rect: " << m_scene->sceneRect();
        m_gtiNoImage = Q_NULLPTR;

        m_zoomFit ? zoomFit(true) : zoomOriginal();
    }
    else
    {
        // this item is saved to a variable because we might need to update the label's color
        // when background color is changed by the user
        m_gtiNoImage  = m_scene->addText("Image failed to load", QFont("Sans", 40 ));

        updateNoImageLabelTextColor();

        setSceneRect(m_scene->itemsBoundingRect());
        resetTransform();
    }

    // reset edits
    m_editState = EditState();

    emit fileChanged(fileName, m_image);
}

void ImageView::saveImage(const QString &fileName)
{
    if (!m_image.isNull())
    {
        // if fileName is null, overwrite current file.
        const QString newFileName = fileName.isNull() ? m_fileName : fileName;

        // apply rotation to the copy of m_image
        QMatrix m;
        m.rotate(m_editState.rotationAngle);
        const QImage imageTmp = m_image.transformed(m, Qt::SmoothTransformation);
        // write the copy
        imageTmp.save(newFileName);
    }
}

void ImageView::closeImage()
{
    m_scene->clear();
    m_fileName = QString();
    emit fileChanged(QString(), QImage());
}

void ImageView::setBgColor(const QString &value)
{
    m_scene->setBackgroundBrush(QBrush(QColor(value)));
    updateNoImageLabelTextColor();
}

void ImageView::nextImage()
{
    loadImage(m_file->next());
}

void ImageView::previousImage()
{
    loadImage(m_file->previous());
}

void ImageView::firstImage()
{
    loadImage(m_file->first());
}

void ImageView::lastImage()
{
    loadImage(m_file->last());
}
