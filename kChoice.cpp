#include "kChoice.h"

// constructors
KChoice::KChoice(QWidget* parent): KDialogBase(parent)  {
    initLayouts();
}

// destructor
KChoice::~KChoice() {}

// methods
void KChoice::initLayouts() {

    // message layout
    m_msgLayout->addWidget(m_messageIcon ,0, Qt::AlignCenter);
    m_msgLayout->addWidget(m_message, Qt::AlignCenter);

    // buttons layout
    m_btnLayout->setAlignment(Qt::AlignCenter);
    m_btnLayout->addWidget(m_btnReject);
    m_btnLayout->addWidget(m_btnAccept);

    // main layout
    m_mainLayout->addLayout(m_msgLayout);
    m_mainLayout->addLayout(m_btnLayout);
}

void KChoice::closeDialog() {
    auto v = m_btnLayout->children();
    for(auto o : v) {delete o; o = nullptr;}
    KDialogBase::closeDialog();
}
QPushButton* KChoice::addButton(const std::string& text) {
    QPushButton* button = new QPushButton(QString::fromStdString(text));
    m_btnLayout->addWidget(button);
    QObject::connect(button, &QPushButton::clicked, this, &KChoice::execute);

    return button;
}
QPushButton* KChoice::insertButton(const std::string& text, int pos) {
    QPushButton* button = new QPushButton(QString::fromStdString(text));
    m_btnLayout->insertWidget(pos, button);
    QObject::connect(button, &QPushButton::clicked, this, &KChoice::execute);

    return button;
}

// slots
void KChoice::accept() {
    closeDialog();
}
void KChoice::reject() {
    closeDialog();
}
void KChoice::execute() {
    closeDialog();
}
