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
	return 2;
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
				if (fileListData->icons.count() > 0)
				{
					result = fileListData->icons[rowIndex];
				}
			}
		}
		if (columnIndex == 1)
		{
			if (role == Qt::DisplayRole)
			{
				if (fileListData->files[rowIndex].isSymLink())
				{
					result = fileListData->files[rowIndex].symLinkTarget();
				}
				else
				{
					result = fileListData->files[rowIndex].absoluteDir().path();
				}
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

void FileListViewModel::setFileListData(std::shared_ptr<FileListData> fileListData)
{
	this->fileListData = fileListData;
}

void FileListViewModel::writeLog(QString text) const
{
	qDebug() << text;
}

