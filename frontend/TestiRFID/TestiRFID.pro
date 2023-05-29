QT += core gui serialport

greaterThan(QT_MAJOR_VERSION,4):QT+=widgets

TEMPLATE = lib
DEFINES += TESTIRFID_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    testirfid.cpp

HEADERS += \
    TestiRFID_global.h \
    testirfid.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    testirfid.ui
