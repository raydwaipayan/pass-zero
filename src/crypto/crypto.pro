QT -= gui core

TEMPLATE = lib
CONFIG += staticlib
TARGET = crypto

SOURCES += hasher.cpp  \
           crypto.cpp
		    
HEADERS += hasher.h \
           crypto.h

include(./crypto.pri)
include(../argon2/argon2.pri)
