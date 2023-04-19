#ifndef PROCESS_H
#define PROCESS_H


#include <QObject>
#include <QProgressDialog>

class MainWindow;
using MainWindow_ptr = void (MainWindow::*)(const std::string&);

class ProcessBar : public QObject {
    Q_OBJECT
private:
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
    //dstructor
    ~ProcessBar();
    void setValue(const int value);

public slots:
    void process(MainWindow *win, MainWindow_ptr f, QStringList paths);

signals:
    void finished();
    void success(const std::string& success);
    void fail(const std::string& fail);

};

#endif // PROCESS_H
