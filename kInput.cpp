#include "kInput.h"

// constructors
KInput::KInput(QWidget* parent): KDialogBase(parent)  {
    initLayouts();
}

// destructor
KInput::~KInput() {
    delete m_field;
}

// methods
void KInput::initLayouts() {

    // message layout
    m_msgLayout->addWidget(m_messageIcon ,0, Qt::AlignCenter);
    m_msgLayout->addWidget(m_message, Qt::AlignCenter);

    // buttons layout
    m_btnLayout->setAlignment(Qt::AlignCenter);
    m_btnLayout->addWidget(m_btnReject);
    m_btnLayout->addWidget(m_btnAccept);

    // main layout
    m_mainLayout->addLayout(m_msgLayout);
    m_mainLayout->addWidget(m_field);
    m_mainLayout->addLayout(m_btnLayout);
}

// slots
void KInput::accept() {
    setVisible(false);
}
void KInput::reject() {
    setVisible(false);
}
