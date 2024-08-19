TEMPLATE = lib

SOURCES += \
    src/geometry/circle.cpp \
    src/abstractpoint.cpp \
    src/geometry/linesegment.cpp \
    src/geometry/point.cpp \
    src/mathlib.cpp

include($${PWD}/../common.pri)

HEADERS += \
    src/geometry/circle.h \
    src/abstractpoint.h \
    src/geometry/linesegment.h \
    src/geometry/point.h

