#ifndef KMESSAGE_H
#define KMESSAGE_H

#include "kDialogBase.h"
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

/**
 * KMessage class represents QDialog object
 * inherits from KDialogBase and handles messages
 * to user from GUI
 */

class KMessage : public KDialogBase {
private:
    void setBtnRejectText(const std::string& text);

public :
    // constructors
    KMessage(QWidget* parent = nullptr);

    // destructor
    virtual ~KMessage();


protected slots:
    virtual void accept() override;
    virtual void reject() override;
};

#endif // KMESSAGE_H
