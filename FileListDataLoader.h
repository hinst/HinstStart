#ifndef FILELISTDATALOADER_H
#define FILELISTDATALOADER_H

#include <memory>
#include <QObject>
#include <QEvent>
#include <QCoreApplication>
#include <QElapsedTimer>
#include "FileListData.h"

class FileListDataLoader : public QThread
{
	Q_OBJECT
public:
    void run() override;
    // Objet to notify when loading is completed;
    QObject* objectToNotifyWhenLoaded;
    // Send this event type when loading is compledted;
    QEvent::Type eventTypeToNotifyWhenLoaded;
	class ProgressEvent : public QEvent
    {
    public:
		enum SubType
		{
			FileAdded,
			IconLoaded,
			Finished
		};
		ProgressEvent(QEvent::Type eventType);
        std::shared_ptr<FileListData> fileListData;
		SubType subType;
		int count;
		QThread* thread;
    };
};

#endif // FILELISTDATALOADER_H
