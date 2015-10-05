# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux-x86
TARGET = gui_sincro
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets
SOURCES += gui_test.cpp.cpp src/forms/SincroForm.cpp src/forms/testForm.cpp src/workers/SincroWorker.cpp
HEADERS += src/forms/SincroForm.h src/forms/testForm.h src/workers/SincroWorker.h
FORMS += src/forms/SincroForm.ui src/forms/testForm.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += src ../goon_sincro/src 
LIBS += -Wl,-rpath,../goon_sincro/dist/Debug/GNU-Linux-x86 ../goon_sincro/dist/Debug/GNU-Linux-x86/libgoon_sincro.so -llog4cxx  
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
