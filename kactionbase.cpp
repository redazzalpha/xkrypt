#include "kactionbase.h"
#include <iostream>

// constructors
KActionBase::KActionBase(const std::string& toolTipText, const std::string& iconPath)
{
    m_pixmap = QPixmap(QString::fromStdString(iconPath));
    m_icon = QIcon(m_pixmap);
    setToolTip(QString::fromStdString(toolTipText));
    setIcon(m_icon);
}

// destructor
KActionBase::~KActionBase(){}
