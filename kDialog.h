#ifndef KDIALOG_H
#define KDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>


class KDialog : public QDialog {
private:
    QLabel* m_message = new QLabel();
    QPushButton* m_btnOk = new QPushButton("Ok");
    QPushButton* m_btnNo = new QPushButton("No");
    QVBoxLayout* m_vlayout = new QVBoxLayout(this);



public :
    // constructors
    KDialog (QWidget* parent = nullptr);

    // destructor
    virtual ~KDialog();

    // methods
    void setMessage(std::string);


private:
    void initMessage();
    void initVLayout();

};

#endif // KDIALOG_H
