#-------------------------------------------------
#
# Project created by QtCreator 2012-02-19T05:48:42
#
#-------------------------------------------------

QT       += core gui opengl
LIBS     += -l GLU

TARGET = CV-Playground
TEMPLATE = app

# # add external dependencies here

# VPATH +=
# INCLUDEPATH +=

SOURCES += main.cpp \
    window.cpp \
    glwidget.cpp \
    geometry.cpp \
    arcball.cpp

HEADERS  += \
    window.h \
    glwidget.h \
    geometry.h \
    arcball.h

OTHER_FILES += \
    README.txt
