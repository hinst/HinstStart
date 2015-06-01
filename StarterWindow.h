#ifndef STARTERWINDOW_H
#define STARTERWINDOW_H

#include <QMainWindow>
#include <QWidget>

class StarterWindow : public QMainWindow
{
    Q_OBJECT

public:
    StarterWindow(QWidget *parent = 0);
    ~StarterWindow();
};

#endif // STARTERWINDOW_H
