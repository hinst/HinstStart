#ifndef STARTERWINDOW_H
#define STARTERWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QListView>
#include <QDebug>
#include "DataContainer.h"

class StarterWindow : public QMainWindow
{
    Q_OBJECT
public:
    StarterWindow(QWidget *parent = 0);
    ~StarterWindow();
private:
    DataContainer dataContainer;
    QListView* fileListView;
};

#endif // STARTERWINDOW_H
