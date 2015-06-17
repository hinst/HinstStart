#include "FileListDataLoader.h"

void FileListDataLoader::run()
{
	std::shared_ptr<FileListData> fileListData(new FileListData());
    QElapsedTimer timer;
    timer.start();
	fileListData->load();
    qDebug() << timer.elapsed();
    if (objectToNotifyWhenLoaded != nullptr)
    {
        auto loadedEvent = new LoadedEvent(this->eventTypeToNotifyWhenLoaded);
        loadedEvent->fileListData = fileListData;
        loadedEvent->thread = this;
        QCoreApplication::postEvent(objectToNotifyWhenLoaded, loadedEvent);
    }
}



FileListDataLoader::LoadedEvent::LoadedEvent(QEvent::Type eventType) : QEvent(eventType)
{
}
