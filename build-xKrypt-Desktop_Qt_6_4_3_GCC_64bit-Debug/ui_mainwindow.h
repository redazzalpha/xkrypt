/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *m_mainStack;
    QWidget *m_keyMPage;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *m_keyMVL;
    QPlainTextEdit *m_keyMIntro;
    QPushButton *m_keyMImportBtn;
    QPlainTextEdit *m_keyMKeyLoaded;
    QVBoxLayout *m_keyMAlgVL;
    QHBoxLayout *m_keyMLabelHL;
    QLabel *m_keyMAlgLabel;
    QLabel *m_keyMModeLabel;
    QHBoxLayout *m_keyMAlgHL;
    QComboBox *m_keyMAlg;
    QComboBox *m_keyMMode;
    QPushButton *m_keyMGenerateBtn;
    QWidget *m_encryptPage;
    QWidget *verticalLayoutWidget_6;
    QVBoxLayout *m_encryptVL;
    QPlainTextEdit *m_encryptIntro;
    QPlainTextEdit *m_encryptKeyLoaded;
    QPushButton *m_encryptSelectFBtn;
    QPlainTextEdit *m_encryptSelectedF;
    QPushButton *m_encryptBtn;
    QWidget *m_decryptPage;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *m_decryptVL;
    QPlainTextEdit *m_decryptIntro;
    QPlainTextEdit *m_decryptLoadedKey;
    QPushButton *m_decryptSelectFBtn;
    QPlainTextEdit *m_decryptSelectedF;
    QPushButton *m_decryptBtn;
    QStatusBar *m_statusbar;
    QMenuBar *m_menubar;
    QToolBar *m_toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMaximumSize(QSize(800, 16777215));
        m_mainStack = new QStackedWidget(centralwidget);
        m_mainStack->setObjectName("m_mainStack");
        m_mainStack->setGeometry(QRect(10, 9, 781, 521));
        m_mainStack->setFrameShape(QFrame::NoFrame);
        m_keyMPage = new QWidget();
        m_keyMPage->setObjectName("m_keyMPage");
        verticalLayoutWidget = new QWidget(m_keyMPage);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 464, 291));
        m_keyMVL = new QVBoxLayout(verticalLayoutWidget);
        m_keyMVL->setObjectName("m_keyMVL");
        m_keyMVL->setContentsMargins(0, 0, 0, 0);
        m_keyMIntro = new QPlainTextEdit(verticalLayoutWidget);
        m_keyMIntro->setObjectName("m_keyMIntro");
        m_keyMIntro->setAutoFillBackground(false);
        m_keyMIntro->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        m_keyMIntro->setFrameShape(QFrame::NoFrame);
        m_keyMIntro->setFrameShadow(QFrame::Plain);
        m_keyMIntro->setTabChangesFocus(false);
        m_keyMIntro->setReadOnly(true);
        m_keyMIntro->setTextInteractionFlags(Qt::NoTextInteraction);
        m_keyMIntro->setBackgroundVisible(false);

        m_keyMVL->addWidget(m_keyMIntro);

        m_keyMImportBtn = new QPushButton(verticalLayoutWidget);
        m_keyMImportBtn->setObjectName("m_keyMImportBtn");

        m_keyMVL->addWidget(m_keyMImportBtn);

        m_keyMKeyLoaded = new QPlainTextEdit(verticalLayoutWidget);
        m_keyMKeyLoaded->setObjectName("m_keyMKeyLoaded");
        m_keyMKeyLoaded->setAutoFillBackground(false);
        m_keyMKeyLoaded->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        m_keyMKeyLoaded->setFrameShape(QFrame::NoFrame);
        m_keyMKeyLoaded->setFrameShadow(QFrame::Plain);
        m_keyMKeyLoaded->setTabChangesFocus(false);
        m_keyMKeyLoaded->setReadOnly(true);
        m_keyMKeyLoaded->setTextInteractionFlags(Qt::NoTextInteraction);
        m_keyMKeyLoaded->setBackgroundVisible(false);

        m_keyMVL->addWidget(m_keyMKeyLoaded);

        m_keyMAlgVL = new QVBoxLayout();
        m_keyMAlgVL->setObjectName("m_keyMAlgVL");
        m_keyMLabelHL = new QHBoxLayout();
        m_keyMLabelHL->setObjectName("m_keyMLabelHL");
        m_keyMAlgLabel = new QLabel(verticalLayoutWidget);
        m_keyMAlgLabel->setObjectName("m_keyMAlgLabel");

        m_keyMLabelHL->addWidget(m_keyMAlgLabel);

        m_keyMModeLabel = new QLabel(verticalLayoutWidget);
        m_keyMModeLabel->setObjectName("m_keyMModeLabel");

        m_keyMLabelHL->addWidget(m_keyMModeLabel);


        m_keyMAlgVL->addLayout(m_keyMLabelHL);

        m_keyMAlgHL = new QHBoxLayout();
        m_keyMAlgHL->setObjectName("m_keyMAlgHL");
        m_keyMAlg = new QComboBox(verticalLayoutWidget);
        m_keyMAlg->setObjectName("m_keyMAlg");

        m_keyMAlgHL->addWidget(m_keyMAlg);

        m_keyMMode = new QComboBox(verticalLayoutWidget);
        m_keyMMode->setObjectName("m_keyMMode");

        m_keyMAlgHL->addWidget(m_keyMMode);


        m_keyMAlgVL->addLayout(m_keyMAlgHL);


        m_keyMVL->addLayout(m_keyMAlgVL);

        m_keyMGenerateBtn = new QPushButton(verticalLayoutWidget);
        m_keyMGenerateBtn->setObjectName("m_keyMGenerateBtn");

        m_keyMVL->addWidget(m_keyMGenerateBtn);

        m_mainStack->addWidget(m_keyMPage);
        m_encryptPage = new QWidget();
        m_encryptPage->setObjectName("m_encryptPage");
        verticalLayoutWidget_6 = new QWidget(m_encryptPage);
        verticalLayoutWidget_6->setObjectName("verticalLayoutWidget_6");
        verticalLayoutWidget_6->setGeometry(QRect(0, 0, 431, 337));
        m_encryptVL = new QVBoxLayout(verticalLayoutWidget_6);
        m_encryptVL->setObjectName("m_encryptVL");
        m_encryptVL->setContentsMargins(0, 0, 0, 0);
        m_encryptIntro = new QPlainTextEdit(verticalLayoutWidget_6);
        m_encryptIntro->setObjectName("m_encryptIntro");
        m_encryptIntro->setAutoFillBackground(false);
        m_encryptIntro->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        m_encryptIntro->setFrameShape(QFrame::NoFrame);
        m_encryptIntro->setFrameShadow(QFrame::Plain);
        m_encryptIntro->setTabChangesFocus(false);
        m_encryptIntro->setReadOnly(true);
        m_encryptIntro->setTextInteractionFlags(Qt::NoTextInteraction);
        m_encryptIntro->setBackgroundVisible(false);

        m_encryptVL->addWidget(m_encryptIntro);

        m_encryptKeyLoaded = new QPlainTextEdit(verticalLayoutWidget_6);
        m_encryptKeyLoaded->setObjectName("m_encryptKeyLoaded");
        m_encryptKeyLoaded->setAutoFillBackground(false);
        m_encryptKeyLoaded->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        m_encryptKeyLoaded->setFrameShape(QFrame::NoFrame);
        m_encryptKeyLoaded->setFrameShadow(QFrame::Plain);
        m_encryptKeyLoaded->setTabChangesFocus(false);
        m_encryptKeyLoaded->setReadOnly(true);
        m_encryptKeyLoaded->setTextInteractionFlags(Qt::NoTextInteraction);
        m_encryptKeyLoaded->setBackgroundVisible(false);

        m_encryptVL->addWidget(m_encryptKeyLoaded);

        m_encryptSelectFBtn = new QPushButton(verticalLayoutWidget_6);
        m_encryptSelectFBtn->setObjectName("m_encryptSelectFBtn");

        m_encryptVL->addWidget(m_encryptSelectFBtn);

        m_encryptSelectedF = new QPlainTextEdit(verticalLayoutWidget_6);
        m_encryptSelectedF->setObjectName("m_encryptSelectedF");
        m_encryptSelectedF->setAutoFillBackground(false);
        m_encryptSelectedF->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        m_encryptSelectedF->setFrameShape(QFrame::NoFrame);
        m_encryptSelectedF->setFrameShadow(QFrame::Plain);
        m_encryptSelectedF->setTabChangesFocus(false);
        m_encryptSelectedF->setReadOnly(true);
        m_encryptSelectedF->setTextInteractionFlags(Qt::NoTextInteraction);
        m_encryptSelectedF->setBackgroundVisible(false);

        m_encryptVL->addWidget(m_encryptSelectedF);

        m_encryptBtn = new QPushButton(verticalLayoutWidget_6);
        m_encryptBtn->setObjectName("m_encryptBtn");

        m_encryptVL->addWidget(m_encryptBtn);

        m_mainStack->addWidget(m_encryptPage);
        m_decryptPage = new QWidget();
        m_decryptPage->setObjectName("m_decryptPage");
        verticalLayoutWidget_5 = new QWidget(m_decryptPage);
        verticalLayoutWidget_5->setObjectName("verticalLayoutWidget_5");
        verticalLayoutWidget_5->setGeometry(QRect(0, 0, 431, 337));
        m_decryptVL = new QVBoxLayout(verticalLayoutWidget_5);
        m_decryptVL->setObjectName("m_decryptVL");
        m_decryptVL->setContentsMargins(0, 0, 0, 0);
        m_decryptIntro = new QPlainTextEdit(verticalLayoutWidget_5);
        m_decryptIntro->setObjectName("m_decryptIntro");
        m_decryptIntro->setAutoFillBackground(false);
        m_decryptIntro->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        m_decryptIntro->setFrameShape(QFrame::NoFrame);
        m_decryptIntro->setFrameShadow(QFrame::Plain);
        m_decryptIntro->setTabChangesFocus(false);
        m_decryptIntro->setReadOnly(true);
        m_decryptIntro->setTextInteractionFlags(Qt::NoTextInteraction);
        m_decryptIntro->setBackgroundVisible(false);

        m_decryptVL->addWidget(m_decryptIntro);

        m_decryptLoadedKey = new QPlainTextEdit(verticalLayoutWidget_5);
        m_decryptLoadedKey->setObjectName("m_decryptLoadedKey");
        m_decryptLoadedKey->setAutoFillBackground(false);
        m_decryptLoadedKey->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        m_decryptLoadedKey->setFrameShape(QFrame::NoFrame);
        m_decryptLoadedKey->setFrameShadow(QFrame::Plain);
        m_decryptLoadedKey->setTabChangesFocus(false);
        m_decryptLoadedKey->setReadOnly(true);
        m_decryptLoadedKey->setTextInteractionFlags(Qt::NoTextInteraction);
        m_decryptLoadedKey->setBackgroundVisible(false);

        m_decryptVL->addWidget(m_decryptLoadedKey);

        m_decryptSelectFBtn = new QPushButton(verticalLayoutWidget_5);
        m_decryptSelectFBtn->setObjectName("m_decryptSelectFBtn");

        m_decryptVL->addWidget(m_decryptSelectFBtn);

        m_decryptSelectedF = new QPlainTextEdit(verticalLayoutWidget_5);
        m_decryptSelectedF->setObjectName("m_decryptSelectedF");
        m_decryptSelectedF->setAutoFillBackground(false);
        m_decryptSelectedF->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        m_decryptSelectedF->setFrameShape(QFrame::NoFrame);
        m_decryptSelectedF->setFrameShadow(QFrame::Plain);
        m_decryptSelectedF->setTabChangesFocus(false);
        m_decryptSelectedF->setReadOnly(true);
        m_decryptSelectedF->setTextInteractionFlags(Qt::NoTextInteraction);
        m_decryptSelectedF->setBackgroundVisible(false);

        m_decryptVL->addWidget(m_decryptSelectedF);

        m_decryptBtn = new QPushButton(verticalLayoutWidget_5);
        m_decryptBtn->setObjectName("m_decryptBtn");

        m_decryptVL->addWidget(m_decryptBtn);

        m_mainStack->addWidget(m_decryptPage);
        MainWindow->setCentralWidget(centralwidget);
        m_statusbar = new QStatusBar(MainWindow);
        m_statusbar->setObjectName("m_statusbar");
        MainWindow->setStatusBar(m_statusbar);
        m_menubar = new QMenuBar(MainWindow);
        m_menubar->setObjectName("m_menubar");
        m_menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(m_menubar);
        m_toolBar = new QToolBar(MainWindow);
        m_toolBar->setObjectName("m_toolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, m_toolBar);

        retranslateUi(MainWindow);

        m_mainStack->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "xKrypt", nullptr));
        m_keyMIntro->setPlainText(QCoreApplication::translate("MainWindow", "Key manager section.\n"
"Import key or generate one from selected algorithm.\n"
"", nullptr));
        m_keyMImportBtn->setText(QCoreApplication::translate("MainWindow", "Import key", nullptr));
        m_keyMKeyLoaded->setPlainText(QCoreApplication::translate("MainWindow", "no key loaded !", nullptr));
        m_keyMAlgLabel->setText(QCoreApplication::translate("MainWindow", "Algorithm:", nullptr));
        m_keyMModeLabel->setText(QCoreApplication::translate("MainWindow", "Mode:", nullptr));
        m_keyMGenerateBtn->setText(QCoreApplication::translate("MainWindow", "Generate key", nullptr));
        m_encryptIntro->setPlainText(QCoreApplication::translate("MainWindow", "Encrypt manager section.\n"
"Select file(s) to Encrypt.\n"
"", nullptr));
        m_encryptKeyLoaded->setPlainText(QCoreApplication::translate("MainWindow", "no key loaded", nullptr));
        m_encryptSelectFBtn->setText(QCoreApplication::translate("MainWindow", "Select file(s)", nullptr));
        m_encryptSelectedF->setPlainText(QCoreApplication::translate("MainWindow", "no file(s) selected", nullptr));
        m_encryptBtn->setText(QCoreApplication::translate("MainWindow", "Encrypt", nullptr));
        m_decryptIntro->setPlainText(QCoreApplication::translate("MainWindow", "Decrypt manager section.\n"
"Select file(s) to Decrypt.\n"
"", nullptr));
        m_decryptLoadedKey->setPlainText(QCoreApplication::translate("MainWindow", "no key loaded", nullptr));
        m_decryptSelectFBtn->setText(QCoreApplication::translate("MainWindow", "Select file(s)", nullptr));
        m_decryptSelectedF->setPlainText(QCoreApplication::translate("MainWindow", "no file(s) selecte", nullptr));
        m_decryptBtn->setText(QCoreApplication::translate("MainWindow", "Decrypt", nullptr));
        m_toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
