#include "FileListDataLoader.h"

void FileListDataLoader::run()
{
	std::shared_ptr<FileListData> fileListData(new FileListData());
    QElapsedTimer timer;
    timer.start();
	fileListData->fileAddedEventReceiver =
		[this, fileListData](int n)
		{
			auto fileAddedEvent = new ProgressEvent(this->eventTypeToNotifyWhenLoaded);
			fileAddedEvent->subType = ProgressEvent::FileAdded;
			fileAddedEvent->fileListData = fileListData;
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
