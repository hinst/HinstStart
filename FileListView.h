#ifndef FILELISTVIEW_H
#define FILELISTVIEW_H

#include <QTableWidget>
#include <QObject>

class FileListView : public QTableView
{
	Q_OBJECT
public:
	FileListView(QWidget *parent = nullptr);
};

#endif // FILELISTVIEW_H
