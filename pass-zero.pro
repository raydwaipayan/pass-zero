QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -L/usr/lib+ -lcryptopp
INCLUDEPATH += /usr/include/cryptopp

SOURCES += \
    src/crypt.cpp \
    src/dataitem.cpp \
    src/main.cpp \
    src/passzero.cpp \
    src/argon2.cpp \
    src/argon2-core.cpp \
    src/argon2-opt-core.cpp \
    src/kat.cpp \
    src/blake2b.c

HEADERS += \
    src/crypt.h \
    src/dataitem.h \
    src/passzero.h \
    src/argon2.h \
    src/argon2-core.h \
    src/kat.h \
    src/blake2.h \
    src/blake2-impl.h \
    src/blamka-round-opt.h \
    src/blamka-round-ref.h \
    src/brg-endian.h

FORMS += \
    ui/passzero.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
