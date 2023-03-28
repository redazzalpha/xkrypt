#include "kMessage.h"
#include <iostream>

// constructors
KMessage::KMessage(QWidget* parent): KDialogBase(parent)  {
    initLayouts();
}

// destructor
KMessage::~KMessage() {}

// methods
void KMessage::initLayouts() {

    // message layout
    m_msgLayout->addWidget(m_messageIcon ,0, Qt::AlignCenter);
    m_msgLayout->addWidget(m_message, Qt::AlignCenter);

    // buttons layout
    m_btnLayout->setAlignment(Qt::AlignCenter);
    m_btnLayout->addWidget(m_btnAccept);

    // main layout
    m_mainLayout->addLayout(m_msgLayout);
    m_mainLayout->addLayout(m_btnLayout);

}

// slots
void KMessage::accept() {
    setVisible(false);
}
void KMessage::reject() {
    setVisible(false);
}
