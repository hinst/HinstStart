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
	// Object which should be notified when loading is completed.
	QObject* progressEventReceiver;
	// Sends this event type to indicate loading progress.
	QEvent::Type loadedEventType;
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
