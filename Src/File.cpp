#include "File.h"
#include <QImageReader>

QStringList File::supportedExtensions()
{
    QList<QByteArray> supportedFormats = QImageReader::supportedImageFormats();
    QStringList ret;
    std::transform(supportedFormats.begin(),
                   supportedFormats.end(),
                   std::back_inserter(ret),
                   [](const QByteArray& byteArray){return QString("*.")+QString(byteArray); });
    return ret;
}

File::File()
{
    setup();
}

File::~File()
{
}

void File::setup()
{
    setFilter(QDir::Files | QDir::NoDotAndDotDot);
    setNameFilters(supportedExtensions());
}

void File::current(QString fileName)
{
    m_currentFile = QFileInfo(fileName);
    setPath(m_currentFile.absolutePath());

    m_index = entryInfoList().indexOf(m_currentFile);

    emit selectionChanged(index(), size());
}

int File::size()
{
    return (entryInfoList().size());
}

int File::index()
{
    return (m_index + 1);
}

QString File::next()
{
    if (m_index + 1 >= size()) {
        return (QString());
    }

    QString fileName = entryInfoList().at(++m_index).absoluteFilePath();
    current(fileName);

    return (fileName);
}

QString File::previous()
{
    if (m_index - 1 < 0) {
        return (QString());
    }

    QString fileName = entryInfoList().at(--m_index).absoluteFilePath();
    current(fileName);

    return (fileName);
}

QString File::first()
{
    if (size() == 0) {
        return (QString());
    }

    m_index = 0;
    QString fileName = entryInfoList().at(m_index).absoluteFilePath();
    current(fileName);

    return (fileName);
}

QString File::last()
{
    if (size() == 0) {
        return (QString());
    }

    m_index = size() - 1;
    QString fileName = entryInfoList().at(m_index).absoluteFilePath();
    current(fileName);

    return (fileName);
}
