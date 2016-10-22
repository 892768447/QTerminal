QT += core gui widgets uitools
CONFIG += c++11
TARGET = QTerminal
INCLUDEPATH += include include/KGL/Widgets
TEMPLATE = staticlib

SOURCES += \
    src/Dialogs/QTerminal.cpp \
    src/Design/QTerminalDesign.cpp \
    src/Dialogs/QFormatEditor.cpp

HEADERS += \
    include/KGL/Dialogs/QTerminal.hpp \
    include/KGL/KGLConfig.hpp \
    include/KGL/Design/QTerminalDesign.hpp \
    include/KGL/Dialogs/QTerminalEnums.hpp \
    include/KGL/Dialogs/QFormatEditor.hpp

FORMS += \
    res/QFormatEditor.ui

RESOURCES += \
    res/gui.qrc
