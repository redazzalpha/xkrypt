#include "actionbase.h"
#include <iostream>

// constructors
AbstractAction::AbstractAction(const std::string& toolTipText, const std::string& iconPath)
{
    setIcon(iconPath);
    setToolTip(QString::fromStdString(toolTipText));
}

std::string AbstractAction::iconPath()
{
    return m_iconPath;
}

// destructor
AbstractAction::~AbstractAction(){}

void AbstractAction::setIcon(const std::string &iconPath)
{
    m_iconPath = iconPath;
    m_pixmap = QPixmap(QString::fromStdString(m_iconPath));
    m_icon = QIcon(m_pixmap);
    QAction::setIcon(m_icon);
}
