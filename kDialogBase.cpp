#include "kDialogBase.h"
#include <QIcon>
#include <QPixmap>
#include <iostream>

// constructors
KDialogBase::KDialogBase(QWidget* parent): QDialog(parent) {

    QPixmap* pixmap = new QPixmap(":/assets/warning.png");
    QIcon* icon = new QIcon(*pixmap);
    setWindowIcon(*icon);


    setMinimumSize(300, 100);
    setModal(true);
    initLayouts();
    connectItems();
}

// destructor
KDialogBase::~KDialogBase() {
    delete m_message;
    delete m_btnAccept;
    delete m_btnReject;
    delete m_hlayout;
    delete m_vlayout;
}

// methods
void KDialogBase::initLayouts() {

    m_message->setAlignment(Qt::AlignCenter);
    m_hlayout->setAlignment(Qt::AlignCenter);

    // buttons layout
    m_hlayout->addWidget(m_btnReject, 0, Qt::AlignCenter);
    m_hlayout->addWidget(m_btnAccept, 0, Qt::AlignCenter);

    // main layout
    m_vlayout->addWidget(m_message, 0, Qt::AlignCenter);
    m_vlayout->addLayout(m_hlayout);
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

