include($${PWD}/../common.pri)

TEMPLATE = app

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    guitest.cpp

INCLUDEPATH +=  $${PWD}/../mathgui/src/             \
                $${PWD}/../mathlib/src/             \
                $${PWD}/../mathlib/src/geometry     \

LIBS_PATH = $${PWD}/../mathgui/bin/$${OS_SUFFIX}/$${BUILD_FLAG}
LIBS += -L$${LIBS_PATH} -lmathgui

LIBS_PATH = $${PWD}/../mathlib/bin/$${OS_SUFFIX}/$${BUILD_FLAG}
LIBS += -L$${LIBS_PATH} -lmathlib



