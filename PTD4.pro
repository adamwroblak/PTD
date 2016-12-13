TEMPLATE = app
TARGET = PTD4

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

SOURCES += \
    sygnalik.cpp \
    main.cpp \
    qcustomplot.cpp \
    funkcje.cpp

HEADERS += \
    sygnalik.h \
    qcustomplot.h \
    funkcje.h




