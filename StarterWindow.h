#ifndef STARTERWINDOW_H
#define STARTERWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTableView>
#include <QDebug>
#include <QLayout>
#include <QLineEdit>
#include <QThread>
#include <QSortFilterProxyModel>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QEvent>
#include "FileListData.h"
#include "FileListViewModel.h"
#include "CommonUI.h"

class StarterWindow : public QMainWindow
{
    Q_OBJECT
public:
    StarterWindow(QWidget *parent = 0);
    ~StarterWindow();
	void loadFileList();
	/** Clears model of fileListView; deletes fileListViewModel, sortFilterProxyModel. */
	void unloadFileList();
public slots:
	void receiveSearchLineEditTextChanged(const QString &text);
protected:
    bool event(QEvent *event) override;
private:
	FileListData *fileListData;
	QTableView* fileListView;
	FileListViewModel* fileListViewModel;
	QSortFilterProxyModel *sortFilterProxyModel;
	QWidget *rootWidget;
	QVBoxLayout* rootLayout;
	QLineEdit* searchLineEdit;
	void WriteLog(QString text);
    QEvent::Type fileListDataLoadedEventType();
};

#endif // STARTERWINDOW_H
