#-------------------------------------------------
#
# Project created by QtCreator 2015-06-01T12:50:42
#
#-------------------------------------------------

QT += core gui widgets winextras
CONFIG(debug, debug|release) {
    CONFIG += console
}
CONFIG += c++11

TARGET = HinstStart
TEMPLATE = app

SOURCES += main.cpp\
        StarterWindow.cpp \
    FileListViewModel.cpp \
    FileListData.cpp \
    CommonUI.cpp \
    FileListDataLoader.cpp \
    CommonLog.cpp \
    ImprovedSortFilterProxyModel.cpp \
    FileListView.cpp \
    SearchFileListLineEdit.cpp

HEADERS  += StarterWindow.h \
    FileListViewModel.h \
    FileListData.h \
    CommonUI.h \
    FileListDataLoader.h \
    CommonLog.h \
    ImprovedSortFilterProxyModel.h \
    FileListView.h \
    SearchFileListLineEdit.h

DISTFILES += \
    ResourceFile.rc

RC_FILE = ResourceFile.rc
