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
    src/crypto/hasher.cpp \
    src/database.cpp \
    src/dataitem.cpp \
    src/main.cpp \
    src/passzero.cpp \
    src/crypto/argon2.cpp \
    src/crypto/argon2-core.cpp \
    src/crypto/argon2-opt-core.cpp \
    src/crypto/kat.cpp \
    src/crypto/blake2b.c \
    src/reader.cpp \
    src/writer.cpp

HEADERS += \
    src/crypto/hasher.h \
    src/database.h \
    src/dataitem.h \
    src/passzero.h \
    src/crypto/argon2.h \
    src/crypto/argon2-core.h \
    src/crypto/kat.h \
    src/crypto/blake2.h \
    src/crypto/blake2-impl.h \
    src/crypto/blamka-round-opt.h \
    src/crypto/blamka-round-ref.h \
    src/crypto/brg-endian.h \
    src/reader.h \
    src/writer.h

FORMS += \
    ui/passzero.ui \
    ui/passzero_old.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
