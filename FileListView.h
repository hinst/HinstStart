#ifndef FILELISTVIEW_H
#define FILELISTVIEW_H

#include <QTableWidget>
#include <QObject>
#include <QKeyEvent>
#include <QEvent>

class FileListView : public QTableView
{
	Q_OBJECT
public:
	QObject *keyEventReceiver;
	QEvent::Type keyDownEventType;
	FileListView(QWidget *parent = nullptr);
protected:
	void keyPressEvent(QKeyEvent *event) override;
};

#endif // FILELISTVIEW_H
