#include "FileListViewModel.h"

FileListViewModel::FileListViewModel()
	: QAbstractListModel()
{
	fileListData = nullptr;
}

int FileListViewModel::rowCount(const QModelIndex &parent) const
{
	if (fileListData != nullptr)
	{
		return fileListData->files.count();
	}
	else
	{
		return 0;
	}
}

QVariant FileListViewModel::data(const QModelIndex &index, int role) const
{
	QVariant result = QVariant::Invalid;
	if (fileListData != nullptr)
	{
		auto itemIndex = index.row();
		if (role == Qt::DisplayRole)
		{
			result = fileListData->files[itemIndex].fileName();
		}
		else if (role == Qt::DecorationRole)
		{
			result = fileListData->icons[itemIndex];
		}
	}
	return result;
}

void FileListViewModel::setFileListData(FileListData *fileListData)
{
	this->fileListData = fileListData;
}

void FileListViewModel::writeLog(QString text) const
{
	qDebug() << text;
}

