QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database.cpp \
    main.cpp \
    mainwindow.cpp \
    receipteditdialog.cpp \
    receipteditwidget.cpp

HEADERS += \
    ReceiptTableDelegate.h \
    ReceiptTableModel.h \
    database.h \
    mainwindow.h \
    receipteditdialog.h \
    receipteditwidget.h

FORMS += \
    mainwindow.ui \
    receipteditdialog.ui \
    receipteditwidget.ui

TRANSLATIONS += \
    Accountant_ja_JP.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
