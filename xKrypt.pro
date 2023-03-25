QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cipherAes.cpp \
    cipherBase.cpp \
    cipherRsa.cpp \
    kActionBase.cpp \
    kActionDecrypt.cpp \
    kActionEncrypt.cpp \
    kActionKeyMgr.cpp \
    kDialog.cpp \
    main.cpp \
    mainwindow.cpp \
    man.cpp

HEADERS += \
    .h \
    cipherAes.h \
    cipherBase.h \
    cipherRsa.h \
    kActionBase.h \
    kActionDecrypt.h \
    kActionEncrypt.h \
    kActionKeyMgr.h \
    kDialog.h \
    mainwindow.h \
    man.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc
