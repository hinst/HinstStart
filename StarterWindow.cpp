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
	progressBar->setTextVisible(false);
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

void StarterWindow::receiveFileListViewDoubleClicked(const QModelIndex &modelIndex)
{
	startFile(modelIndex);
}

void StarterWindow::startFile(const QModelIndex &modelIndex)
{
	auto actualModelIndex = sortFilterProxyModel->mapToSource(modelIndex);
	auto rowIndex = actualModelIndex.row();
	auto file = fileListData->files[rowIndex];
	auto filePath = QString("file:///") + file.filePath();
	auto fileUrl = QUrl(filePath);
	QDesktopServices::openUrl(fileUrl);
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
			progressLabel->setText("Loading files: " + QString::number(loadedEvent->count) + "...");
			result = true;
		}
		else if (loadedEvent->subType == FileListDataLoader::ProgressEvent::IconLoaded)
		{
			auto fileCount = loadedEvent->fileListData->files.count();
			auto iconCount = loadedEvent->count;
			progressLabel->setText("Loading icons: " + QString::number(iconCount) + " of " + QString::number(fileCount) + "...");
			if (progressBar->maximum() != fileCount)
			{
				progressBar->setMaximum(fileCount);
			}
			progressBar->setValue(loadedEvent->count);
			loadedEvent->fileListData->burnIcon(iconCount - 1);
			result = true;
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
    auto *loaderThread = new FileListDataLoader();
    loaderThread->objectToNotifyWhenLoaded = this;
    loaderThread->eventTypeToNotifyWhenLoaded = fileListDataLoadedEventType();
    loaderThread->start();
}

void StarterWindow::writeLog(QString text)
{
	CommonLog::Write(text);
}

QEvent::Type StarterWindow::fileListDataLoadedEventType()
{
    return (QEvent::Type)(QEvent::User + 1);
}

void StarterWindow::receiveFileList(std::shared_ptr<FileListData> fileListData)
{
	writeLog("Now receiving file list...");
	unloadFileList();
	fileListViewModel = new FileListViewModel();
    fileListViewModel->setFileListData(fileListData);
	sortFilterProxyModel = new ImprovedSortFilterProxyModel();
    sortFilterProxyModel->setSourceModel(fileListViewModel);
	sortFilterProxyModel->setFilterKeyColumn(0);
    sortFilterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    fileListView->setModel(sortFilterProxyModel);
    fileListView->setColumnWidth(0, 300);
	fileListView->setColumnWidth(1, 700);
	fileListView->sortByColumn(0, Qt::AscendingOrder);
	QObject::connect(fileListView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(receiveFileListViewDoubleClicked(QModelIndex)));
	progressWidget->setVisible(false);
	sortFilterProxyModel->setFilterFixedString(searchLineEdit->text());
	this->fileListData = fileListData;
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
