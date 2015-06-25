#include "FileListView.h"

FileListView::FileListView(QWidget *parent) : QTableView(parent)
{

}

void FileListView::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
	{
		auto event = new QEvent(keyEnterEventType);
		QCoreApplication::postEvent(keyEventReceiver, event);
	}
}

void FileListView::writeLog(QString text)
{
	CommonLog::Write(QString("FileListView: ") + text);
}

