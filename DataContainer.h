#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <QDir>
#include <QList>
#include <QString>
#include <QDebug>

const QString UserStartMenuSubPath("AppData/Roaming/Microsoft/Windows/Start Menu");
const QString CommonStartMenuPath("C:/ProgramData/Microsoft/Windows/Start Menu");

class DataContainer
{
public:
    DataContainer();
    QList<QFileInfo> files;
    QString userStartMenuPath;
    QString commonStartMenuPath;
    void load();
    void loadFiles(QString directory);
private:
    void setPaths();
};

#endif // DATACONTAINER_H
