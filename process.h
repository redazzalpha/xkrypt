#ifndef PROCESS_H
#define PROCESS_H


#include <QObject>
#include <QProgressDialog>

class ProcessBar : public QObject {
    Q_OBJECT
private:
    QProgressDialog* m_progress = nullptr;
    std::string m_label;
    std::string m_cancelButton;
    int m_min;
    int m_max;

public :
    //constructor
    ProcessBar(
        const std::string& label = "Processing please wait...",
        const std::string& cancelButton = "Cancel operation",
        const int min = 0, const int max = 0
    );

    //destructor
    ~ProcessBar();

    // methods
    void init(const int max = 0 );

public slots:
    void processing(const int progress);
    void kill();

signals:
    void finished();
};

#endif // PROCESS_H
