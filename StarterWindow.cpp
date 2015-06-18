#include "StarterWindow.h"

StarterWindow::StarterWindow(QWidget *parent)
    : QMainWindow(parent)
{
	rootWidget = new QWidget(this);
	setCentralWidget(rootWidget);
	rootLayout = new QVBoxLayout(rootWidget);
	searchLineEdit = new QLineEdit(this);
	searchLineEdit->setFont(CommonUI::globalObject.fixedFont());
	rootLayout->addWidget(searchLineEdit);
	progressWidget = new QFrame(this);
	progressLayout = new QHBoxLayout(progressWidget);
	progressLabel = new QLabel(this);
	progressLabel->setText("Now loading...");
	progressLabel->setFont(CommonUI::globalObject.fixedFont());
	progressLabel->setFixedWidth(300);
	progressLayout->addWidget(progressLabel, 1);
	progressBar = new QProgressBar(this);
	progressBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	progressLayout->addWidget(progressBar, 1);
	progressWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	rootLayout->addWidget(progressWidget);
	fileListView = new QTableView(this);
	fileListView->setIconSize(QSize(32, 32));
	fileListView->setFont(CommonUI::globalObject.fixedFont());
	fileListView->verticalHeader()->setVisible(false);
	fileListView->verticalHeader()->resizeSections(QHeaderView::Fixed);
	fileListView->verticalHeader()->setDefaultSectionSize(34);
	fileListViewModel = nullptr;
	sortFilterProxyModel = nullptr;
	rootLayout->addWidget(fileListView);
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
    auto result = false;
    if (event->type() == fileListDataLoadedEventType())
    {
		auto loadedEvent = (FileListDataLoader::ProgressEvent*)event;
		if (loadedEvent->subType == FileListDataLoader::ProgressEvent::Finished)
		{
			receiveFileList(loadedEvent->fileListData);
			loadedEvent->thread->wait();
			delete loadedEvent->thread;
			result = true;
		}
		else if (loadedEvent->subType == FileListDataLoader::ProgressEvent::FileAdded)
		{
			progressLabel->setText("Loading files: " + QString::number(loadedEvent->fileListData->files.count()) + "...");
		}
    }
    else
    {
        result = this->QMainWindow::event(event);
    }
    return result;
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
    auto *loaderThread = new FileListDataLoader();
    loaderThread->objectToNotifyWhenLoaded = this;
    loaderThread->eventTypeToNotifyWhenLoaded = fileListDataLoadedEventType();
    loaderThread->start();
}

void StarterWindow::WriteLog(QString text)
{
	CommonLog::Write(text);
}

QEvent::Type StarterWindow::fileListDataLoadedEventType()
{
    return (QEvent::Type)(QEvent::User + 1);
}

void StarterWindow::receiveFileList(std::shared_ptr<FileListData> fileListData)
{
	WriteLog("Now receiving file list...");
	unloadFileList();
	fileListViewModel = new FileListViewModel();
    fileListViewModel->setFileListData(fileListData);
    sortFilterProxyModel = new QSortFilterProxyModel();
    sortFilterProxyModel->setSourceModel(fileListViewModel);
    sortFilterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    fileListView->setModel(sortFilterProxyModel);
    fileListView->setColumnWidth(0, 300);
}

void StarterWindow::unloadFileList()
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
}
