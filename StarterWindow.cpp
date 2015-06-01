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
	fileListData = nullptr;
	fileListViewModel = nullptr;
	sortFilterProxyModel = nullptr;
	rootLayout->addWidget(fileListView);
	rootWidget->setLayout(rootLayout);
	QObject::connect(searchLineEdit, SIGNAL(textChanged(QString)), this, SLOT(receiveSearchLineEditTextChanged(QString)));
}

StarterWindow::~StarterWindow()
{
	unloadFileList();
}

void StarterWindow::receiveSearchLineEditTextChanged(const QString& text)
{
	if (sortFilterProxyModel != nullptr)
	{
		sortFilterProxyModel->setFilterFixedString(text);
	}
}

void StarterWindow::loadFileList()
{
	unloadFileList();
	fileListData = new FileListData();
	fileListViewModel = new FileListViewModel();
	fileListViewModel->setFileListData(fileListData);
	sortFilterProxyModel = new QSortFilterProxyModel();
	sortFilterProxyModel->setSourceModel(fileListViewModel);
	sortFilterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	fileListView->setModel(sortFilterProxyModel);
}

void StarterWindow::WriteLog(QString text)
{
	qDebug() << text;
}

void StarterWindow::unloadFileList()
{
	fileListView->setModel(nullptr);
	if (fileListData != nullptr)
	{
		delete fileListData;
		fileListData = nullptr;
	}
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
}
