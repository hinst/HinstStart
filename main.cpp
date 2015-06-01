#include <QApplication>
#include "StarterWindow.h"
#include "FileListData.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StarterWindow w;
	w.showMaximized();
	w.load();
    return a.exec();
}
