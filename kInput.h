#ifndef KINPUT_H
#define KINPUT_H

#include "kDialogBase.h"
#include <QLineEdit>

class KInput : public KDialogBase {
    // data members
private:
    QLineEdit* m_field = new QLineEdit();

public :
    // constructors
    KInput(QWidget* parent = nullptr);

    // destructor
    virtual ~KInput();

    // methods
private:
    void initLayouts();


public slots:
    virtual void accept() override;
    virtual void reject() override;

};

#endif // KINPUT_H
