#include "process.h"
#include "defines.h"

#include <QProgressDialog>
#include <thread>
#include <iostream>

using namespace std;

// slots
ProcessBar::ProcessBar(const std::string &label, const std::string &cancelButton, const int min, const int max)
    : m_label(label), m_cancelButton(cancelButton), m_min(min), m_max(max)
{}

ProcessBar::~ProcessBar()
{
    delete m_progress;
}

void ProcessBar::setValue(const int value)
{
    m_progress->setValue(value);
}
void ProcessBar::init()
{
    std::cout << "init process here" << std::endl;

    m_progress = new QProgressDialog("processing please wait...", "cancel operation", 0, 100);
    m_progress->setMinimumDuration(0);
    m_progress->setMinimumWidth(PROCESS_BAR_WIDTH);
    m_progress->setWindowModality(Qt::WindowModal);
}
void ProcessBar::process()
{

    for (int i = 1; i < 100; i++) {
        m_progress->setValue(i);
        if(m_progress->wasCanceled()) break;
        std::cout << "in the process thread round : " << i << std::endl;
        std::this_thread::sleep_for(1s);
    }
    m_progress->setValue(100);
    emit finished();
}

