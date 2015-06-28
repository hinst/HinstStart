#include "SearchFileListLineEdit.h"

SearchFileListLineEdit::SearchFileListLineEdit(QWidget *parent) : QLineEdit(parent)
{

}

void SearchFileListLineEdit::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Down)
	{
		auto event = new QEvent(keyDownEventType);
		QCoreApplication::postEvent(keyEventReceiver, event);
	}
	else
	{
		this->QLineEdit::keyPressEvent(event);
	}
}

