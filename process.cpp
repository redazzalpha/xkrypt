#include "process.h"
#include "defines.h"
#include <QProgressDialog>
#include <thread>
#include <iostream>
#include "mainwindow.h"

using namespace std;

// constructors
ProcessBar::ProcessBar(const std::string &label, const std::string &cancelButton, const int min, const int max)
    : m_label(label), m_cancelButton(cancelButton), m_min(min), m_max(max)
{}

// destructor
ProcessBar::~ProcessBar()
{}

// slots
void ProcessBar::process(MainWindow* win, MainWindow_ptr f, QStringList paths)
{
    size_t size = paths.size();
    QProgressDialog progress("processing please wait...", "cancel operation", 0, 0);
    progress.setMinimumDuration(0);
    progress.setMinimumWidth(PROCESS_BAR_WIDTH);
    progress.setWindowModality(Qt::WindowModal);
    progress.setMaximum(size);
    progress.setValue(0);

    size_t i;
    for (i = 0; i < size; i++) {
        progress.setValue(i);
        if(progress.wasCanceled()) break;
        (win->*f)(paths[i].toStdString());
        std::cout << "process thread round : " << i << std::endl;
    }
    progress.setValue(size);
    emit finished();

    string message = "Operation done successfully!<br />";
    message += "Using: " +
        win->cipher()->getAlgName() +=
        (" - " + win->cipher()->getModeName()) +
        " mode" + "<br />Succeeded: " + std::to_string(i) +
        " - Failed: " + std::to_string(size - i);
    emit success(message);
}
