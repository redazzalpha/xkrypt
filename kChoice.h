#ifndef KCHOICE_H
#define KCHOICE_H

#include "kDialogBase.h"

class KChoice : public KDialogBase {
public :
    // constructors
    KChoice(QWidget* parent = nullptr);

    // destructor
    virtual ~KChoice();

    // methods
private:
    void initLayouts();
    void closeDialog();

public:
    virtual QPushButton* addButton(const std::string& text) override;
    virtual QPushButton* insertButton(const std::string& text, const int pos) override;


public slots:
    virtual void accept() override;
    virtual void reject() override;
    virtual void execute();


};

#endif // KCHOICE_H
