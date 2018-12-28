######################################################################
# Automatically generated by qmake (3.1) Tue Dec 11 17:38:16 2018
######################################################################

QT += core gui widgets

TEMPLATE = app
TARGET = saturn
INCLUDEPATH += .

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/centralwidget.cpp\
    src/dirselector.cpp \
    src/plateviewcontroller.cpp\
    src/plateitemmodel.cpp\
    src/platelisttab.cpp\
    src/searchthread.cpp \
    src/dpxreader.cpp

HEADERS += \
    src/mainwindow.h \
    src/centralwidget.h\
    src/dirselector.h \
    src/plateviewcontroller.h\
    src/plateitemmodel.h\
    src/platelisttab.h\
    src/searchthread.h \
    src/dpxreader.h \
    src/DPXimage_Header.h
