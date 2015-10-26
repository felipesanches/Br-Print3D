#-------------------------------------------------
#
# Project created by QtCreator 2015-06-01T19:05:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BrPrint3D
TEMPLATE = app
TRANSLATIONS = EN_english.ts \
               PT_portuguese.ts\

SOURCES += main.cpp\
    glwidget.cpp \
    points.cpp \
    KI/Arduino_Serial.cpp \
    KI/File_Queue.cpp \
    KI/Repetier.cpp \
    threadRotine.cpp \
    KI/StringRepetierOps.cpp \
    Windows/aboutbrprint.cpp \
    Windows/documentation.cpp \
    Windows/help.cpp \
    Windows/legalwarning.cpp \
    Windows/loading.cpp \
    Windows/warning.cpp \
    arduinolistener.cpp \
    BrPrint3D.cpp \
    PrinterSettings.cpp \
    PrinterSettingsWidget.cpp \
    ManualControlWidget.cpp

HEADERS  += \
    glwidget.h \
    points.h \
    KI/Arduino_Serial.h \
    KI/File_Queue.h \
    KI/Repetier.h \
    threadRotine.h \
    KI/StringRepetierOps.h \
    Windows/aboutbrprint.h \
    Windows/documentation.h \
    Windows/help.h \
    Windows/legalwarning.h \
    Windows/loading.h \
    Windows/warning.h \
    arduinolistener.h \
    BrPrint \#D
    BrPrint3D.h \
    PrinterSettings.h \
    PrinterSettingsWidget.h \
    ManualControlWidget.h

FORMS    += \
    Pandora.ui \
    Windows/aboutbrprint.ui \
    Windows/documentation.ui \
    Windows/help.ui \
    Windows/legalwarning.ui \
    Windows/loading.ui \
    Windows/warning.ui \
    3dwidget.ui \
    PrinterSettingsWidget.ui \
    ManualControlWidget.ui

RESOURCES += \
    images.qrc \
    fonts.qrc \
    translations.qrc

LIBS += -lGL -lGLU -lglut
CONFIG += c++11

