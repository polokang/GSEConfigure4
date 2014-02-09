#-------------------------------------------------
#
# Project created by QtCreator 2013-12-16T09:20:11
#
#-------------------------------------------------

QT       += core gui xml xmlpatterns

TARGET = GSEConfigure
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    common.cpp \
    hwcfg.c \
    gcbconf.cpp \
    gcbdelegate.cpp \
    portcf.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    common.h \
    base.h \
    realdata.h \
    hio.h \
    gcbconf.h \
    gcbdelegate.h \
    portcf.h \
    about.h

FORMS    += mainwindow.ui \
    gcbconf.ui \
    portcf.ui \
    about.ui


win32{
LIBS +=-L./lib -lxmlhelplib
}

RC_FILE = app.rc

OTHER_FILES += \
    app.rc

RESOURCES += \
    gseCfg.qrc
