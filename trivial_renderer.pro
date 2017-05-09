TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tvector4d.cpp \
    tvector3d.cpp \
    tmodel.cpp \
    tmatrix4x4.cpp \
    tinput.cpp \
    timage.cpp \
    tdraw.cpp \
    lodepng.cpp \
    cmdline.c \
    tshading.cpp

HEADERS += \
    tvector4d.h \
    tvector3d.h \
    tpoint.h \
    tmodel.h \
    tmatrix4x4.h \
    tinput.h \
    timage.h \
    tdraw.h \
    lodepng.h \
    cmdline.h \
    tshading.h
