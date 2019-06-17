#-------------------------------------------------
#
# Project created by QtCreator 2019-06-05T15:58:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtPDF
TEMPLATE = app

DESTDIR = $$PWD/../bin
INCLUDEPATH += $$PWD/../3rdparty/mupdf/includedll \
    $$PWD/../3rdparty/mupdf/include

LIBS += -L$$PWD/../3rdparty/mupdf/lib -llibmupdfdll


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui
