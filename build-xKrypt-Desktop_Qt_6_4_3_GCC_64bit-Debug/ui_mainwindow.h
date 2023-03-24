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
    QStackedWidget *mainStack;
    QWidget *page_encrypt;
    QWidget *verticalLayoutWidget_6;
    QVBoxLayout *verticalLayout_6;
    QPlainTextEdit *plainTextEdit_12;
    QPlainTextEdit *plainTextEdit_15;
    QPushButton *btn_selectFilesToEncrypt;
    QPlainTextEdit *plainTextEdit_13;
    QPushButton *btn_encrypt;
    QWidget *page_keyManager;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit_2;
    QPushButton *btn_importKey;
    QPlainTextEdit *plainTextEdit;
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *btn_generateKey;
    QWidget *page_decrypt;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_5;
    QPlainTextEdit *plainTextEdit_10;
    QPlainTextEdit *plainTextEdit_14;
    QPushButton *btn_selectFilesToDecrypt;
    QPlainTextEdit *plainTextEdit_11;
    QPushButton *btn_decrypt;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMaximumSize(QSize(800, 16777215));
        mainStack = new QStackedWidget(centralwidget);
        mainStack->setObjectName("mainStack");
        mainStack->setGeometry(QRect(10, 9, 781, 521));
        mainStack->setFrameShape(QFrame::NoFrame);
        page_encrypt = new QWidget();
        page_encrypt->setObjectName("page_encrypt");
        verticalLayoutWidget_6 = new QWidget(page_encrypt);
        verticalLayoutWidget_6->setObjectName("verticalLayoutWidget_6");
        verticalLayoutWidget_6->setGeometry(QRect(0, 0, 431, 337));
        verticalLayout_6 = new QVBoxLayout(verticalLayoutWidget_6);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        plainTextEdit_12 = new QPlainTextEdit(verticalLayoutWidget_6);
        plainTextEdit_12->setObjectName("plainTextEdit_12");
        plainTextEdit_12->setAutoFillBackground(false);
        plainTextEdit_12->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        plainTextEdit_12->setFrameShape(QFrame::NoFrame);
        plainTextEdit_12->setFrameShadow(QFrame::Plain);
        plainTextEdit_12->setTabChangesFocus(false);
        plainTextEdit_12->setReadOnly(true);
        plainTextEdit_12->setTextInteractionFlags(Qt::NoTextInteraction);
        plainTextEdit_12->setBackgroundVisible(false);

        verticalLayout_6->addWidget(plainTextEdit_12);

        plainTextEdit_15 = new QPlainTextEdit(verticalLayoutWidget_6);
        plainTextEdit_15->setObjectName("plainTextEdit_15");
        plainTextEdit_15->setAutoFillBackground(false);
        plainTextEdit_15->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        plainTextEdit_15->setFrameShape(QFrame::NoFrame);
        plainTextEdit_15->setFrameShadow(QFrame::Plain);
        plainTextEdit_15->setTabChangesFocus(false);
        plainTextEdit_15->setReadOnly(true);
        plainTextEdit_15->setTextInteractionFlags(Qt::NoTextInteraction);
        plainTextEdit_15->setBackgroundVisible(false);

        verticalLayout_6->addWidget(plainTextEdit_15);

        btn_selectFilesToEncrypt = new QPushButton(verticalLayoutWidget_6);
        btn_selectFilesToEncrypt->setObjectName("btn_selectFilesToEncrypt");

        verticalLayout_6->addWidget(btn_selectFilesToEncrypt);

        plainTextEdit_13 = new QPlainTextEdit(verticalLayoutWidget_6);
        plainTextEdit_13->setObjectName("plainTextEdit_13");
        plainTextEdit_13->setAutoFillBackground(false);
        plainTextEdit_13->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        plainTextEdit_13->setFrameShape(QFrame::NoFrame);
        plainTextEdit_13->setFrameShadow(QFrame::Plain);
        plainTextEdit_13->setTabChangesFocus(false);
        plainTextEdit_13->setReadOnly(true);
        plainTextEdit_13->setTextInteractionFlags(Qt::NoTextInteraction);
        plainTextEdit_13->setBackgroundVisible(false);

        verticalLayout_6->addWidget(plainTextEdit_13);

        btn_encrypt = new QPushButton(verticalLayoutWidget_6);
        btn_encrypt->setObjectName("btn_encrypt");

        verticalLayout_6->addWidget(btn_encrypt);

        mainStack->addWidget(page_encrypt);
        page_keyManager = new QWidget();
        page_keyManager->setObjectName("page_keyManager");
        verticalLayoutWidget = new QWidget(page_keyManager);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 391, 291));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        plainTextEdit_2 = new QPlainTextEdit(verticalLayoutWidget);
        plainTextEdit_2->setObjectName("plainTextEdit_2");
        plainTextEdit_2->setAutoFillBackground(false);
        plainTextEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        plainTextEdit_2->setFrameShape(QFrame::NoFrame);
        plainTextEdit_2->setFrameShadow(QFrame::Plain);
        plainTextEdit_2->setTabChangesFocus(false);
        plainTextEdit_2->setReadOnly(true);
        plainTextEdit_2->setTextInteractionFlags(Qt::NoTextInteraction);
        plainTextEdit_2->setBackgroundVisible(false);

        verticalLayout->addWidget(plainTextEdit_2);

        btn_importKey = new QPushButton(verticalLayoutWidget);
        btn_importKey->setObjectName("btn_importKey");

        verticalLayout->addWidget(btn_importKey);

        plainTextEdit = new QPlainTextEdit(verticalLayoutWidget);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setAutoFillBackground(false);
        plainTextEdit->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        plainTextEdit->setFrameShape(QFrame::NoFrame);
        plainTextEdit->setFrameShadow(QFrame::Plain);
        plainTextEdit->setTabChangesFocus(false);
        plainTextEdit->setReadOnly(true);
        plainTextEdit->setTextInteractionFlags(Qt::NoTextInteraction);
        plainTextEdit->setBackgroundVisible(false);

        verticalLayout->addWidget(plainTextEdit);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        comboBox = new QComboBox(verticalLayoutWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        verticalLayout->addWidget(comboBox);

        btn_generateKey = new QPushButton(verticalLayoutWidget);
        btn_generateKey->setObjectName("btn_generateKey");

        verticalLayout->addWidget(btn_generateKey);

        mainStack->addWidget(page_keyManager);
        page_decrypt = new QWidget();
        page_decrypt->setObjectName("page_decrypt");
        verticalLayoutWidget_5 = new QWidget(page_decrypt);
        verticalLayoutWidget_5->setObjectName("verticalLayoutWidget_5");
        verticalLayoutWidget_5->setGeometry(QRect(0, 0, 431, 337));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        plainTextEdit_10 = new QPlainTextEdit(verticalLayoutWidget_5);
        plainTextEdit_10->setObjectName("plainTextEdit_10");
        plainTextEdit_10->setAutoFillBackground(false);
        plainTextEdit_10->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        plainTextEdit_10->setFrameShape(QFrame::NoFrame);
        plainTextEdit_10->setFrameShadow(QFrame::Plain);
        plainTextEdit_10->setTabChangesFocus(false);
        plainTextEdit_10->setReadOnly(true);
        plainTextEdit_10->setTextInteractionFlags(Qt::NoTextInteraction);
        plainTextEdit_10->setBackgroundVisible(false);

        verticalLayout_5->addWidget(plainTextEdit_10);

        plainTextEdit_14 = new QPlainTextEdit(verticalLayoutWidget_5);
        plainTextEdit_14->setObjectName("plainTextEdit_14");
        plainTextEdit_14->setAutoFillBackground(false);
        plainTextEdit_14->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        plainTextEdit_14->setFrameShape(QFrame::NoFrame);
        plainTextEdit_14->setFrameShadow(QFrame::Plain);
        plainTextEdit_14->setTabChangesFocus(false);
        plainTextEdit_14->setReadOnly(true);
        plainTextEdit_14->setTextInteractionFlags(Qt::NoTextInteraction);
        plainTextEdit_14->setBackgroundVisible(false);

        verticalLayout_5->addWidget(plainTextEdit_14);

        btn_selectFilesToDecrypt = new QPushButton(verticalLayoutWidget_5);
        btn_selectFilesToDecrypt->setObjectName("btn_selectFilesToDecrypt");

        verticalLayout_5->addWidget(btn_selectFilesToDecrypt);

        plainTextEdit_11 = new QPlainTextEdit(verticalLayoutWidget_5);
        plainTextEdit_11->setObjectName("plainTextEdit_11");
        plainTextEdit_11->setAutoFillBackground(false);
        plainTextEdit_11->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0);"));
        plainTextEdit_11->setFrameShape(QFrame::NoFrame);
        plainTextEdit_11->setFrameShadow(QFrame::Plain);
        plainTextEdit_11->setTabChangesFocus(false);
        plainTextEdit_11->setReadOnly(true);
        plainTextEdit_11->setTextInteractionFlags(Qt::NoTextInteraction);
        plainTextEdit_11->setBackgroundVisible(false);

        verticalLayout_5->addWidget(plainTextEdit_11);

        btn_decrypt = new QPushButton(verticalLayoutWidget_5);
        btn_decrypt->setObjectName("btn_decrypt");

        verticalLayout_5->addWidget(btn_decrypt);

        mainStack->addWidget(page_decrypt);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        mainStack->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "xKrypt", nullptr));
        plainTextEdit_12->setPlainText(QCoreApplication::translate("MainWindow", "Encrypt manager section.\n"
"Select file(s) to Encrypt.\n"
"", nullptr));
        plainTextEdit_15->setPlainText(QCoreApplication::translate("MainWindow", "no key loaded", nullptr));
        btn_selectFilesToEncrypt->setText(QCoreApplication::translate("MainWindow", "Select file(s)", nullptr));
        plainTextEdit_13->setPlainText(QCoreApplication::translate("MainWindow", "no file(s) selected", nullptr));
        btn_encrypt->setText(QCoreApplication::translate("MainWindow", "Encrypt", nullptr));
        plainTextEdit_2->setPlainText(QCoreApplication::translate("MainWindow", "Key manager section.\n"
"Import key or generate one from selected algorithm.\n"
"", nullptr));
        btn_importKey->setText(QCoreApplication::translate("MainWindow", "Import key", nullptr));
        plainTextEdit->setPlainText(QCoreApplication::translate("MainWindow", "no key loaded !", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Select Algorithm", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Symmectric - Aes", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Asymmetric - Rsa", nullptr));

        btn_generateKey->setText(QCoreApplication::translate("MainWindow", "Generate key", nullptr));
        plainTextEdit_10->setPlainText(QCoreApplication::translate("MainWindow", "Decrypt manager section.\n"
"Select file(s) to Decrypt.\n"
"", nullptr));
        plainTextEdit_14->setPlainText(QCoreApplication::translate("MainWindow", "no key loaded", nullptr));
        btn_selectFilesToDecrypt->setText(QCoreApplication::translate("MainWindow", "Select file(s)", nullptr));
        plainTextEdit_11->setPlainText(QCoreApplication::translate("MainWindow", "no file(s) selecte", nullptr));
        btn_decrypt->setText(QCoreApplication::translate("MainWindow", "Decrypt", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
