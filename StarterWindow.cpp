#include "StarterWindow.h"

StarterWindow::StarterWindow(QWidget *parent)
    : QMainWindow(parent)
{
	rootWidget = new QWidget;
	setCentralWidget(rootWidget);
	rootLayout = new QVBoxLayout();
	searchLineEdit = new QLineEdit();
	rootLayout->addWidget(searchLineEdit);
	fileListView = new QListView();
	fileListViewModel = new FileListViewModel();
	rootLayout->addWidget(fileListView);
	rootWidget->setLayout(rootLayout);
}

StarterWindow::~StarterWindow()
{

}

void StarterWindow::load()
{
	this->dataContainer.load();
	fileListViewModel->dataContainer = &dataContainer;
	fileListView->setModel(fileListViewModel);
}

void StarterWindow::WriteLog(QString text)
{
	qDebug() << text;
}

int FileListViewModel::rowCount(const QModelIndex &parent) const
{
	return dataContainer->files.count();
}

QVariant FileListViewModel::data(const QModelIndex &index, int role) const
{
	QVariant result = QVariant::Invalid;
	if (role == Qt::DisplayRole)
	{
		result = dataContainer->files[index.row()].fileName();
	}
	return result;
}

void FileListViewModel::WriteLog(QString text) const
{
	qDebug() << text;
}
