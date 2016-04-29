#-------------------------------------------------
#
# Project created by QtCreator 2016-04-28T12:36:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT       += network

CONFIG += c++11
CONFIG += qwt

TARGET = TrackLive
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        qmainplot.cpp \
        qtrackclient.cpp

HEADERS  += mainwindow.h \
        qmainplot.h \
        qtrackclient.h
