QT += core

TEMPLATE = lib
CONFIG  += qt staticlib
TARGET   = io

SOURCES +=  reader.cpp \
			writer.cpp
			
HEADERS +=  reader.h \
			writer.h

include (./io.pri)
include (../storage/storage.pri)
include (../crypto/crypto.pri)
