#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <memory>
#include <functional>
#include <QDir>
#include <QList>
#include <QString>
#include <QDebug>
#include <QIcon>
#include <QFileIconProvider>
#include <QSharedPointer>
#include <QThread>
#include <windows.h>
#include <QtWinExtras/QtWin>
#include "CommonLog.h"

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
	void load();
	// Progress reporting
	std::function<void(int countOfFiles)> fileAddedEventReceiver;
	std::function<void(int countOfIcons)> iconLoadedEventReceiver;
	~FileListData();
	void burnIcon(int index);
private:
	HICON *hicons;
	void setPaths();
	void loadFiles(QString directoryPath);
	void loadFile(QFileInfo fileInfo);
	void WriteLog(QString text);
	HICON loadHIcon(QString filePath);
	void loadHIcons();
	void releaseHIcons();
};

#endif // DATACONTAINER_H
