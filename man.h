#ifndef MAN_H
#define MAN_H

#include <iostream>
#include <QObject>

class Man : public QObject {
    Q_OBJECT

private:
    int m_age;
    std::string m_name;

public:
    void fctEmitSignal(){
        emit fctSignal();
    }
signals:
    void fctSignal();
public slots:
void fctSlot();

};

#endif // MAN_H
