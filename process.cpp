#include "process.h"
#include "defines.h"
#include <QProgressDialog>
#include <thread>
#include <iostream>

using namespace std;


// constructors

ProcessBar::ProcessBar(const std::string &label, const std::string &cancelButton, const int min, const int max)
    : m_label(label), m_cancelButton(cancelButton), m_min(min), m_max(max)
{}

// destructor
ProcessBar::~ProcessBar()
{
    if(m_progress != nullptr) delete m_progress;
}

// methods
void ProcessBar::init(const int max)
{
    std::cout << "int start int here ! " << std::endl;

    m_progress = new QProgressDialog(QString::fromStdString(m_label), QString::fromStdString(m_cancelButton), m_min, m_max);
    m_progress->setMinimumDuration(0);
    m_progress->setMinimumWidth(PROCESS_BAR_WIDTH);
    m_progress->setWindowModality(Qt::WindowModal);
    m_progress->setMaximum(0);
    m_max = max;
}

// slots
void ProcessBar::processing(const int progress)
{
    std::cout << "process start process here ! " << std::endl;

    if(progress > 0 && progress < m_max) m_progress->setValue(progress);
    if(progress >= m_max) emit finished();
}
void ProcessBar::kill()
{
    m_progress->close();
    delete m_progress;
    m_progress = nullptr;
}


