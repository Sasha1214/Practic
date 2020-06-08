include(gtest_dependency.pri)
INCLUDEPATH += C:\QT1\laba9\TestWork\test

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        test/IKeypad.h \
        test/ILatch.h \
        test/lockcontroller.h \
        tst_testdivisionbyzero.h

SOURCES += \
        main.cpp \
        test/lockcontroller.cpp
