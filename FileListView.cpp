#include "FileListView.h"

FileListView::FileListView(QWidget *parent) : QTableView(parent)
{

}

void FileListView::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Down)
	{

	}
}

