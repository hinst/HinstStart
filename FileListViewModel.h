#ifndef FILELISTVIEWMODEL_H
#define FILELISTVIEWMODEL_H

#include <QTableView>
#include <QList>
#include "FileListData.h"

class FileListViewModel : public QAbstractTableModel
{
public:
	FileListViewModel();
	int rowCount(const QModelIndex & parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void setFileListData(std::shared_ptr<FileListData> fileListData);
private:
    std::shared_ptr<FileListData> fileListData;
	void writeLog(QString text) const;
};

#endif // FILELISTVIEWMODEL_H
