#include "FileListData.h"

FileListData::FileListData()
{
	setPaths();
}

void FileListData::setPaths()
{
    this->userStartMenuPath = QDir::homePath() + "/" + UserStartMenuSubPath;
    this->commonStartMenuPath = CommonStartMenuPath;
}

void FileListData::load()
{
	this->files.clear();
	this->loadFiles(this->userStartMenuPath);
	this->loadIcons();
}

void FileListData::loadFiles(QString directoryPath)
{
	QDir qDirectory(directoryPath);
	auto files = qDirectory.entryInfoList();
	if (files.count() > 0)
	{
		for (int i = 0; i < files.count(); i++)
		{
			auto fileInfo = files[i];
			if ((fileInfo.fileName() != "..") && (fileInfo.fileName() != "."))
			{
				this->loadFile(fileInfo);
			}
		}
	}
}

void FileListData::loadFile(QFileInfo fileInfo)
{
	if (fileInfo.isDir())
	{
		loadFiles(fileInfo.filePath());
	}
	else
	{
		this->files.append(fileInfo);
		if (this->fileAddedEventReceiver != nullptr)
			this->fileAddedEventReceiver(files.count());
	}
}

void FileListData::WriteLog(QString text)
{
	qDebug() << (QString("FileListData") + text);
}

QIcon FileListData::loadIcon(QString filePath)
{
	QIcon result;
	auto filePathWideChars = new wchar_t[filePath.length() + 1];
	filePath = filePath.replace('/', '\\');
	filePath.toWCharArray(filePathWideChars);
	filePathWideChars[filePath.length()] = 0;
	auto fileInfo = new SHFILEINFO();
	this->WriteLog("Now loading icon for file " + filePath);
	if (SHGetFileInfoW(filePathWideChars, FILE_ATTRIBUTE_NORMAL, fileInfo, sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_LARGEICON))
	{
		result = QIcon(QtWin::fromHICON(fileInfo->hIcon));
		this->WriteLog("Icon loaded");
	}
	delete[] filePathWideChars;
	DestroyIcon(fileInfo->hIcon);
	delete fileInfo;
	return result;
}

void FileListData::loadIcons()
{
	auto fileIconProvider = new QFileIconProvider();
	icons.clear();
	for (int i = 0; i < files.count(); i++)
	{
		auto fileInfo = files[i];
		if (fileInfo.isSymLink())
			fileInfo = QFileInfo(fileInfo.symLinkTarget());
        /*
        const auto icon = loadIcon(fileInfo.absoluteFilePath());
		icons.append(icon);
        */
	}
	delete fileIconProvider;
}

