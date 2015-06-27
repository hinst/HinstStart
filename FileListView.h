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
	// Delta should be +1 for down key, -1 for up key.
	void moveSelection(int delta);
};

#endif // FILELISTVIEW_H
