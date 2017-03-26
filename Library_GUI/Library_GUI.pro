#-------------------------------------------------
#
# Project created by QtCreator 2017-03-23T19:02:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Library_GUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        dmain1.cpp \
    books.cpp \
    function.cpp \
    logbook.cpp \
    people.cpp \
    dmain2.cpp \
    dmainc.cpp \
    dlogin.cpp \
    dadmin.cpp \
    dadmin_nbook1.cpp \
    dadmin_nbook2.cpp \
    dadmin_nperson.cpp \
    dadmin_fbook.cpp \
    dadmin_fperson1.cpp \
    duser.cpp \
    duser_convert.cpp \
    duser_key.cpp \
    dadmin_fperson2.cpp \
    duser_borrow.cpp \
    duser_return.cpp \
    dcolor.cpp \
    mythread.cpp \
    dadmin_fbook2.cpp

HEADERS  += dmain1.h \
    books.h \
    function.h \
    global_define.h \
    logbook.h \
    people.h \
    dmain2.h \
    dmainc.h \
    dlogin.h \
    dadmin.h \
    dadmin_nbook1.h \
    dadmin_nbook2.h \
    dadmin_nperson.h \
    dadmin_fbook.h \
    dadmin_fperson1.h \
    duser.h \
    duser_convert.h \
    duser_key.h \
    dadmin_fperson2.h \
    duser_borrow.h \
    duser_return.h \
    dcolor.h \
    mythread.h \
    dadmin_fbook2.h

FORMS    += dmain1.ui \
    dmain2.ui \
    dmainc.ui \
    dlogin.ui \
    dadmin.ui \
    dadmin_nbook1.ui \
    dadmin_nbook2.ui \
    dadmin_nperson.ui \
    dadmin_fbook.ui \
    dadmin_fperson1.ui \
    duser.ui \
    duser_convert.ui \
    duser_key.ui \
    dadmin_fperson2.ui \
    duser_borrow.ui \
    duser_return.ui \
    dcolor.ui \
    dadmin_fbook2.ui

RC_FILE = icon.rc

RESOURCES += \
    resource.qrc
