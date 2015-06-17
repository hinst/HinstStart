#ifndef FILELISTDATALOADER_H
#define FILELISTDATALOADER_H

#include <QObject>
#include <QEvent>
#include <memory>
#include "FileListData.h"

class FileListDataLoader : public QObject
{
	Q_OBJECT
public:
	explicit FileListDataLoader(QObject *parent = 0);
	std::shared_ptr<FileListData> fileListData;
	static QEvent::Type pokeEventType();
	bool event(QEvent *event) override;
	void load();
};

#endif // FILELISTDATALOADER_H
