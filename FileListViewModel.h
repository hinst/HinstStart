#ifndef FILELISTVIEWMODEL_H
#define FILELISTVIEWMODEL_H

#include <QListView>
#include <QList>
#include "FileListData.h"

class FileListViewModel : public QAbstractListModel
{
public:
	FileListViewModel();
	int rowCount(const QModelIndex & parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	void setFileListData(FileListData *fileListData);
private:
	FileListData *fileListData;
	void writeLog(QString text) const;
};

#endif // FILELISTVIEWMODEL_H
