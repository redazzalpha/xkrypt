#ifndef KDIALOGBASE_H
#define KDIALOGBASE_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QPixmap>

/**
 * KDialogBase class is abstract and represents QDialog object
 * This class is used to remplace QDialog object
 */

class KDialogBase : public QDialog {
protected:
    QLabel* m_message = new QLabel("No message set!");
    QPixmap* m_pixmap = new QPixmap();
    QLabel* m_messageIcon = new QLabel();
    QPushButton* m_btnAccept = new QPushButton("Ok");
    QPushButton* m_btnReject = new QPushButton("No");
    QVBoxLayout* m_mainLayout = new QVBoxLayout(this);
    QHBoxLayout* m_btnLayout = new QHBoxLayout();
    QHBoxLayout* m_msgLayout = new QHBoxLayout();

public :
    // constructors
    KDialogBase (QWidget* parent = nullptr);

    // destructor
    virtual ~KDialogBase();

    // methods
    void setMessage(std::string message);
    void setBtnAcceptText(std::string text);
    void setBtnRejectText(std::string text);
    void setIcon(std::string iconPath);
    void show(std::string message, std::string iconPath);

protected:
    void hideBtnAccept();
    void hideBtnReject();
    void showBtnAccept();
    void showBtnReject();

private:
    void initLayouts();
    void connectItems();

protected slots:
    virtual void accept() = 0;
    virtual void reject() = 0;

};

#endif // KDIALOGBASE_H
