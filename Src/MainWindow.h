#pragma once

#include <QMainWindow>
#include <QTimer>
#include <memory>

class File;
class Preferences;
class QLineEdit;


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString &initialImage, QWidget *parent = Q_NULLPTR);
    ~MainWindow();


private slots:
    void openImage();
    void saveImage();
    void saveImageAs();
    void deleteImage();
    void sortName();
    void sortDate();
    void sortAscending();
    void sortDescending();
    void fullscreen();
    void slideshow();
    void zoomFit(bool value);
    void options();
    void about();
    void fileChanged(const QString &fileName, const QImage &image);
    void zoomEditingFinished();

private:
    void setup();
    void setConnections();
    void setupMenu();
    void setupToolbar();
    void setPreferences();
    void setShortcuts();
    void openImageFilename(const QString& fileName);
    void slideshowStep();
    void updateToolbarBg(const QString &color);


    void resizeEvent(QResizeEvent *event);

private:
    Ui::MainWindow *ui;
    std::unique_ptr<File> m_file;
    std::unique_ptr<QTimer> m_timer;
    bool m_slideshowRunning;
    Preferences     *m_preferences;
    QAction         *m_actionFullscreen;
    QLineEdit       *m_editZoom;

};
