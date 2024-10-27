QT += core gui charts 
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport 
CONFIG += c++11

SOURCES += \
    dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    dialog.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    dialog.ui \
    mainwindow.ui
