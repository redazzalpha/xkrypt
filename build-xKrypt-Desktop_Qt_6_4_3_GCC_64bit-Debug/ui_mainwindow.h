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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
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
    QVBoxLayout *vlayout;
    QLabel *m_keyMIntro;
    QFrame *line_3;
    QSpacerItem *verticalSpacer_3;
    QLabel *label;
    QSpacerItem *verticalSpacer_5;
    QPushButton *m_keyMImportBtn;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_6;
    QVBoxLayout *vlayout_5;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout;
    QComboBox *m_keyMKeyLength;
    QPushButton *m_keyMGenerateBtn;
    QPushButton *m_keyMFlushBtn;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *hlayout;
    QCheckBox *m_keyMSaveOnF;
    QCheckBox *m_keyMshowKey;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QFrame *line_2;
    QPlainTextEdit *m_keyMKeyLoaded;
    QWidget *m_encryptPage;
    QWidget *verticalLayoutWidget_6;
    QVBoxLayout *vlayout_3;
    QPlainTextEdit *m_encryptIntro;
    QPlainTextEdit *m_encryptKeyLoaded;
    QPushButton *m_encryptSelectFBtn;
    QPlainTextEdit *m_encryptSelectedF;
    QVBoxLayout *vlayout_4;
    QHBoxLayout *hlayout_3;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QHBoxLayout *hlayout_4;
    QComboBox *m_keyMAlgs_2;
    QComboBox *m_keyMModes_2;
    QComboBox *m_keyMKeys_2;
    QPushButton *m_encryptBtn;
    QWidget *m_decryptPage;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *vlayout_2;
    QPlainTextEdit *m_decryptIntro;
    QPlainTextEdit *m_decryptLoadedKey;
    QPushButton *m_decryptSelectFBtn;
    QPlainTextEdit *m_decryptSelectedF;
    QVBoxLayout *vlayout_1;
    QHBoxLayout *hlayout_1;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QHBoxLayout *hlayout_2;
    QComboBox *m_keyMAlgs;
    QComboBox *m_keyMModes;
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
        verticalLayoutWidget->setGeometry(QRect(0, 0, 464, 491));
        vlayout = new QVBoxLayout(verticalLayoutWidget);
        vlayout->setObjectName("vlayout");
        vlayout->setContentsMargins(0, 0, 0, 0);
        m_keyMIntro = new QLabel(verticalLayoutWidget);
        m_keyMIntro->setObjectName("m_keyMIntro");

        vlayout->addWidget(m_keyMIntro);

        line_3 = new QFrame(verticalLayoutWidget);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        vlayout->addWidget(line_3);

        verticalSpacer_3 = new QSpacerItem(20, 220, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vlayout->addItem(verticalSpacer_3);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");
        QFont font;
        font.setBold(true);
        font.setUnderline(true);
        label->setFont(font);

        vlayout->addWidget(label);

        verticalSpacer_5 = new QSpacerItem(20, 200, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vlayout->addItem(verticalSpacer_5);

        m_keyMImportBtn = new QPushButton(verticalLayoutWidget);
        m_keyMImportBtn->setObjectName("m_keyMImportBtn");
        m_keyMImportBtn->setMaximumSize(QSize(120, 16777215));

        vlayout->addWidget(m_keyMImportBtn);

        verticalSpacer = new QSpacerItem(20, 220, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vlayout->addItem(verticalSpacer);

        line = new QFrame(verticalLayoutWidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        vlayout->addWidget(line);

        verticalSpacer_4 = new QSpacerItem(20, 220, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vlayout->addItem(verticalSpacer_4);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");
        QFont font1;
        font1.setBold(true);
        font1.setUnderline(true);
        font1.setStrikeOut(false);
        font1.setKerning(true);
        label_2->setFont(font1);
        label_2->setMargin(0);

        vlayout->addWidget(label_2);

        verticalSpacer_6 = new QSpacerItem(20, 200, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vlayout->addItem(verticalSpacer_6);

        vlayout_5 = new QVBoxLayout();
        vlayout_5->setObjectName("vlayout_5");
        label_13 = new QLabel(verticalLayoutWidget);
        label_13->setObjectName("label_13");

        vlayout_5->addWidget(label_13);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        m_keyMKeyLength = new QComboBox(verticalLayoutWidget);
        m_keyMKeyLength->setObjectName("m_keyMKeyLength");
        m_keyMKeyLength->setMinimumSize(QSize(70, 0));

        horizontalLayout->addWidget(m_keyMKeyLength);

        m_keyMGenerateBtn = new QPushButton(verticalLayoutWidget);
        m_keyMGenerateBtn->setObjectName("m_keyMGenerateBtn");
        m_keyMGenerateBtn->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(m_keyMGenerateBtn);

        m_keyMFlushBtn = new QPushButton(verticalLayoutWidget);
        m_keyMFlushBtn->setObjectName("m_keyMFlushBtn");
        m_keyMFlushBtn->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(m_keyMFlushBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        vlayout_5->addLayout(horizontalLayout);


        vlayout->addLayout(vlayout_5);

        hlayout = new QHBoxLayout();
        hlayout->setObjectName("hlayout");
        m_keyMSaveOnF = new QCheckBox(verticalLayoutWidget);
        m_keyMSaveOnF->setObjectName("m_keyMSaveOnF");
        m_keyMSaveOnF->setMaximumSize(QSize(100, 16777215));

        hlayout->addWidget(m_keyMSaveOnF);

        m_keyMshowKey = new QCheckBox(verticalLayoutWidget);
        m_keyMshowKey->setObjectName("m_keyMshowKey");
        m_keyMshowKey->setChecked(true);
        m_keyMshowKey->setTristate(false);

        hlayout->addWidget(m_keyMshowKey);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hlayout->addItem(horizontalSpacer);


        vlayout->addLayout(hlayout);

        verticalSpacer_2 = new QSpacerItem(20, 220, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vlayout->addItem(verticalSpacer_2);

        line_2 = new QFrame(verticalLayoutWidget);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        vlayout->addWidget(line_2);

        m_keyMKeyLoaded = new QPlainTextEdit(verticalLayoutWidget);
        m_keyMKeyLoaded->setObjectName("m_keyMKeyLoaded");
        m_keyMKeyLoaded->setAutoFillBackground(false);
        m_keyMKeyLoaded->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);color:red;"));
        m_keyMKeyLoaded->setFrameShape(QFrame::NoFrame);
        m_keyMKeyLoaded->setFrameShadow(QFrame::Plain);
        m_keyMKeyLoaded->setTabChangesFocus(false);
        m_keyMKeyLoaded->setReadOnly(true);
        m_keyMKeyLoaded->setTextInteractionFlags(Qt::NoTextInteraction);
        m_keyMKeyLoaded->setBackgroundVisible(false);

        vlayout->addWidget(m_keyMKeyLoaded);

        m_mainStack->addWidget(m_keyMPage);
        m_encryptPage = new QWidget();
        m_encryptPage->setObjectName("m_encryptPage");
        verticalLayoutWidget_6 = new QWidget(m_encryptPage);
        verticalLayoutWidget_6->setObjectName("verticalLayoutWidget_6");
        verticalLayoutWidget_6->setGeometry(QRect(0, 0, 431, 340));
        vlayout_3 = new QVBoxLayout(verticalLayoutWidget_6);
        vlayout_3->setObjectName("vlayout_3");
        vlayout_3->setContentsMargins(0, 0, 0, 0);
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

        vlayout_3->addWidget(m_encryptIntro);

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

        vlayout_3->addWidget(m_encryptKeyLoaded);

        m_encryptSelectFBtn = new QPushButton(verticalLayoutWidget_6);
        m_encryptSelectFBtn->setObjectName("m_encryptSelectFBtn");

        vlayout_3->addWidget(m_encryptSelectFBtn);

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

        vlayout_3->addWidget(m_encryptSelectedF);

        vlayout_4 = new QVBoxLayout();
        vlayout_4->setObjectName("vlayout_4");
        hlayout_3 = new QHBoxLayout();
        hlayout_3->setObjectName("hlayout_3");
        label_8 = new QLabel(verticalLayoutWidget_6);
        label_8->setObjectName("label_8");

        hlayout_3->addWidget(label_8);

        label_9 = new QLabel(verticalLayoutWidget_6);
        label_9->setObjectName("label_9");

        hlayout_3->addWidget(label_9);

        label_10 = new QLabel(verticalLayoutWidget_6);
        label_10->setObjectName("label_10");

        hlayout_3->addWidget(label_10);


        vlayout_4->addLayout(hlayout_3);

        hlayout_4 = new QHBoxLayout();
        hlayout_4->setObjectName("hlayout_4");
        m_keyMAlgs_2 = new QComboBox(verticalLayoutWidget_6);
        m_keyMAlgs_2->setObjectName("m_keyMAlgs_2");

        hlayout_4->addWidget(m_keyMAlgs_2);

        m_keyMModes_2 = new QComboBox(verticalLayoutWidget_6);
        m_keyMModes_2->setObjectName("m_keyMModes_2");

        hlayout_4->addWidget(m_keyMModes_2);

        m_keyMKeys_2 = new QComboBox(verticalLayoutWidget_6);
        m_keyMKeys_2->setObjectName("m_keyMKeys_2");

        hlayout_4->addWidget(m_keyMKeys_2);


        vlayout_4->addLayout(hlayout_4);


        vlayout_3->addLayout(vlayout_4);

        m_encryptBtn = new QPushButton(verticalLayoutWidget_6);
        m_encryptBtn->setObjectName("m_encryptBtn");

        vlayout_3->addWidget(m_encryptBtn);

        m_mainStack->addWidget(m_encryptPage);
        m_decryptPage = new QWidget();
        m_decryptPage->setObjectName("m_decryptPage");
        verticalLayoutWidget_5 = new QWidget(m_decryptPage);
        verticalLayoutWidget_5->setObjectName("verticalLayoutWidget_5");
        verticalLayoutWidget_5->setGeometry(QRect(0, 0, 431, 340));
        vlayout_2 = new QVBoxLayout(verticalLayoutWidget_5);
        vlayout_2->setObjectName("vlayout_2");
        vlayout_2->setContentsMargins(0, 0, 0, 0);
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

        vlayout_2->addWidget(m_decryptIntro);

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

        vlayout_2->addWidget(m_decryptLoadedKey);

        m_decryptSelectFBtn = new QPushButton(verticalLayoutWidget_5);
        m_decryptSelectFBtn->setObjectName("m_decryptSelectFBtn");

        vlayout_2->addWidget(m_decryptSelectFBtn);

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

        vlayout_2->addWidget(m_decryptSelectedF);

        vlayout_1 = new QVBoxLayout();
        vlayout_1->setObjectName("vlayout_1");
        hlayout_1 = new QHBoxLayout();
        hlayout_1->setObjectName("hlayout_1");
        label_5 = new QLabel(verticalLayoutWidget_5);
        label_5->setObjectName("label_5");

        hlayout_1->addWidget(label_5);

        label_6 = new QLabel(verticalLayoutWidget_5);
        label_6->setObjectName("label_6");

        hlayout_1->addWidget(label_6);

        label_7 = new QLabel(verticalLayoutWidget_5);
        label_7->setObjectName("label_7");

        hlayout_1->addWidget(label_7);


        vlayout_1->addLayout(hlayout_1);

        hlayout_2 = new QHBoxLayout();
        hlayout_2->setObjectName("hlayout_2");
        m_keyMAlgs = new QComboBox(verticalLayoutWidget_5);
        m_keyMAlgs->setObjectName("m_keyMAlgs");

        hlayout_2->addWidget(m_keyMAlgs);

        m_keyMModes = new QComboBox(verticalLayoutWidget_5);
        m_keyMModes->setObjectName("m_keyMModes");

        hlayout_2->addWidget(m_keyMModes);


        vlayout_1->addLayout(hlayout_2);


        vlayout_2->addLayout(vlayout_1);

        m_decryptBtn = new QPushButton(verticalLayoutWidget_5);
        m_decryptBtn->setObjectName("m_decryptBtn");

        vlayout_2->addWidget(m_decryptBtn);

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
        m_keyMIntro->setText(QCoreApplication::translate("MainWindow", "Key manager section.\n"
"Import key or generate one from selected algorithm.\n"
"", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Import key:", nullptr));
        m_keyMImportBtn->setText(QCoreApplication::translate("MainWindow", "Select file(s)", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Generate key:", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "key (bits):", nullptr));
        m_keyMGenerateBtn->setText(QCoreApplication::translate("MainWindow", "Generate", nullptr));
        m_keyMFlushBtn->setText(QCoreApplication::translate("MainWindow", "Flush key", nullptr));
        m_keyMSaveOnF->setText(QCoreApplication::translate("MainWindow", "save on file", nullptr));
        m_keyMshowKey->setText(QCoreApplication::translate("MainWindow", "show key", nullptr));
        m_keyMKeyLoaded->setPlainText(QCoreApplication::translate("MainWindow", "no key loaded !", nullptr));
        m_encryptIntro->setPlainText(QCoreApplication::translate("MainWindow", "Encrypt manager section.\n"
"Select file(s) to Encrypt.\n"
"", nullptr));
        m_encryptKeyLoaded->setPlainText(QCoreApplication::translate("MainWindow", "no key loaded", nullptr));
        m_encryptSelectFBtn->setText(QCoreApplication::translate("MainWindow", "Select file(s)", nullptr));
        m_encryptSelectedF->setPlainText(QCoreApplication::translate("MainWindow", "no file(s) selected", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Algorithm:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Mode:", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "key (bits):", nullptr));
        m_encryptBtn->setText(QCoreApplication::translate("MainWindow", "Encrypt", nullptr));
        m_decryptIntro->setPlainText(QCoreApplication::translate("MainWindow", "Decrypt manager section.\n"
"Select file(s) to Decrypt.\n"
"", nullptr));
        m_decryptLoadedKey->setPlainText(QCoreApplication::translate("MainWindow", "no key loaded", nullptr));
        m_decryptSelectFBtn->setText(QCoreApplication::translate("MainWindow", "Select file(s)", nullptr));
        m_decryptSelectedF->setPlainText(QCoreApplication::translate("MainWindow", "no file(s) selected", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Algorithm:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Mode:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "key (bits):", nullptr));
        m_decryptBtn->setText(QCoreApplication::translate("MainWindow", "Decrypt", nullptr));
        m_toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
