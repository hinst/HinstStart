#include "FileListViewModel.h"

int FileListViewModel::rowCount(const QModelIndex &parent) const
{
	return dataContainer->files.count();
}

QVariant FileListViewModel::data(const QModelIndex &index, int role) const
{
	QVariant result = QVariant::Invalid;
	if (role == Qt::DisplayRole)
	{
		result = dataContainer->files[index.row()].fileName();
	}
	return result;
}

void FileListViewModel::WriteLog(QString text) const
{
	qDebug() << text;
}
