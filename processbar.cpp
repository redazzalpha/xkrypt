#include "processbar.h"
#include "defines.h"
#include <QPainter>
#include <QProgressDialog>
#include  <iostream>
#include <thread>

using namespace std;

// constructors
ProcessBar::ProcessBar(const string& label, const string& cancelButton, const int min, const int max)
    : m_label(label), m_cancelButton(cancelButton), m_min(min), m_max(max),
    m_progress(QString::fromStdString(m_label), QString::fromStdString(m_cancelButton), m_min, m_max)
{
    connectItems();
    m_progress.setMinimumWidth(PROCESS_BAR_WIDTH);
    m_progress.setMinimumDuration(0);
    m_progress.hide();
//    m_progress.cancel();
}

// methods
QProgressDialog &ProcessBar::progress()
{
    return m_progress;
}

// private methods
void ProcessBar::connectItems()
{
    QObject::connect(&m_progress, &QProgressDialog::canceled, this, &ProcessBar::kill);
    QObject::connect(&m_progress, &QProgressDialog::accepted, this, &ProcessBar::kill);
}

// slots
void ProcessBar::init()
{
    m_progress.setMinimumWidth(PROCESS_BAR_WIDTH);
    m_progress.setMinimumDuration(0);
}
void ProcessBar::kill()
{
    emit finished();
    m_progress.cancel();
    m_loop = false;
}
void ProcessBar::process()
{

    int i = 1;
    while(m_loop) {
        if(m_progress.wasCanceled()) kill();
        std::cout << "processing... : " <<  i++ << std::endl;
        std::this_thread::sleep_for(1s);
    }

    std::cout << "finished processing ..." << std::endl;
    emit finished();
}
