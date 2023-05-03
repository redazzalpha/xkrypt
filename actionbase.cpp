#include "actionbase.h"
#include <iostream>

// constructors
AbstractActionBase::AbstractActionBase(const std::string& toolTipText, const std::string& iconPath)
{
    setIcon(iconPath);
    setToolTip(QString::fromStdString(toolTipText));
}

std::string AbstractActionBase::iconPath()
{
    return m_iconPath;
}

// destructor
AbstractActionBase::~AbstractActionBase(){}

void AbstractActionBase::setIcon(const std::string &iconPath)
{
    m_iconPath = iconPath;
    m_pixmap = QPixmap(QString::fromStdString(m_iconPath));
    m_icon = QIcon(m_pixmap);
    QAction::setIcon(m_icon);
}
