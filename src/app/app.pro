TEMPLATE = app
TARGET = pass-zero

CONFIG += qt
QT += core gui
DESTDIR = ../..
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += main.cpp \
		passzero.cpp

HEADERS += passzero.h 

FORMS += ../ui/passzero.ui

LIBS += -L../io -lio
LIBS += -L../storage -lstorage
LIBS += -L../crypto -lcrypto
LIBS += -L../argon2 -largon2
LIBS += -L/usr/lib/ -lcryptopp

include(./app.pri)
include(../crypto/crypto.pri)
include(../argon2/argon2.pri)
include(../storage/storage.pri)
include(../io/io.pri)

unix:!macx {
    target.files += $$DESTDIR/$$TARGET
    target.path = /usr/local/bin
    INSTALLS += target
}

