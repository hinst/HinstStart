#include "FileListViewModel.h"

FileListViewModel::FileListViewModel()
	: QAbstractTableModel()
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

int FileListViewModel::columnCount(const QModelIndex &parent) const
{
	return 1;
}

QVariant FileListViewModel::data(const QModelIndex &index, int role) const
{
	QVariant result = QVariant::Invalid;
	if (fileListData != nullptr)
	{
		auto rowIndex = index.row();
		auto columnIndex = index.column();
		if (columnIndex == 0)
		{
			if (role == Qt::DisplayRole)
			{
				result = fileListData->files[rowIndex].fileName();
			}
			else if (role == Qt::DecorationRole)
			{
				result = fileListData->icons[rowIndex];
			}
		}
	}
	return result;
}

QVariant FileListViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	QVariant result = QVariant::Invalid;
	if (orientation == Qt::Horizontal)
	{
		if (section == 0)
		{
			if (role == Qt::DisplayRole)
			{
				result = "Name";
			}
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

