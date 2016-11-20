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
    int size();

private:
    void setup();

    int m_index;
    QFileInfo m_currentFile;

signals:
    void updateTitleBar(QString string);
};