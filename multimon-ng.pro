TEMPLATE = app
CONFIG += console
CONFIG -= qt
CONFIG -= app_bundle
DEFINES += MAX_VERBOSE_LEVEL=3
QMAKE_CFLAGS += -std=gnu99
QMAKE_CFLAGS += -g # For profiling

isEmpty(PREFIX) {
 PREFIX = /usr/local/
}
TARGET = easmon-ng
target.path = $$PREFIX/bin
INSTALLS += target

HEADERS += \
    multimon.h \
    gen.h \
    filter.h \
    filter-i386.h

SOURCES += \
    unixinput.c \
    uart.c \
    selcall.c \
    hdlc.c \
    demod_ufsk12.c \
    demod_dtmf.c \
    costabi.c \
    costabf.c \
    clip.c \
    demod_eas.c \
    demod_dumpcsv.c

macx{
DEFINES += DUMMY_AUDIO
DEFINES += CHARSET_UTF8
#DEFINES += ARCH_X86_64
}

unix:freebsd-g++:!symbian:!macx{
#DEFINES += ARCH_I386
DEFINES += PULSE_AUDIO
DEFINES += CHARSET_UTF8
LIBS += -L/usr/local/lib -lpulse-simple -lpulse
}

unix:linux-g++-32:!symbian:!macx{
#DEFINES += ARCH_I386
DEFINES += PULSE_AUDIO
DEFINES += CHARSET_UTF8
LIBS += -lpulse-simple -lpulse
}

unix:linux-g++-64:!symbian:!macx{
#DEFINES += ARCH_X86_64
DEFINES += PULSE_AUDIO
DEFINES += CHARSET_UTF8
LIBS += -lpulse-simple -lpulse
}

unix:linux-g++:!symbian:!macx{
DEFINES += PULSE_AUDIO
DEFINES += CHARSET_UTF8
LIBS += -lpulse-simple -lpulse
}
