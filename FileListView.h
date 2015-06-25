#ifndef FILELISTVIEW_H
#define FILELISTVIEW_H

#include <QTableWidget>
#include <QObject>
#include <QKeyEvent>
#include <QEvent>
#include <QCoreApplication>
#include "CommonLog.h"

class FileListView : public QTableView
{
	Q_OBJECT
public:
	QObject *keyEventReceiver;
	QEvent::Type keyEnterEventType;
	FileListView(QWidget *parent = nullptr);
protected:
	void keyPressEvent(QKeyEvent *event) override;
private:
	void writeLog(QString text);
};

#endif // FILELISTVIEW_H
