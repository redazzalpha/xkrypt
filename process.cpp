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
{}

// slots
void ProcessBar::process()
{
    QProgressDialog progress("processing please wait...", "cancel operation", 0, 0);
    progress.setMinimumDuration(0);
    progress.setMinimumWidth(PROCESS_BAR_WIDTH);
    progress.setModal(false);
    progress.setValue(0);

    std::cout << "process start here ! " << std::endl;
    for (int i = 0; i < 100; i++) {
        progress.setValue(i);
        if(progress.wasCanceled()) break;
        std::cout << "process thread round : " << i << std::endl;
        std::this_thread::sleep_for(1s);
    }
    progress.setValue(100);
    emit finished();

}
