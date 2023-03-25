#ifndef KMESSAGE_H
#define KMESSAGE_H

#include "kDialogBase.h"
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>


class KMessage : public KDialogBase {
private:
    void setBtnRejectText(std::string text);

public :
    KMessage(QWidget* parent = nullptr);
    virtual ~KMessage();

protected slots:
    virtual void accept();
    virtual void reject();
};

#endif // KMESSAGE_H
