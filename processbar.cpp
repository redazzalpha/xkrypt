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
    m_labelText = labelText;
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
void ProcessBar::setMin(const int min)
{
    m_min = min;
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
    QVBoxLayout* vlayout = new QVBoxLayout;
    QHBoxLayout* hlayout = new QHBoxLayout;
    m_label = new QLabel(QString::fromStdString(m_labelText));
    m_sublabel = new QLabel;
    m_button = new QPushButton(QString::fromStdString(m_cancelButton));

    m_button->setMaximumWidth(125);
    m_label->setAlignment(Qt::AlignCenter);

    hlayout->setAlignment(Qt::AlignRight);
    hlayout->addWidget(m_sublabel, Qt::AlignLeft);
    hlayout->addWidget(m_button, Qt::AlignRight);

    vlayout->addWidget(m_label);
    vlayout->addWidget(&m_progress);
    vlayout->addLayout(hlayout);

    setLayout(vlayout);

    QObject::connect(m_button, &QPushButton::clicked, this, &ProcessBar::cancel);
}

// slots
void ProcessBar::proceed(const int progress)
{
    if(progress > 0)
        m_progress.setMaximum(m_max);
    m_progress.setValue(progress);
    string sublabel = "processing: ";
    sublabel += std::to_string(progress+1) + "/" + std::to_string(m_max);
    m_sublabel->setText(QString::fromStdString(sublabel));
}
void ProcessBar::cancel()
{
    m_label->setText("Canceling operation please wait...");
    m_button->setEnabled(false);
    m_progress.setMaximum(m_min);
    emit canceled();
}
void ProcessBar::show()
{

    m_button->setEnabled(true);
    m_progress.setMaximum(m_min);
    string sublabel = "processing: ";
    sublabel += std::to_string(1) + "/" + std::to_string(m_max);
    m_sublabel->setText(QString::fromStdString(sublabel));
    QDialog::show();
}
