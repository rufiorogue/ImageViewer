#pragma once

#include <QGraphicsView>
#include <QMouseEvent>

#include <memory>

class File;
class QMovie;
class QGraphicsTextItem;

class ImageView : public QGraphicsView
{
    Q_OBJECT

public:
    ImageView(QWidget *parent = Q_NULLPTR);
    ~ImageView();

    const QString &fileName()const;
    QSize imageSize()const;


    /// @return zoom in percent
    qreal zoom()const;

    void setFileObject(File *file);
    void setBgColor(const QString &value);
    void setZoomFactor(const qreal f);
    void setZoomMin(const qreal value);
    void setZoomMax(const qreal value);

    void loadImage(const QString &fileName);
    void saveImage(const QString &fileName);
    void closeImage();

public slots:
    void nextImage();
    void previousImage();
    void firstImage();
    void lastImage();
    void rotateLeft();
    void rotateRight();
    void zoomOriginal();
    void zoomFit(bool value);
    void zoomIn(const QPoint &viewPoint);
    void zoomOut(const QPoint &viewPoint);
    void zoomArbitrary(const qreal &zoom);


private:
    void setup();
    void recalculate(qreal zoom = 1.0);
    void scaleAtPoint(const qreal &scale, const QPoint &viewPoint);

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void resizeEvent(QResizeEvent* event);

private:

    /// current zoom
    qreal m_zoom {1.0};

    /// zoomIn  = zoom / zoomFactor
    /// zoomOut = zoom * zoomFactor
    qreal m_zoomFactor {0.909};

    /// zoom is clamped to range [minZoom; maxZoom]
    qreal m_minZoom {0.05};
    qreal m_maxZoom {50.0};

    /// zoom-fit mode flag
    bool m_zoomFit {false};

    struct EditState
    {
        qreal rotationAngle {0.0};
    };

    /// Edits performed on the current image.
    /// Edits are applied on the copy of m_image upon saving
    EditState       m_editState;

    QString         m_fileName;
    QImage          m_image;
    std::unique_ptr<QMovie> m_gifMovie;
    File            *m_file{nullptr};
    QGraphicsScene  *m_scene{nullptr};
    QGraphicsTextItem *m_gtiNoImage{nullptr};

    void updateNoImageLabelTextColor();

signals:
    void zoomChanged(const qreal zoom);
    void fileChanged(const QString &fileName, const QImage &image);
    void zoomFitCanceled();
};


inline
void ImageView::setFileObject(File *file)
{
    m_file = file;
}


inline
QSize ImageView::imageSize()const
{
    return m_image.size();
}


inline
qreal ImageView::zoom() const
{
    return (qRound(m_zoom * 10000.0) / 100.0);
}

inline
const QString &ImageView::fileName() const
{
    return (m_fileName);
}

inline
void ImageView::setZoomFactor(const qreal value)
{
    m_zoomFactor = value;
}
inline
void ImageView::setZoomMin(const qreal value)
{
    m_minZoom = value;
}
inline
void ImageView::setZoomMax(const qreal value)
{
    m_maxZoom = value;
}

