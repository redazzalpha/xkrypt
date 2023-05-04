#include "processbar.h"
#include "defines.h"

#include <QVBoxLayout>
#include <iostream>

using namespace std;

// constructors
ProcessBar::ProcessBar(
    QWidget* parent,
    const string& labelText,
    const string& cancelButton,
    const int min, const int max)
    : QDialog(parent)
{
    m_parent = parent;
    m_label = labelText;
    m_cancelButton = cancelButton;
    m_min = min;
    m_max = max;

    setup();
    initLayouts();
}

// methods
void ProcessBar::setMax(const int max)
{
    m_max = max;
}

// private methods
void ProcessBar::setup() {

    m_progress.setParent(m_parent);
    m_progress.setMinimum(m_min);
    m_progress.setMaximum(m_min);

    setWindowTitle("xkrypt - process");
    setWindowFlags(Qt::CustomizeWindowHint | Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::WindowModal);
    setMinimumWidth(PROCESS_BAR_WIDTH);
}
void ProcessBar::initLayouts()
{
    QPushButton* button = new QPushButton(QString::fromStdString(m_cancelButton));
    QLabel* label = new QLabel(QString::fromStdString(m_label));
    QVBoxLayout* vlayout = new QVBoxLayout;
    QHBoxLayout* hlayout = new QHBoxLayout;

    button->setMaximumWidth(125);
    label->setText(QString::fromStdString(m_label));
    label->setAlignment(Qt::AlignCenter);

    hlayout->setAlignment(Qt::AlignRight);
    hlayout->addWidget(button, Qt::AlignRight);

    vlayout->addWidget(label);
    vlayout->addWidget(&m_progress);
    vlayout->addLayout(hlayout);

    setLayout(vlayout);
}

// slots
void ProcessBar::proceed(const int progress)
{
    if(progress > 0)
        m_progress.setMaximum(m_max);
    m_progress.setValue(progress);
}
