#include "StarterWindow.h"

StarterWindow::StarterWindow(QWidget *parent)
    : QMainWindow(parent)
{
	rootWidget = new QWidget;
	setCentralWidget(rootWidget);
	rootLayout = new QVBoxLayout();
	searchLineEdit = new QLineEdit();
	searchLineEdit->setFont(CommonUI::globalObject.fixedFont());
	rootLayout->addWidget(searchLineEdit);
	fileListView = new QTableView();
	fileListView->setIconSize(QSize(32, 32));
	fileListView->setFont(CommonUI::globalObject.fixedFont());
	fileListView->verticalHeader()->setVisible(false);
	fileListView->verticalHeader()->resizeSections(QHeaderView::Fixed);
	fileListView->verticalHeader()->setDefaultSectionSize(34);
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

bool StarterWindow::event(QEvent *event)
{
    if (event->type() == )
}

void StarterWindow::loadFileList()
{
	unloadFileList();
    /*
	fileListData = new FileListData();
	fileListViewModel = new FileListViewModel();
	fileListViewModel->setFileListData(fileListData);
	sortFilterProxyModel = new QSortFilterProxyModel();
	sortFilterProxyModel->setSourceModel(fileListViewModel);
	sortFilterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	fileListView->setModel(sortFilterProxyModel);
	fileListView->setColumnWidth(0, 300);
    */
    QThread *loaderThread = new
}

void StarterWindow::WriteLog(QString text)
{
    qDebug() << text;
}

QEvent::Type StarterWindow::fileListDataLoadedEventType()
{
    return (QEvent::Type)(QEvent::User + 1);
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
