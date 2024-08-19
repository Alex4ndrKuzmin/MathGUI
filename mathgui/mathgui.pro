TEMPLATE = lib

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH +=  $${PWD}/../mathlib/src/             \
                $${PWD}/../mathlib/src/geometry     \


HEADERS +=                                  \
    src/Canvas.h \
    src/CircleItem.h \
    src/EditingItem.h                       \
    src/Interfaces/IGeometryItem.h          \
    src/Interfaces/IGraphicLine.h           \
    src/Common/ObjectCounter.h \
    src/LineSegmentItem.h \
    src/PointItem.h

SOURCES +=                                  \
    src/Canvas.cpp \
    src/CircleItem.cpp \
    src/LineSegmentItem.cpp \
    src/PointItem.cpp \
    src/mathgui.cpp                         \
    src/EditingItem.cpp                     \
    src/Interfaces/IGeometryItem.cpp        \
    src/Interfaces/IGraphicLine.cpp         \
    src/Common/ObjectCounter.cpp

include($${PWD}/../common.pri)

LIBS_PATH = $${PWD}/../mathlib/bin/$${OS_SUFFIX}/$${BUILD_FLAG}
LIBS += -L$${LIBS_PATH} -lmathlib
