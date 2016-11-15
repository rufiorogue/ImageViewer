#pragma once

#include <QGraphicsView>
#include <QMouseEvent>

class ImageView : public QGraphicsView {
    Q_OBJECT

public:
    ImageView(QWidget* parent = Q_NULLPTR);
    ~ImageView();

    QString& fileName();
    qreal zoom();

    void setZoomStep(int value);

    void loadImage(QString& fileName);
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
    QString m_fileName;

    QGraphicsScene* m_scene;

signals:
    void updateStatusBar(ImageView* imageView);
};