#ifndef PROCESSBAR_H
#define PROCESSBAR_H

#include <QDialog>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>

class ProcessBar : public QDialog {
    Q_OBJECT

private:
    QWidget* m_parent;
    QProgressBar m_progress;
    std::string m_label;
    std::string m_cancelButton;
    int m_min;
    int m_max;

public:
    // constructors
    ProcessBar(
        QWidget* parent = nullptr,
        const std::string& labelText = "Processing please wait...",
        const std::string& cancelButton = "Cancel operation",
        const int min = 0, const int max = 0
    );

    // methods
    void setMax(const int max = 1);

private:
    void setup();
    void initLayouts();

public slots:
    void proceed(const int progress);
};

#endif // PROCESSBAR_H
