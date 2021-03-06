QT       += core gui
QT       += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    graphdiagram.cpp \
    main.cpp \
    mainwindow.cpp \
    measurementstable.cpp \
    ppmswidget.cpp \
    startdialog.cpp

HEADERS += \
    graphdiagram.h \
    mainwindow.h \
    measurementstable.h \
    ppmswidget.h \
    startdialog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    Ressourcen.qrc


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Instruments/release/ -lInstruments
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Instruments/debug/ -lInstruments
else:unix:!macx: LIBS += -L$$OUT_PWD/../Instruments/ -lInstruments

INCLUDEPATH += $$PWD/../Instruments
DEPENDPATH += $$PWD/../Instruments

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../InduControlCore/release/ -lInduControlCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../InduControlCore/debug/ -lInduControlCore
else:unix:!macx: LIBS += -L$$OUT_PWD/../InduControlCore/ -lInduControlCore

INCLUDEPATH += $$PWD/../InduControlCore
DEPENDPATH += $$PWD/../InduControlCore

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../InduCore/release/ -lInduCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../InduCore/debug/ -lInduCore
else:unix:!macx: LIBS += -L$$OUT_PWD/../InduCore/ -lInduCore

INCLUDEPATH += $$PWD/../InduCore
DEPENDPATH += $$PWD/../InduCore
