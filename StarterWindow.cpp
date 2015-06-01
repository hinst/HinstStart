#include "StarterWindow.h"

StarterWindow::StarterWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->fileListView = new QListView(this);
    this->dataContainer.load();
}

StarterWindow::~StarterWindow()
{

}
