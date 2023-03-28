QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aesCbc.cpp \
    aesEax.cpp \
    aesGcm.cpp \
    cipherAes.cpp \
    cipherBase.cpp \
    cipherRsa.cpp \
    kAction.cpp \
    kActionBase.cpp \
    kActionDecrypt.cpp \
    kActionEncrypt.cpp \
    kActionKeyMgr.cpp \
    kActionPage.cpp \
    kActionQuit.cpp \
    main.cpp \
    mainwindow.cpp \
    rsaOeap.cpp \
    rsaSsa.cpp

HEADERS += \
    aesCbc.h \
    aesEax.h \
    aesGcm.h \
    cipherAes.h \
    cipherBase.h \
    cipherRsa.h \
    defines.h \
    enums.h \
    kAction.h \
    kActionBase.h \
    kActionDecrypt.h \
    kActionEncrypt.h \
    kActionKeyMgr.h \
    kActionPage.h \
    kActionQuit.h \
    mainwindow.h \
    rsaOeap.h \
    rsaSsa.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += \
    /usr/local/include/cryptopp/

LIBS += \
    -L /usr/local/lib/ -l:libcryptopp.a




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc
