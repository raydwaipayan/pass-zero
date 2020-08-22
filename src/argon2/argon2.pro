QT -= gui core

TEMPLATE = lib
CONFIG += staticlib
TARGET = argon2

SOURCES +=  argon2.cpp \
        argon2-core.cpp \
        argon2-opt-core.cpp \
        blake2b.c \
        kat.cpp
		    
HEADERS +=  argon2.h \
        argon2-core.h \
        blake2.h \
        blake2-impl.h \
        blamka-round-opt.h \
        brg-endian.h \
        kat.h
			
include(./argon2.pri)

