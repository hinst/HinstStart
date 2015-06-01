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
		if (role == Qt::DisplayRole)
		{
			result = fileListData->files[index.row()].fileName();
		}
	}
	return result;
}

void FileListViewModel::WriteLog(QString text) const
{
	qDebug() << text;
}
