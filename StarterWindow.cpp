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
	fileListViewModel = nullptr;
	sortFilterProxyModel = nullptr;
	rootLayout->addWidget(fileListView);
	rootWidget->setLayout(rootLayout);
}

StarterWindow::~StarterWindow()
{
	delete fileListViewModel;
}

void StarterWindow::load()
{
	fileListView->setModel(nullptr);
	if (sortFilterProxyModel != nullptr)
	{
		delete sortFilterProxyModel;
		sortFilterProxyModel = nullptr;
	}
	if (fileListViewModel != nullptr)
	{
		delete fileListViewModel;
		fileListViewModel = nullptr;
	}
	dataContainer.load();
	fileListViewModel = new FileListViewModel();
	fileListViewModel->fileListData = &dataContainer;
	sortFilterProxyModel = new QSortFilterProxyModel();
	sortFilterProxyModel->setSourceModel(fileListViewModel);
	fileListView->setModel(sortFilterProxyModel);
}

void StarterWindow::WriteLog(QString text)
{
	qDebug() << text;
}
