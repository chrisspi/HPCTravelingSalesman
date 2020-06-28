#-------------------------------------------------
#
# Project created by QtCreator 2017-09-29T15:53:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HPC_TSP
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



# Hier werden die Dateien deklariert die in das Projekt geladen werden sollen

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        gamewidget_2.cpp \
        ../cliApp/gamewidget_2.cpp \
        ../cliApp/ali535.tsp \
        ../cliApp/berlin52.tsp \
        ../cliApp/ENN.cpp \
        ../cliApp/ENN.h \
        ../cliApp/main.cpp \
        ../cliApp/makefile \
        ../cliApp/points.h \
        ../cliApp/TSP.cpp \
        ../cliApp/TSP.h \

HEADERS += \
        mainwindow.h \
        gamewidget_2.h

FORMS += \
        mainwindow.ui
