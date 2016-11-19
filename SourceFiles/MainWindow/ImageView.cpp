#include "ImageView.h"

ImageView::ImageView(QWidget* parent)
    : QGraphicsView(parent)
{
    m_scene = new QGraphicsScene(this);

    setup();
}

ImageView::~ImageView()
{
}

void ImageView::loadImage(QString& fileName)
{
    if (!m_fileName.isNull()) {
        closeImage();
    }

    m_fileName = fileName;

    if (!m_image.load(fileName)) {
        return;
    }

    QPixmap pixmap;
    if (!pixmap.convertFromImage(m_image)) {
        return;
    }

    m_scene->clear();
    m_scene->addPixmap(pixmap);

    recalculate();

    emit updateStatusBar(this);
}

void ImageView::setup()
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setScene(m_scene);
    setStyleSheet("QGraphicsView { border: 0px; padding: 0px -4px -4px 0px; }");
    setTransformationAnchor(ViewportAnchor::AnchorUnderMouse);
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
}

void ImageView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MouseButton::LeftButton) {
        setDragMode(QGraphicsView::ScrollHandDrag);
    }

    QGraphicsView::mousePressEvent(event);
}

void ImageView::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MouseButton::LeftButton) {
        setDragMode(QGraphicsView::NoDrag);
    }

    QGraphicsView::mouseReleaseEvent(event);
}

void ImageView::setZoomStep(int value)
{
    m_zoomStep = (double) value / 100;
    m_zoomIn = (m_zoom + m_zoomStep) / m_zoom;
    m_zoomOut = (m_zoom - m_zoomStep) / m_zoom;
}

void ImageView::zoomIn()
{
    if (m_fileName.isNull()) {
        return;
    }

    if (qRound((m_zoom + m_zoomStep) * 100) > MAX_ZOOM) {
        return;
    }

    scale(m_zoomIn, m_zoomIn);

    m_zoom += m_zoomStep;
    m_zoomOut = 1 / m_zoomIn;
    m_zoomIn = (m_zoom + m_zoomStep) / m_zoom;

    emit updateStatusBar(this);
}

void ImageView::zoomOut()
{
    if (m_fileName.isNull()) {
        return;
    }

    if (qRound((m_zoom - m_zoomStep) * 100) < MIN_ZOOM) {
        return;
    }

    scale(m_zoomOut, m_zoomOut);

    m_zoom -= m_zoomStep;
    m_zoomIn = 1 / m_zoomOut;
    m_zoomOut = (m_zoom - m_zoomStep) / m_zoom;

    emit updateStatusBar(this);
}

void ImageView::wheelEvent(QWheelEvent* event)
{
    if (event->delta() > 0) {
        zoomIn();
    } else if (event->delta() < 0) {
        zoomOut();
    }
}

QString& ImageView::fileName()
{
    return (m_fileName);
}

qreal ImageView::zoom()
{
    return (qRound(m_zoom * 10000.0) / 100.0);
}

void ImageView::zoomFit()
{
    if (m_fileName.isNull()) {
        return;
    }

    fitInView(m_scene->sceneRect(), Qt::AspectRatioMode::KeepAspectRatio);
    recalculate((transform().m11()) ? transform().m11() : transform().m21());
    emit updateStatusBar(this);
}

void ImageView::zoomOriginal()
{
    if (m_fileName.isNull()) {
        return;
    }

    scale(1 / m_zoom, 1 / m_zoom);
    recalculate();
    emit updateStatusBar(this);
}

void ImageView::recalculate(double zoom)
{
    m_zoom = (zoom > 0) ? zoom : -zoom;
    m_zoomIn = (m_zoom + m_zoomStep) / m_zoom;
    m_zoomOut = (m_zoom - m_zoomStep) / m_zoom;
}

void ImageView::rotateLeft()
{
    rotate(-90);
}

void ImageView::rotateRight()
{
    rotate(90);
}

void ImageView::saveImage(QString& fileName)
{
    if (!m_image.save(fileName)) {
        return;
    }
}

void ImageView::closeImage()
{
    zoomOriginal();
    m_scene->clear();
    m_fileName = QString();
    emit updateStatusBar(this);
}

void ImageView::setBgColor(QString value)
{
    m_scene->setBackgroundBrush(QBrush(QColor(value)));
}
