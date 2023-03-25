#include "kDialogBase.h"
#include <iostream>

// constructors
KDialogBase::KDialogBase(QWidget* parent): QDialog(parent) {

    setMinimumSize(300, 100);
    setModal(true);
    initLayouts();
    connectItems();
}

// destructor
KDialogBase::~KDialogBase() {

    delete m_pixmap;
    delete m_messageIcon;
    delete m_message;
    delete m_msgLayout;

    delete m_btnAccept;
    delete m_btnReject;
    delete m_btnLayout;

    delete m_mainLayout;
}

// methods
void KDialogBase::initLayouts() {

    m_message->setAlignment(Qt::AlignCenter);

    // message layout
    m_msgLayout->setAlignment(Qt::AlignCenter);
    m_msgLayout->addWidget(m_messageIcon ,0, Qt::AlignCenter);
    m_msgLayout->addWidget(m_message, Qt::AlignCenter);

    // buttons layout
    m_btnLayout->setAlignment(Qt::AlignCenter);
    m_btnLayout->addWidget(m_btnReject, 0, Qt::AlignCenter);
    m_btnLayout->addWidget(m_btnAccept, 0, Qt::AlignCenter);

    // main layout
    m_mainLayout->addLayout(m_msgLayout);
    m_mainLayout->addLayout(m_btnLayout);
}
void KDialogBase::connectItems() {

    QObject::connect(m_btnAccept, &QPushButton::clicked, this, &QDialog::accept);
    QObject::connect(m_btnReject, &QPushButton::clicked, this, &QDialog::reject);

    QObject::connect(this, &QDialog::accepted, this, &KDialogBase::accept);
    QObject::connect(this, &QDialog::rejected, this, &KDialogBase::reject);
}

void KDialogBase::setMessage(std::string message) {
    m_message->setText(QString::fromStdString(message));
}
void KDialogBase::setBtnAcceptText(std::string text) {
    m_btnAccept->setText(QString::fromStdString(text));
}
void KDialogBase::setBtnRejectText(std::string text) {
    m_btnReject->setText(QString::fromStdString(text));
}
void KDialogBase::setIcon(std::string iconPath) {
    m_pixmap->load(QString::fromStdString(iconPath));
    m_messageIcon->setPixmap(m_pixmap->scaled(55, 55, Qt::KeepAspectRatio));
}
void KDialogBase::show(std::string message, std::string iconPath) {
    setIcon(iconPath);
    setMessage(message);
    exec();
}

void KDialogBase::hideBtnAccept() {
    m_btnAccept->setVisible(false);
}
void KDialogBase::hideBtnReject() {
    m_btnReject->setVisible(false);
}
void KDialogBase::showBtnAccept() {
    m_btnAccept->setVisible(true);
}
void KDialogBase::showBtnReject() {
    m_btnReject->setVisible(true);
}

