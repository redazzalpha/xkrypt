#include "process.h"
#include "defines.h"
#include <QProgressDialog>
#include <thread>
#include <iostream>

using namespace std;


// constructors

ProcessBar::ProcessBar(QWidget *parent, const std::string &label, const std::string &cancelButton, const int min, const int max)
    : m_parent(parent), m_label(label), m_cancelButton(cancelButton), m_min(min), m_max(max)
{}

// destructor
ProcessBar::~ProcessBar()
{
    if(m_progress != nullptr) delete m_progress;
}

// methods
void ProcessBar::init(const int max)
{
    m_progress = new QProgressDialog(QString::fromStdString(m_label), QString::fromStdString(m_cancelButton), m_min, m_max, m_parent);
    m_progress->setMinimumDuration(0);
    m_progress->setMinimumWidth(PROCESS_BAR_WIDTH);
    m_progress->setWindowFlags(Qt::CustomizeWindowHint | Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowStaysOnTopHint);
    m_progress->setWindowModality(Qt::WindowModal);
    m_progress->setMaximum(0);
    m_progress->setAutoClose(false);
    m_max = max;

    QObject::connect(m_progress, &QProgressDialog::canceled, this, &ProcessBar::killed);
    QObject::connect(m_progress, &QProgressDialog::accepted, this, &ProcessBar::killed);
}

// slots
void ProcessBar::processing(const int progress)
{
    if(progress > 0 && progress < m_max) {
        m_progress->setMaximum(m_max);
        m_progress->setValue(progress);
    }
    if(progress >= m_max) emit finished();
}
void ProcessBar::kill()
{
    if(m_progress) {
        delete m_progress;
        m_progress = nullptr;
    }
    emit finished();
}

