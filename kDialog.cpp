#include "kDialog.h"
#include <iostream>

// constructors
KDialog::KDialog(QWidget* parent): QDialog(parent) {

    setMinimumSize(300, 100);
    initVLayout();
}

// destructor
KDialog::~KDialog() {
    delete m_message;
    delete m_btnOk;
    delete m_btnNo;
    delete m_vlayout;
}

// methods
void KDialog::initVLayout() {
    m_vlayout->addWidget(m_message, 0, Qt::AlignCenter);
    m_vlayout->addWidget(m_btnOk, 0, Qt::AlignCenter);
}

void KDialog::setMessage(std::string message) {
    m_message->setText(QString::fromStdString(message));
}
