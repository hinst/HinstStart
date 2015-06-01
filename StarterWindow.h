#ifndef STARTERWINDOW_H
#define STARTERWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QListView>
#include <QDebug>
#include <QLayout>
#include <QLineEdit>
#include <QThread>
#include "DataContainer.h"

class FileListViewModel : public QAbstractListModel {
public:
	DataContainer *dataContainer;
	int rowCount(const QModelIndex & parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
private:
	void WriteLog(QString text) const;
};

class StarterWindow : public QMainWindow
{
    Q_OBJECT
public:
    StarterWindow(QWidget *parent = 0);
    ~StarterWindow();
	void load();
private:
    DataContainer dataContainer;
    QListView* fileListView;
	FileListViewModel* fileListViewModel;
	QWidget *rootWidget;
	QVBoxLayout* rootLayout;
	QLineEdit* searchLineEdit;
	void WriteLog(QString text);
};

#endif // STARTERWINDOW_H
