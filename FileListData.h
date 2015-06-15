#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <QDir>
#include <QList>
#include <QString>
#include <QDebug>
#include <QIcon>
#include <QFileIconProvider>
#include <QSharedPointer>
#include <QThread>
#include <memory>
#include <windows.h>
#include <QtWinExtras/QtWin>

const QString UserStartMenuSubPath("AppData/Roaming/Microsoft/Windows/Start Menu");
const QString CommonStartMenuPath("C:/ProgramData/Microsoft/Windows/Start Menu");

class FileListData
{
public:
	FileListData();
    QList<QFileInfo> files;
    QString userStartMenuPath;
    QString commonStartMenuPath;
	QList<QIcon> icons;
private:
	void load();
	void setPaths();
	void loadFiles(QString directoryPath);
	void loadFile(QFileInfo fileInfo);
	void WriteLog(QString text);
	QIcon loadIcon(QString filePath);
	void loadIcons();
};

#endif // DATACONTAINER_H
