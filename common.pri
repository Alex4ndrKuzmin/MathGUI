win32: OS_SUFFIX = win32
linux-g++: OS_SUFFIX = linux

CONFIG(debug, debug|release) {
    BUILD_FLAG = debug
    LIB_SUFFIX = d
} else {
    BUILD_FLAG = release
}

DESTDIR = $${_PRO_FILE_PWD_}/bin/$${OS_SUFFIX}/$${BUILD_FLAG}
OUT_PWD = $${_PRO_FILE_PWD_}/bin/$${OS_SUFFIX}/$${BUILD_FLAG}
OBJECTS_DIR = $${_PRO_FILE_PWD_}/bin/$${OS_SUFFIX}/$${BUILD_FLAG}/.obj
MOC_DIR = $${_PRO_FILE_PWD_}/bin/$${OS_SUFFIX}/$${BUILD_FLAG}/.moc
RCC_DIR = $${_PRO_FILE_PWD_}/bin/$${OS_SUFFIX}/$${BUILD_FLAG}/.rcc
UI_DIR = $${_PRO_FILE_PWD_}/bin/$${OS_SUFFIX}/$${BUILD_FLAG}/.ui
MAKEFILE = $${_PRO_FILE_PWD_}/bin/$${OS_SUFFIX}/$${BUILD_FLAG}/Makefile

linux-q++: QMAKE_CXXFLAGS += -std=c++11

