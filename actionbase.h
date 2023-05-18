#ifndef ACTIONBASE_H
#define ACTIONBASE_H

#include <QAction>
#include <QMainWindow>

/**
 * KActionBase class is abstract and represents QAction object
 * This class is used to remplace QAction object
 */

class AbstractAction: public QAction {
    Q_OBJECT

protected:
    QPixmap m_pixmap;
    QIcon m_icon;
    std::string m_iconPath;

public:
    // constructor
    AbstractAction(const std::string& toolTipText, const std::string& iconPath);
    std::string iconPath();

    // destructor
    virtual ~AbstractAction();

    // methods
    void setIcon(const std::string& iconPath);

public slots:
    virtual void onActionClick() = 0;

signals:
    void setStackPage(const int page);
    void quit();
};

#endif // ACTIONBASE_H
