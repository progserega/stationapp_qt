QT += qml quick sql

CONFIG += c++11

SOURCES += main.cpp \
    sqlstore.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    sqlstore.h
