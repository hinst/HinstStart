#include "FileListView.h"

FileListView::FileListView(QWidget *parent) : QTableView(parent)
{

}

void FileListView::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
	{
		if (keyEventReceiver != nullptr)
		{
			auto event = new QEvent(keyEnterEventType);
			QCoreApplication::postEvent(keyEventReceiver, event);
		}
	}
	else if (event->key() == Qt::Key_Down)
	{
		moveSelection(1);
	}
	else if (event->key() == Qt::Key_Up)
	{
		auto moved = moveSelection(-1);
		if (false == moved)
		{
			if (keyEventReceiver != nullptr)
			{
				auto event = new QEvent(keyUpEventType);
				QCoreApplication::postEvent(keyEventReceiver, event);
			}
		}
	}
	else
	{
		this->QTableView::keyPressEvent(event);
	}
}

void FileListView::writeLog(QString text)
{
	CommonLog::write(QString("FileListView: ") + text);
}

bool FileListView::moveSelection(int delta)
{
	auto result = false;
	auto selectedIndexes = this->selectionModel()->selection().indexes();
	if (selectedIndexes.count() > 0)
	{
		auto selectedIndex = selectedIndexes[0];
		auto newSelectedRowIndex = selectedIndex.row() + delta;
		if (0 <= newSelectedRowIndex && newSelectedRowIndex < this->model()->rowCount())
		{
			this->selectRow(newSelectedRowIndex);
			result = true;
		}
	}
	return result;
}

