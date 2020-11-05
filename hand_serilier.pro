QT += quick virtualkeyboard

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
           _GLIBCXX_USE_CXX11_ABI=0
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        device_pi.cpp \
        devicedriver.cpp \
        main.cpp \
        qReader.cpp \
        qRedis.cpp \
        qmlredisinterface.cpp \
        qmlthread.cpp \
        tcpmodel.cpp

RESOURCES += qml.qrc

INCLUDEPATH += /usr/local/include/hiredis
LIBS += -L/home/haoran/Qt5.14.2/5.14.2/gcc_64/bin/qmake   -lhiredis
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

    Environment {
        QT_QUICK_CONTROLS_CONF: "qrc:/qtquickcontrols2.conf"
        QT_AUTO_SCREEN_SCALE_FACTOR: "1"
    }
HEADERS += \
    device_pi.h \
    devicedriver.h \
    qReader.h \
    qRedis.h \
    qmlredisinterface.h \
    qmlthread.h \
    tcpmodel.h

LIBS  += -lwiringPi
OBJECTS_DIR  = tmp
MOC_DIR      = tmp

DISTFILES +=
