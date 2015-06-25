#include "FileListDataLoader.h"

void FileListDataLoader::run()
{
	std::shared_ptr<FileListData> fileListData(new FileListData());
    QElapsedTimer timer;
    timer.start();
	fileListData->fileAddedEventReceiver =
		[this, fileListData](int countOfFiles)
		{
			auto fileAddedEvent = new ProgressEvent(this->loadedEventType);
			fileAddedEvent->subType = ProgressEvent::FileAdded;
			fileAddedEvent->count = countOfFiles;
			QCoreApplication::postEvent(this->progressEventReceiver, fileAddedEvent);
		};
	fileListData->iconLoadedEventReceiver =
		[this, fileListData](int countOfIcons)
		{
			auto fileAddedEvent = new ProgressEvent(this->loadedEventType);
			fileAddedEvent->subType = ProgressEvent::IconLoaded;
			fileAddedEvent->fileListData = fileListData;
			fileAddedEvent->count = countOfIcons;
			QCoreApplication::postEvent(this->progressEventReceiver, fileAddedEvent);
		};
	fileListData->load();
    qDebug() << timer.elapsed();
    if (progressEventReceiver != nullptr)
    {
		auto loadedEvent = new ProgressEvent(this->loadedEventType);
		loadedEvent->subType = ProgressEvent::Finished;
		loadedEvent->fileListData = fileListData;
        loadedEvent->thread = this;
        QCoreApplication::postEvent(progressEventReceiver, loadedEvent);
    }
}

FileListDataLoader::ProgressEvent::ProgressEvent(QEvent::Type eventType) : QEvent(eventType)
{
}
