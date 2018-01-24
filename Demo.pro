######################################################################
# Automatically generated by qmake (3.0) Tue Jan 16 21:29:30 2018
######################################################################
QT+=core gui sql
greaterThan(QT_MAJOR_VERSION,4):QT+=widgets

TEMPLATE = app
TARGET = Demo
INCLUDEPATH += .

# Input
HEADERS += aboutus.h \
           admin.h \
           bookcommand.h \
           catalogage.h \
           cell.h \
           connexion.h \
           finddialog.h \
           generateid.h \
           gotocelldialog.h \
           hirebook.h \
           history.h \
           mainwindow.h \
           modelview.h \
           searchbook.h \
           sortdialog.h \
           spreadsheet.h
FORMS += gotocelldialog.ui mainwindow.ui sortdialog.ui
SOURCES += aboutus.cpp \
           admin.cpp \
           bookcommand.cpp \
           catalogage.cpp \
           cell.cpp \
           connexion.cpp \
           finddialog.cpp \
           generateid.cpp \
           gotocelldialog.cpp \
           hirebook.cpp \
           history.cpp \
           main.cpp \
           mainwindow.cpp \
           modelview.cpp \
           searchbook.cpp \
           sortdialog.cpp \
           spreadsheet.cpp
RESOURCES += spreadsheet.qrc