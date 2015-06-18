#ifndef STARTERWINDOW_H
#define STARTERWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTableView>
#include <QLayout>
#include <QLineEdit>
#include <QThread>
#include <QSortFilterProxyModel>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QEvent>
#include <QLabel>
#include "FileListData.h"
#include "FileListViewModel.h"
#include "CommonUI.h"
#include "FileListDataLoader.h"
#include "CommonLog.h"

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
	QTableView *fileListView;
	FileListViewModel *fileListViewModel;
	QSortFilterProxyModel *sortFilterProxyModel;
	QWidget *rootWidget;
	QVBoxLayout *rootLayout;
	QHBoxLayout *progressLayout;
	QWidget *progressWidget;
	QLabel *progressLabel;
	QLineEdit* searchLineEdit;
	void WriteLog(QString text);
    static QEvent::Type fileListDataLoadedEventType();
    void receiveFileList(std::shared_ptr<FileListData> fileListData);
};

#endif // STARTERWINDOW_H
