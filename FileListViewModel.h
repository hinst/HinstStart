#ifndef FILELISTVIEWMODEL_H
#define FILELISTVIEWMODEL_H

#include <QListView>
#include "FileListData.h"

class FileListViewModel : public QAbstractListModel
{
public:
	FileListViewModel();
	int rowCount(const QModelIndex & parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	FileListData *fileListData;
private:
	void WriteLog(QString text) const;
};

#endif // FILELISTVIEWMODEL_H
