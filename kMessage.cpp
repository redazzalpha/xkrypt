#include "kMessage.h"
#include <iostream>

// constructors
KMessage::KMessage(QWidget* parent): KDialogBase(parent)  {
    hideBtnReject();
}

// destructor
KMessage::~KMessage() {}

// slots
void KMessage::accept() {
    setVisible(false);
}
void KMessage::reject() {
    setVisible(false);
}
