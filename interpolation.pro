QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = interpolation
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp\
        plotframe.cpp

HEADERS  += widget.h\
        plotframe.h

FORMS    += widget.ui
