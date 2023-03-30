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
    QWidget *m_pageKeyM;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *vlayout;
    QLabel *m_label;
    QFrame *line_3;
    QSpacerItem *spacer;
    QLabel *label;
    QSpacerItem *spacer_15;
    QPushButton *m_keyMImport;
    QSpacerItem *spacer_2;
    QFrame *line;
    QSpacerItem *spacer_3;
    QLabel *label_2;
    QSpacerItem *spacer_16;
    QVBoxLayout *vlayout_5;
    QHBoxLayout *hlayout_5;
    QLabel *label_13;
    QLabel *label_4;
    QSpacerItem *spacer_4;
    QHBoxLayout *hlayout_6;
    QComboBox *m_keyMLength;
    QComboBox *m_keyMEncoding;
    QPushButton *m_keyMGenerate;
    QSpacerItem *spacer_5;
    QHBoxLayout *hlayout_7;
    QPushButton *m_keyMFlush;
    QSpacerItem *spacer_6;
    QHBoxLayout *hlayout;
    QCheckBox *m_keyMSaveOnF;
    QCheckBox *m_keyMshowKey;
    QSpacerItem *spacer_13;
    QSpacerItem *spacer_14;
    QFrame *line_2;
    QLabel *label_3;
    QPlainTextEdit *m_keyMLoaded;
    QWidget *m_pageEnc;
    QWidget *verticalLayoutWidget_6;
    QVBoxLayout *vlayout_3;
    QLabel *m_label_6;
    QPlainTextEdit *m_encLoaded;
    QPushButton *m_encImport;
    QPlainTextEdit *m_encSelected;
    QVBoxLayout *vlayout_4;
    QHBoxLayout *hlayout_3;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QHBoxLayout *hlayout_4;
    QComboBox *m_encAlgs;
    QComboBox *m_encModes;
    QPushButton *m_encEncrypt;
    QWidget *m_pageDec;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *vlayout_2;
    QLabel *m_label_2;
    QPlainTextEdit *m_decLoaded;
    QPushButton *m_decImport;
    QPlainTextEdit *m_decSelected;
    QVBoxLayout *vlayout_1;
    QHBoxLayout *hlayout_1;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QHBoxLayout *hlayout_2;
    QComboBox *m_decAlgs;
    QComboBox *m_decModes;
    QPushButton *m_decDecrypt;
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
        m_pageKeyM = new QWidget();
        m_pageKeyM->setObjectName("m_pageKeyM");
        verticalLayoutWidget = new QWidget(m_pageKeyM);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 464, 491));
        vlayout = new QVBoxLayout(verticalLayoutWidget);
        vlayout->setObjectName("vlayout");
        vlayout->setContentsMargins(0, 0, 0, 0);
        m_label = new QLabel(verticalLayoutWidget);
        m_label->setObjectName("m_label");

        vlayout->addWidget(m_label);

        line_3 = new QFrame(verticalLayoutWidget);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        vlayout->addWidget(line_3);

        spacer = new QSpacerItem(20, 220, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vlayout->addItem(spacer);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");
        QFont font;
        font.setBold(true);
        font.setUnderline(true);
        label->setFont(font);

        vlayout->addWidget(label);

        spacer_15 = new QSpacerItem(20, 200, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vlayout->addItem(spacer_15);

        m_keyMImport = new QPushButton(verticalLayoutWidget);
        m_keyMImport->setObjectName("m_keyMImport");
        m_keyMImport->setMaximumSize(QSize(120, 16777215));

        vlayout->addWidget(m_keyMImport);

        spacer_2 = new QSpacerItem(20, 220, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vlayout->addItem(spacer_2);

        line = new QFrame(verticalLayoutWidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        vlayout->addWidget(line);

        spacer_3 = new QSpacerItem(20, 220, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vlayout->addItem(spacer_3);

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

        spacer_16 = new QSpacerItem(20, 200, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vlayout->addItem(spacer_16);

        vlayout_5 = new QVBoxLayout();
        vlayout_5->setObjectName("vlayout_5");
        hlayout_5 = new QHBoxLayout();
        hlayout_5->setObjectName("hlayout_5");
        label_13 = new QLabel(verticalLayoutWidget);
        label_13->setObjectName("label_13");
        label_13->setMinimumSize(QSize(70, 0));

        hlayout_5->addWidget(label_13);

        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName("label_4");

        hlayout_5->addWidget(label_4);

        spacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hlayout_5->addItem(spacer_4);


        vlayout_5->addLayout(hlayout_5);

        hlayout_6 = new QHBoxLayout();
        hlayout_6->setObjectName("hlayout_6");
        m_keyMLength = new QComboBox(verticalLayoutWidget);
        m_keyMLength->setObjectName("m_keyMLength");
        m_keyMLength->setMinimumSize(QSize(70, 0));

        hlayout_6->addWidget(m_keyMLength);

        m_keyMEncoding = new QComboBox(verticalLayoutWidget);
        m_keyMEncoding->setObjectName("m_keyMEncoding");
        m_keyMEncoding->setMinimumSize(QSize(70, 0));

        hlayout_6->addWidget(m_keyMEncoding);

        m_keyMGenerate = new QPushButton(verticalLayoutWidget);
        m_keyMGenerate->setObjectName("m_keyMGenerate");
        m_keyMGenerate->setMaximumSize(QSize(120, 16777215));

        hlayout_6->addWidget(m_keyMGenerate);

        spacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hlayout_6->addItem(spacer_5);


        vlayout_5->addLayout(hlayout_6);

        hlayout_7 = new QHBoxLayout();
        hlayout_7->setObjectName("hlayout_7");
        m_keyMFlush = new QPushButton(verticalLayoutWidget);
        m_keyMFlush->setObjectName("m_keyMFlush");
        m_keyMFlush->setMaximumSize(QSize(120, 16777215));

        hlayout_7->addWidget(m_keyMFlush);

        spacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hlayout_7->addItem(spacer_6);


        vlayout_5->addLayout(hlayout_7);


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

        spacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hlayout->addItem(spacer_13);


        vlayout->addLayout(hlayout);

        spacer_14 = new QSpacerItem(20, 220, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vlayout->addItem(spacer_14);

        line_2 = new QFrame(verticalLayoutWidget);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        vlayout->addWidget(line_2);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName("label_3");
        label_3->setFont(font);

        vlayout->addWidget(label_3);

        m_keyMLoaded = new QPlainTextEdit(verticalLayoutWidget);
        m_keyMLoaded->setObjectName("m_keyMLoaded");
        m_keyMLoaded->setAutoFillBackground(false);
        m_keyMLoaded->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);color:red;"));
        m_keyMLoaded->setFrameShape(QFrame::NoFrame);
        m_keyMLoaded->setFrameShadow(QFrame::Plain);
        m_keyMLoaded->setTabChangesFocus(false);
        m_keyMLoaded->setReadOnly(true);
        m_keyMLoaded->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        m_keyMLoaded->setBackgroundVisible(false);

        vlayout->addWidget(m_keyMLoaded);

        m_mainStack->addWidget(m_pageKeyM);
        m_pageEnc = new QWidget();
        m_pageEnc->setObjectName("m_pageEnc");
        verticalLayoutWidget_6 = new QWidget(m_pageEnc);
        verticalLayoutWidget_6->setObjectName("verticalLayoutWidget_6");
        verticalLayoutWidget_6->setGeometry(QRect(0, 0, 431, 340));
        vlayout_3 = new QVBoxLayout(verticalLayoutWidget_6);
        vlayout_3->setObjectName("vlayout_3");
        vlayout_3->setContentsMargins(0, 0, 0, 0);
        m_label_6 = new QLabel(verticalLayoutWidget_6);
        m_label_6->setObjectName("m_label_6");

        vlayout_3->addWidget(m_label_6);

        m_encLoaded = new QPlainTextEdit(verticalLayoutWidget_6);
        m_encLoaded->setObjectName("m_encLoaded");
        m_encLoaded->setAutoFillBackground(false);
        m_encLoaded->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        m_encLoaded->setFrameShape(QFrame::NoFrame);
        m_encLoaded->setFrameShadow(QFrame::Plain);
        m_encLoaded->setTabChangesFocus(false);
        m_encLoaded->setReadOnly(true);
        m_encLoaded->setTextInteractionFlags(Qt::NoTextInteraction);
        m_encLoaded->setBackgroundVisible(false);

        vlayout_3->addWidget(m_encLoaded);

        m_encImport = new QPushButton(verticalLayoutWidget_6);
        m_encImport->setObjectName("m_encImport");

        vlayout_3->addWidget(m_encImport);

        m_encSelected = new QPlainTextEdit(verticalLayoutWidget_6);
        m_encSelected->setObjectName("m_encSelected");
        m_encSelected->setAutoFillBackground(false);
        m_encSelected->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        m_encSelected->setFrameShape(QFrame::NoFrame);
        m_encSelected->setFrameShadow(QFrame::Plain);
        m_encSelected->setTabChangesFocus(false);
        m_encSelected->setReadOnly(true);
        m_encSelected->setTextInteractionFlags(Qt::NoTextInteraction);
        m_encSelected->setBackgroundVisible(false);

        vlayout_3->addWidget(m_encSelected);

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
        m_encAlgs = new QComboBox(verticalLayoutWidget_6);
        m_encAlgs->setObjectName("m_encAlgs");

        hlayout_4->addWidget(m_encAlgs);

        m_encModes = new QComboBox(verticalLayoutWidget_6);
        m_encModes->setObjectName("m_encModes");

        hlayout_4->addWidget(m_encModes);


        vlayout_4->addLayout(hlayout_4);


        vlayout_3->addLayout(vlayout_4);

        m_encEncrypt = new QPushButton(verticalLayoutWidget_6);
        m_encEncrypt->setObjectName("m_encEncrypt");

        vlayout_3->addWidget(m_encEncrypt);

        m_mainStack->addWidget(m_pageEnc);
        m_pageDec = new QWidget();
        m_pageDec->setObjectName("m_pageDec");
        verticalLayoutWidget_5 = new QWidget(m_pageDec);
        verticalLayoutWidget_5->setObjectName("verticalLayoutWidget_5");
        verticalLayoutWidget_5->setGeometry(QRect(0, 0, 431, 340));
        vlayout_2 = new QVBoxLayout(verticalLayoutWidget_5);
        vlayout_2->setObjectName("vlayout_2");
        vlayout_2->setContentsMargins(0, 0, 0, 0);
        m_label_2 = new QLabel(verticalLayoutWidget_5);
        m_label_2->setObjectName("m_label_2");

        vlayout_2->addWidget(m_label_2);

        m_decLoaded = new QPlainTextEdit(verticalLayoutWidget_5);
        m_decLoaded->setObjectName("m_decLoaded");
        m_decLoaded->setAutoFillBackground(false);
        m_decLoaded->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        m_decLoaded->setFrameShape(QFrame::NoFrame);
        m_decLoaded->setFrameShadow(QFrame::Plain);
        m_decLoaded->setTabChangesFocus(false);
        m_decLoaded->setReadOnly(true);
        m_decLoaded->setTextInteractionFlags(Qt::NoTextInteraction);
        m_decLoaded->setBackgroundVisible(false);

        vlayout_2->addWidget(m_decLoaded);

        m_decImport = new QPushButton(verticalLayoutWidget_5);
        m_decImport->setObjectName("m_decImport");

        vlayout_2->addWidget(m_decImport);

        m_decSelected = new QPlainTextEdit(verticalLayoutWidget_5);
        m_decSelected->setObjectName("m_decSelected");
        m_decSelected->setAutoFillBackground(false);
        m_decSelected->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        m_decSelected->setFrameShape(QFrame::NoFrame);
        m_decSelected->setFrameShadow(QFrame::Plain);
        m_decSelected->setTabChangesFocus(false);
        m_decSelected->setReadOnly(true);
        m_decSelected->setTextInteractionFlags(Qt::NoTextInteraction);
        m_decSelected->setBackgroundVisible(false);

        vlayout_2->addWidget(m_decSelected);

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
        m_decAlgs = new QComboBox(verticalLayoutWidget_5);
        m_decAlgs->setObjectName("m_decAlgs");

        hlayout_2->addWidget(m_decAlgs);

        m_decModes = new QComboBox(verticalLayoutWidget_5);
        m_decModes->setObjectName("m_decModes");

        hlayout_2->addWidget(m_decModes);


        vlayout_1->addLayout(hlayout_2);


        vlayout_2->addLayout(vlayout_1);

        m_decDecrypt = new QPushButton(verticalLayoutWidget_5);
        m_decDecrypt->setObjectName("m_decDecrypt");

        vlayout_2->addWidget(m_decDecrypt);

        m_mainStack->addWidget(m_pageDec);
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
        m_label->setText(QCoreApplication::translate("MainWindow", "Key manager section.\n"
"Import key or generate one from selected algorithm.\n"
"", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Import key", nullptr));
        m_keyMImport->setText(QCoreApplication::translate("MainWindow", "Select file(s)", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Generate key", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "key (bits)", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Encoding", nullptr));
        m_keyMGenerate->setText(QCoreApplication::translate("MainWindow", "Generate", nullptr));
        m_keyMFlush->setText(QCoreApplication::translate("MainWindow", "Flush key", nullptr));
        m_keyMSaveOnF->setText(QCoreApplication::translate("MainWindow", "save on file", nullptr));
        m_keyMshowKey->setText(QCoreApplication::translate("MainWindow", "show key", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Loaded key", nullptr));
        m_keyMLoaded->setPlainText(QCoreApplication::translate("MainWindow", "no key loaded !", nullptr));
        m_label_6->setText(QCoreApplication::translate("MainWindow", "Encrypt manager section.\n"
"Select file(s) to Decrypt.\n"
"", nullptr));
        m_encLoaded->setPlainText(QCoreApplication::translate("MainWindow", "no key loaded", nullptr));
        m_encImport->setText(QCoreApplication::translate("MainWindow", "Select file(s)", nullptr));
        m_encSelected->setPlainText(QCoreApplication::translate("MainWindow", "no file(s) selected", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Algorithm:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Mode:", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "key (bits):", nullptr));
        m_encEncrypt->setText(QCoreApplication::translate("MainWindow", "Encrypt", nullptr));
        m_label_2->setText(QCoreApplication::translate("MainWindow", "Decrypt manager section.\n"
"Select file(s) to Decrypt.\n"
"", nullptr));
        m_decLoaded->setPlainText(QCoreApplication::translate("MainWindow", "no key loaded", nullptr));
        m_decImport->setText(QCoreApplication::translate("MainWindow", "Select file(s)", nullptr));
        m_decSelected->setPlainText(QCoreApplication::translate("MainWindow", "no file(s) selected", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Algorithm:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Mode:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "key (bits):", nullptr));
        m_decDecrypt->setText(QCoreApplication::translate("MainWindow", "Decrypt", nullptr));
        m_toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
