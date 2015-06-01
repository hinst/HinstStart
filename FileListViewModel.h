#ifndef FILELISTVIEWMODEL_H
#define FILELISTVIEWMODEL_H

#include <QListView>
#include "FileListData.h"

class FileListViewModel : public QAbstractListModel
{
public:
	FileListData *dataContainer;
	int rowCount(const QModelIndex & parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
private:
	void WriteLog(QString text) const;
};

#endif // FILELISTVIEWMODEL_H
