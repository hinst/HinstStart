#include "FileListView.h"

FileListView::FileListView(QWidget *parent) : QTableView(parent)
{

}

void FileListView::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
	{
		writeLog("Start");
		auto event = new QEvent(keyEnterEventType);
		QCoreApplication::postEvent(keyEventReceiver, event);
	}
	if (event->key() == Qt::Key_Down)
	{
		moveSelection(1);
	}
	if (event->key() == Qt::Key_Up)
	{
		moveSelection(-1);
	}
}

void FileListView::writeLog(QString text)
{
	CommonLog::write(QString("FileListView: ") + text);
}

void FileListView::moveSelection(int delta)
{
	auto selectedIndexes = this->selectionModel()->selection().indexes();
	if (selectedIndexes.count() > 0)
	{
		auto selectedIndex = selectedIndexes[0];
		auto newSelectedRowIndex = selectedIndex.row() + delta;
		if (0 <= newSelectedRowIndex && newSelectedRowIndex < this->model()->rowCount())
		{
			this->selectRow(newSelectedRowIndex);
		}
	}
}

