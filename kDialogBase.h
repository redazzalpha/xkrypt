#ifndef KDIALOGBASE_H
#define KDIALOGBASE_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class KDialogBase : public QDialog {
protected:
    QLabel* m_message = new QLabel("No message set!");
    QPushButton* m_btnAccept = new QPushButton("Ok");
    QPushButton* m_btnReject = new QPushButton("No");
    QVBoxLayout* m_vlayout = new QVBoxLayout(this);
    QHBoxLayout* m_hlayout = new QHBoxLayout();

public :
    // constructors
    KDialogBase (QWidget* parent = nullptr);

    // destructor
    virtual ~KDialogBase();

    // methods
    void setMessage(std::string message);
    void setBtnAcceptText(std::string text);
    void setBtnRejectText(std::string text);

protected:
    void hideBtnAccept();
    void showBtnAccept();
    void hideBtnReject();
    void showBtnReject();

private:
    void initLayouts();
    void connectItems();

protected slots:
    virtual void accept() = 0;
    virtual void reject() = 0;

};

#endif // KDIALOGBASE_H
