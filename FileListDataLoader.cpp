#include "FileListDataLoader.h"

void FileListDataLoader::run()
{
	std::shared_ptr<FileListData> fileListData(new FileListData());
    QElapsedTimer timer;
    timer.start();
	fileListData->fileAddedEventReceiver =
		[this, fileListData](int countOfFiles)
		{
			auto fileAddedEvent = new ProgressEvent(this->eventTypeToNotifyWhenLoaded);
			fileAddedEvent->subType = ProgressEvent::FileAdded;
			fileAddedEvent->count = countOfFiles;
			QCoreApplication::postEvent(this->objectToNotifyWhenLoaded, fileAddedEvent);
		};
	fileListData->iconLoadedEventReceiver =
		[this, fileListData](int countOfIcons)
		{
			auto fileAddedEvent = new ProgressEvent(this->eventTypeToNotifyWhenLoaded);
			fileAddedEvent->subType = ProgressEvent::IconLoaded;
			fileAddedEvent->fileListData = fileListData;
			fileAddedEvent->count = countOfIcons;
			QCoreApplication::postEvent(this->objectToNotifyWhenLoaded, fileAddedEvent);
		};
	fileListData->load();
    qDebug() << timer.elapsed();
    if (objectToNotifyWhenLoaded != nullptr)
    {
		auto loadedEvent = new ProgressEvent(this->eventTypeToNotifyWhenLoaded);
		loadedEvent->subType = ProgressEvent::Finished;
		loadedEvent->fileListData = fileListData;
        loadedEvent->thread = this;
        QCoreApplication::postEvent(objectToNotifyWhenLoaded, loadedEvent);
    }
}

FileListDataLoader::ProgressEvent::ProgressEvent(QEvent::Type eventType) : QEvent(eventType)
{
}
