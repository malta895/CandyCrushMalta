 #-------------------------------------------------
#
# Project created by QtCreator 2015-01-19T11:48:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CandyCrushGUI
TEMPLATE = app

CONFIG += c++11 #aggiungo  il supporto al c++ 11

QT += multimedia #aggiungo il supporto multimediale per leggere i file wav

SOURCES += main.cpp\
        mainwindow.cpp \
    finestragioco.cpp \
    gestiscicampo.cpp \
    inserimento_nome.cpp \
    sequenziale.cpp \
    classifica.cpp \
    finestraclassifica.cpp \
    finestrasequenziale.cpp

HEADERS  += mainwindow.h \
    finestragioco.h \
    gestiscicampo.h \
    inserimento_nome.h \
    sequenziale.h \
    classifica.h \
    finestraclassifica.h \
    finestrasequenziale.h

FORMS    += mainwindow.ui \
    finestragioco.ui \
    inserimento_nome.ui \
    finestraclassifica.ui \
    finestrasequenziale.ui

DISTFILES += \
    FileDati/campo.dat \
    FileDati/giocatori.dat \
    FileDati/mosse.dat \
    FileDati/sequenziale.dat
