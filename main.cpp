#include <QApplication>
#include "StarterWindow.h"
#include "DataContainer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StarterWindow w;
    w.show();
    return a.exec();
}
