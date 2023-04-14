#include "processbar.h"
#include "defines.h"

#include <QProgressDialog>
#include <iostream>
#include <thread>
using namespace std;

ProcessBar::ProcessBar(QWidget *parent) : m_parent(parent) {}

void ProcessBar::process()
{
    QProgressDialog progress("Copying files...", "Abort Copy", 0, 10, nullptr);
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumWidth(PROGRESS_BAR_WIDTH);
    progress.setMinimumDuration(0);

    for (int i = 0; i < 10; i++) {
        progress.setValue(i);

        if (progress.wasCanceled()) break;
        std::this_thread::sleep_for(1s);
    }
    progress.setValue(10);
    emit finished();
}
