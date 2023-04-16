#ifndef PROCESSBAR_H
#define PROCESSBAR_H

#include <QObject>
#include <QProgressDialog>

class ProcessBar : public QObject {
    Q_OBJECT

private:
    std::string m_label;
    std::string m_cancelButton;
    int m_min;
    int m_max;
    QProgressDialog m_progress;
    bool m_loop = true;

public:
    // constructors
    ProcessBar(const std::string& label = "Processing please wait...", const std::string& cancelButton = "Cancel operation", const int min = 0, const int max = 0);

    // methods
    QProgressDialog& progress();

private:
    void connectItems();


public slots:
    void init();
    void process();
    void kill();

signals:
    void finished();
};

#endif // PROCESSBAR_H
