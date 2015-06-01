#ifndef STARTERWINDOW_H
#define STARTERWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QListView>
#include <QDebug>
#include <QLayout>
#include <QLineEdit>
#include <QThread>
#include <QSortFilterProxyModel>
#include "FileListData.h"
#include "FileListViewModel.h"

class StarterWindow : public QMainWindow
{
    Q_OBJECT
public:
    StarterWindow(QWidget *parent = 0);
    ~StarterWindow();
	void load();
private:
	FileListData dataContainer;
    QListView* fileListView;
	FileListViewModel* fileListViewModel;
	QSortFilterProxyModel *sortFilterProxyModel;
	QWidget *rootWidget;
	QVBoxLayout* rootLayout;
	QLineEdit* searchLineEdit;
	void WriteLog(QString text);
};

#endif // STARTERWINDOW_H
