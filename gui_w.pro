QT += core gui serialport printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    countdownhandler.cpp \
    dataprocess.cpp \
    file.cpp \
    jsonmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    serialportreader.cpp

HEADERS += \
    countdownhandler.h \
    dataprocess.h \
    datasmoother.h \
    file.h \
    jsonmanager.h \
    mainwindow.h \
    qcustomplot.h \
    serialportreader.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

