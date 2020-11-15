QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    widget/chessboard.cpp \
    widget/chessman.cpp \
    windows/mainwindow.cpp

HEADERS += \
    widget/chessboard.h \
    widget/chessman.h \
    windows/mainwindow.h

FORMS += \
    windows/mainwindow.ui

TRANSLATIONS += \
    chines_chess_zh_SG.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    img/b.png \
    img/bb.png \
    img/bj.png \
    img/bm.png \
    img/board.png \
    img/bp.png \
    img/bs.png \
    img/bx.png \
    img/bz.png \
    img/icon.png \
    img/r.png \
    img/rb.png \
    img/rj.png \
    img/rm.png \
    img/rp.png \
    img/rs.png \
    img/rx.png \
    img/rz.png

RESOURCES += \
    img/img.qrc


