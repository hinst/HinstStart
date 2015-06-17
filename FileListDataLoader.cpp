#include "FileListDataLoader.h"

FileListDataLoader::FileListDataLoader(QObject *parent) : QObject(parent)
{
}

QEvent::Type FileListDataLoader::pokeEventType()
{
	return (QEvent::Type)(QEvent::User + 1);
}

bool FileListDataLoader::event(QEvent *event)
{
	bool result = false;
	if (event->type() == pokeEventType())
	{
		load();
		result = true;
	}
	else
	{
		result = this->QObject::event(event);
	}
	return result;
}

void FileListDataLoader::load()
{
	std::shared_ptr<FileListData> fileListData(new FileListData());
	fileListData->load();
	this->fileListData = fileListData;
}

