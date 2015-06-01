#include "DataContainer.h"

DataContainer::DataContainer()
{

}

void DataContainer::setPaths()
{
    this->userStartMenuPath = QDir::homePath() + "/" + UserStartMenuSubPath;
	WriteLog("userStartMenuPath = '" + userStartMenuPath + "'");
    this->commonStartMenuPath = CommonStartMenuPath;
}

void DataContainer::load()
{
	this->files.clear();
    this->setPaths();
	this->loadFiles(this->userStartMenuPath);
}

void DataContainer::loadFiles(QString directoryPath)
{
	QDir qDirectory(directoryPath);
	auto files = qDirectory.entryInfoList();
	if (files.count() > 0)
	{
		for (int i = 0; i < files.count(); i++)
		{
			auto fileInfo = files[i];
			if ((fileInfo.fileName() != "..") && (fileInfo.fileName() != "."))
			{
				this->loadFile(fileInfo);
			}
		}
	}
}

void DataContainer::loadFile(QFileInfo fileInfo)
{
	if (fileInfo.isDir())
	{
		loadFiles(fileInfo.filePath());
	}
	else
	{
		this->files.append(fileInfo);
	}
}

void DataContainer::WriteLog(QString text)
{
	qDebug() << (QString("DataContainer") + text);
}

