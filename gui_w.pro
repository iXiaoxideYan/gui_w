QT += core gui serialport printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include
SOURCES += \
    src/graphhandler.cpp \
    src/countdownhandler.cpp \
    src/dataprocess.cpp \
    src/file.cpp \
    src/jsonmanager.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/qcustomplot.cpp \
    src/serialportreader.cpp

HEADERS += \
    include/countdownhandler.h \
    include/dataprocess.h \
    include/datasmoother.h \
    include/file.h \
    include/graphhandler.h \
    include/jsonmanager.h \
    include/mainwindow.h \
    include/qcustomplot.h \
    include/serialportreader.h

FORMS += \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

