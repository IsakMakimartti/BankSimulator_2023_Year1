QT       += core gui
QT += serialport
QT +=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.



win32: LIBS += -L$$PWD/build-KirjautumisDLL-Desktop_Qt_6_5_0_MinGW_64_bit-Debug/debug/ -lKirjautumisDLL

INCLUDEPATH += $$PWD/KirjautumisDLL
DEPENDPATH += $$PWD/KirjautumisDLL

win32: LIBS += -L$$PWD/build-NostoTalletusDLL-Desktop_Qt_6_5_0_MinGW_64_bit-Debug/debug/ -lNostoTalletusDLL

INCLUDEPATH += $$PWD/NostoTalletusDLL
DEPENDPATH += $$PWD/NostoTalletusDLL

win32: LIBS += -L$$PWD/build-nostoTalletusHistoriaDLL-Desktop_Qt_6_5_0_MinGW_64_bit-Debug/debug/ -lnostoTalletusHistoriaDLL

INCLUDEPATH += $$PWD/nostoTalletusHistoriaDLL
DEPENDPATH += $$PWD/nostoTalletusHistoriaDLL

win32: LIBS += -L$$PWD/build-TestiRFID-Desktop_Qt_6_5_0_MinGW_64_bit-Debug/debug/ -lTestiRFID

INCLUDEPATH += $$PWD/TestiRFID
DEPENDPATH += $$PWD/TestiRFID

win32: LIBS += -L$$PWD/build-TiliDLL-Desktop_Qt_6_5_0_MinGW_64_bit-Debug/debug/ -lTiliDLL

INCLUDEPATH += $$PWD/TiliDLL
DEPENDPATH += $$PWD/TiliDLL

win32: LIBS += -L$$PWD/build-TalletusDLL-Desktop_Qt_6_5_0_MinGW_64_bit-Debug/debug/ -lTalletusDLL

INCLUDEPATH += $$PWD/DLLTalletus
DEPENDPATH += $$PWD/DLLTalletus
