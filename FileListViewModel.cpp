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
				if (rowIndex < fileListData->icons.count())
				{
					result = fileListData->icons[rowIndex];
				}
			}
		}
		if (columnIndex == 1)
		{
			result = this->dataFilePath(index, role);
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
		if (section == 1)
		{
			if (role == Qt::DisplayRole)
			{
				result = "Path";
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

QString FileListViewModel::dataFilePath(const QModelIndex &index, int role) const
{
	QString filePath;
	auto rowIndex = index.row();
	if (role == Qt::DisplayRole)
	{
		if (fileListData->files[rowIndex].isSymLink())
		{
			filePath = fileListData->files[rowIndex].symLinkTarget();
		}
		else
		{
			filePath = fileListData->files[rowIndex].absoluteDir().path();
		}
	}
	filePath = filePath.replace('/', '\\');
	return filePath;
}

void FileListViewModel::notifyIconChanged(int rowIndex)
{
	auto index = createIndex(rowIndex, 0, nullptr);
	QVector<int> roles({Qt::DecorationRole});
	emit dataChanged(index, index, roles);
}

