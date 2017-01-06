#pragma once

#include <QDir>

class File : public QObject, public QDir {
    Q_OBJECT

public:
    File();
    ~File();

    void current(QString fileName);
    int index();
    QString next();
    QString previous();
    QString first();
    QString last();
    int size();

    static QStringList supportedExtensions();

private:
    void setup();

    int m_index;
    QFileInfo m_currentFile;

signals:
    void selectionChanged(const int position, const int size);
};
