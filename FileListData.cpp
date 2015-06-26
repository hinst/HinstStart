#include "FileListData.h"

FileListData::FileListData()
{
	hicons = nullptr;
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
	this->loadHIcons();
}

FileListData::~FileListData()
{
	releaseHIcons();
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
	CommonLog::write(QString("FileListData") + text);
}

HICON FileListData::loadHIcon(QString filePath)
{
	HICON result = 0;
	auto filePathWideChars = new wchar_t[filePath.length() + 1];
	filePath = filePath.replace('/', '\\');
	filePath.toWCharArray(filePathWideChars);
	filePathWideChars[filePath.length()] = 0;
	auto fileInfo = new SHFILEINFO();
	if (SHGetFileInfoW(filePathWideChars, FILE_ATTRIBUTE_NORMAL, fileInfo, sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_LARGEICON))
	{
		result = fileInfo->hIcon;
	}
	delete[] filePathWideChars;
	delete fileInfo;
	return result;
}

void FileListData::burnIcon(int index)
{
	auto hicon = hicons[index];
//	if (files[index].suffix() == QString("url"))
//		writeLog(files[index].fileName());
	QIcon icon = QIcon(QtWin::fromHICON(hicon));
	icons.append(icon);
}

void FileListData::loadHIcons()
{
	hicons = new HICON[files.count()];
	for (int i = 0; i < files.count(); i++)
	{
		auto fileInfo = files[i];
		if (fileInfo.isSymLink())
			fileInfo = QFileInfo(fileInfo.symLinkTarget());
		const auto icon = loadHIcon(fileInfo.absoluteFilePath());
		hicons[i] = icon;
		if (iconLoadedEventReceiver != nullptr)
			iconLoadedEventReceiver(i + 1);
	}
}

void FileListData::releaseHIcons()
{
	if (hicons != nullptr)
	{
		for (int i = 0; i < files.count(); i++)
			DestroyIcon(hicons[i]);
		delete[] hicons;
		hicons = nullptr;
	}
}

void FileListData::writeLog(QString text)
{
	CommonLog::write(text);
}

