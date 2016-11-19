#include "File.h"

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
    setNameFilters(QStringList({"*.bmp", "*.jpg", "*.png"}));
}

void File::current(QString fileName)
{
    m_currentFile = QFileInfo(fileName);
    setPath(m_currentFile.absolutePath());

    m_index = entryInfoList().indexOf(m_currentFile);

    emit updateTitleBar("[" + QString::number(index()) + "/"
        + QString::number(size()) + "]");
}

int File::size()
{
    return (entryInfoList().size());
}

int File::index()
{
    return (m_index + 1);
}
