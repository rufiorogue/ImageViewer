#pragma once

#include <QGraphicsView>
#include <QMouseEvent>

class File;

class ImageView : public QGraphicsView {
    Q_OBJECT

public:
    ImageView(File* file, QWidget* parent = Q_NULLPTR);
    ~ImageView();

    QString& fileName();
    QPoint resolution();
    qreal zoom();

    void setBgColor(QString value);
    void setZoomStep(int value);

    void closeImage();
    void loadImage(QString fileName);
    void nextImage();
    void previousImage();
    void saveImage(QString fileName);
    void rotateLeft();
    void rotateRight();
    void zoomFit();
    void zoomIn();
    void zoomOriginal();
    void zoomOut();

private:
    void setup();
    void recalculate(double zoom = 1.00);

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

    const double MIN_ZOOM = 5; // %
    const double MAX_ZOOM = 500; // %

    double m_zoom;
    double m_zoomIn;
    double m_zoomOut;
    double m_zoomStep;
    QImage m_image;
    QString m_fileName;

    File* m_file;
    QGraphicsScene* m_scene;

signals:
    void updateStatusBar(ImageView* imageView);
};