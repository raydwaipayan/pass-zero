QT += testlib
QT -= gui

CONFIG += qt console warn_on testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    testcrypto.cpp

HEADERS += \
    testcrypto.h

LIBS +=-L../src/crypto -lcrypto -lcryptopp -L../src/argon2 -largon2
include(../src/crypto/crypto.pri)
