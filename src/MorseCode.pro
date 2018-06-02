#-------------------------------------------------
#
# Project created by QtCreator 2016-07-12T23:54:52
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MorseCode
TEMPLATE = app


SOURCES += qmouselabel.cpp \
    qplaintexteditkey.cpp \
    main.cpp\
    mainwindow.cpp\
    fftx.cpp \
    appcore.cpp \
    ringbuffer.cpp \
    soundsettings.cpp \
    morsedecodersettings.cpp \
    printtext.cpp \
    morseencodercore.cpp \
    morsedecodercore.cpp \
    inputtext.cpp \
    progtimer.cpp \
    settings.cpp \
    qlabelkey.cpp \
    spectrumsettings.cpp \
    configfile.cpp \
    wavefile.cpp \
    audioplayer.cpp \
    audiorecorder.cpp \
    audioplayerthread.cpp \
    audiorecorderthread.cpp \
    eden.cpp \
    spectrumfull.cpp \
    about.cpp

HEADERS  += qmouselabel.h \
    objmem.h \
    qplaintexteditkey.h \
    mainwindow.h\
    fftx.h \
    appcore.h \
    ringbuffer.h \
    soundsettings.h \
    morsedecodersettings.h \
    printtext.h \
    morseencodercore.h \
    morsedecodercore.h \
    inputtext.h \
    progtimer.h \
    settings.h \
    qlabelkey.h \
    spectrumsettings.h \
    configfile.h \
    wavefile.h \
    audioplayer.h \
    audiorecorder.h \
    audioplayerthread.h \
    audiorecorderthread.h \
    eden.h \
    spectrumfull.h \
    about.h

FORMS    += mainwindow.ui \
    soundsettings.ui \
    printtext.ui \
    morsedecodersettings.ui \
    inputtext.ui \
    spectrumsettings.ui \
    spectrumfull.ui \
    about.ui

CONFIG += c++11
