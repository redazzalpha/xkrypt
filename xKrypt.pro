QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aescbc.cpp \
    aeseax.cpp \
    aesgcm.cpp \
    cipheraes.cpp \
    cipherbase.cpp \
    cipherrsa.cpp \
    kaction.cpp \
    kactionbase.cpp \
    kactiondecrypt.cpp \
    kactionencrypt.cpp \
    kactionkeyMgr.cpp \
    kactionpage.cpp \
    kactionquit.cpp \
    kexcept.cpp \
    keygen.cpp \
    kserial.cpp \
    main.cpp \
    mainwindow.cpp \
    rsaoeap.cpp \
    rsassa.cpp

HEADERS += \
    aescbc.h \
    aeseax.h \
    aesgcm.h \
    cipheraes.h \
    cipherbase.h \
    cipherrsa.h \
    defines.h \
    enums.h \
    kaction.h \
    kactionbase.h \
    kactiondecrypt.h \
    kactionencrypt.h \
    kactionkeyMgr.h \
    kactionpage.h \
    kactionquit.h \
    kexcept.h \
    keygen.h \
    kserial.h \
    mainwindow.h \
    rsaoeap.h \
    rsassa.h

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
