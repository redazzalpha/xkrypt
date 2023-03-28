#include "kDialogBase.h"
#include <iostream>

// constructors
KDialogBase::KDialogBase(QWidget* parent): QDialog(parent) {

    setMinimumSize(300, 100);
    setModal(true);
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
void KDialogBase::connectItems() {

    QObject::connect(m_btnAccept, &QPushButton::clicked, this, &QDialog::accept);
    QObject::connect(m_btnReject, &QPushButton::clicked, this, &QDialog::reject);

    QObject::connect(this, &QDialog::accepted, this, &KDialogBase::accept);
    QObject::connect(this, &QDialog::rejected, this, &KDialogBase::reject);
}

void KDialogBase::setMessage(const std::string& message) {
    m_message->setText(QString::fromStdString(message));
}
void KDialogBase::setBtnAcceptText(const std::string& text) {
    m_btnAccept->setText(QString::fromStdString(text));
}
void KDialogBase::setBtnRejectText(const std::string& text) {
    m_btnReject->setText(QString::fromStdString(text));
}
void KDialogBase::setIcon(const std::string& iconPath) {
    m_pixmap->load(QString::fromStdString(iconPath));
    // set QPixmap size
    m_messageIcon->setPixmap(m_pixmap->scaled(40, 40, Qt::KeepAspectRatio));
}
void KDialogBase::show(const std::string& message, const std::string& iconPath) {
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

void KDialogBase::closeDialog() {
    delete this;
}

QPushButton* KDialogBase::addButton(const std::string&) {return nullptr;}
QPushButton* KDialogBase::insertButton(const std::string&, const int) {return nullptr;}
