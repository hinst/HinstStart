#ifndef SEARCHFILELISTLINEEDIT_H
#define SEARCHFILELISTLINEEDIT_H

#include <QObject>
#include <QLineEdit>
#include <QKeyEvent>
#include <QCoreApplication>

class SearchFileListLineEdit : public QLineEdit
{
	Q_OBJECT
public:
	SearchFileListLineEdit(QWidget *parent = 0);
	QObject *keyEventReceiver;
	QEvent::Type keyDownEventType;
protected:
	void keyPressEvent(QKeyEvent *event) override;
};

#endif // SEARCHFILELISTLINEEDIT_H
