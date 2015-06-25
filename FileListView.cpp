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
		auto selectedIndexes = this->selectionModel()->selection().indexes();
		if (selectedIndexes.count() > 0)
		{
			auto selectedIndex = selectedIndexes[0];
			this->selectRow(selectedIndex.row() + 1);
		}
	}
}

void FileListView::writeLog(QString text)
{
	CommonLog::Write(QString("FileListView: ") + text);
}

