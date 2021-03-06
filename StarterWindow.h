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
#include <QProgressBar>
#include <QFrame>
#include <QDesktopServices>
#include <QUrl>
#include "FileListData.h"
#include "FileListViewModel.h"
#include "CommonUI.h"
#include "FileListDataLoader.h"
#include "CommonLog.h"
#include "ImprovedSortFilterProxyModel.h"
#include "FileListView.h"
#include "SearchFileListLineEdit.h"

class StarterWindow : public QMainWindow
{
    Q_OBJECT
public:
    StarterWindow(QWidget *parent = 0);
	void loadFileList();
	// Clears model of fileListView; deletes fileListViewModel, sortFilterProxyModel
	void unloadFileList();
	~StarterWindow();
public slots:
	void receiveSearchLineEditTextChanged(const QString &text);
	void receiveFileListViewDoubleClicked(const QModelIndex& modelIndex);
protected:
    bool event(QEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
private:
	FileListView *fileListView;
	FileListViewModel *fileListViewModel;
	ImprovedSortFilterProxyModel *sortFilterProxyModel;
	std::shared_ptr<FileListData> fileListData;
	QWidget *rootWidget;
	QVBoxLayout *rootLayout;
	QHBoxLayout *progressLayout;
	QFrame *progressWidget;
	QLabel *progressLabel;
	QProgressBar *progressBar;
	SearchFileListLineEdit* searchLineEdit;
	void writeLog(QString text);
	static QEvent::Type fileListLoadingProgressEventType();
	static QEvent::Type listEnterEventType();
	static QEvent::Type searchFileLineEditKeyDownEventType();
	static QEvent::Type fileListKeyUpEventType();
    void receiveFileList(std::shared_ptr<FileListData> fileListData);
	void loadFileListView();
	void receiveFileListProgressEvent(FileListDataLoader::ProgressEvent *event);
	void receiveListEnterEvent();
	void receiveSearchFileLineEditKeyDownEvent();
	void receiveFileListKeyUpEvent();
	void startFile(const QModelIndex& modelIndex);
};

#endif // STARTERWINDOW_H
