QT -= gui
QT += core

TEMPLATE = lib
CONFIG += staticlib
TARGET = storage

SOURCES +=  database.cpp \
			dataitem.cpp
			
HEADERS +=  database.h \
			dataitem.h

include(./storage.pri)
include(../crypto/crypto.pri)

