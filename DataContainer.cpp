#include "DataContainer.h"

DataContainer::DataContainer()
{

}

void DataContainer::setPaths()
{
    this->userStartMenuPath = QDir::homePath() + "/" + UserStartMenuSubPath;
    qDebug() << ("userStartMenuPath = '" + userStartMenuPath + "'");
    this->commonStartMenuPath = CommonStartMenuPath;
}

void DataContainer::load()
{
    this->setPaths();
}

void DataContainer::loadFiles(QString directory)
{

}

