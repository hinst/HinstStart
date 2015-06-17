#ifndef FILELISTDATALOADER_H
#define FILELISTDATALOADER_H

#include <memory>
#include <QObject>
#include <QEvent>
#include <QCoreApplication>
#include "FileListData.h"

class FileListDataLoader : public QObject
{
	Q_OBJECT
public:
	explicit FileListDataLoader(QObject *parent = 0);
    static QEvent::Type pokeEventType();
	bool event(QEvent *event) override;
	void load();
    // Objet to notify when loading is completed;
    QObject* objectToNotifyWhenLoaded;
    // Send this event type when loading is compledted;
    QEvent::Type eventTypeToNotifyWhenLoaded;
    class LoadedEvent : public QEvent
    {
    public:
        shared_ptr<FileListData> fileListData;
    };
};

#endif // FILELISTDATALOADER_H
