#ifndef PROCESSBAR_H
#define PROCESSBAR_H

#include <QWidget>

class ProcessBar : public QObject {
    Q_OBJECT

private:
    QWidget* m_parent;
public:
    // constructors
    ProcessBar(QWidget* parent);

public slots:
    void process();
signals:
    void finished();
};

#endif // PROCESSBAR_H
