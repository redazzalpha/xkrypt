#ifndef ACTIONBASE_H
#define ACTIONBASE_H

#include <QAction>
#include <QMainWindow>

/**
 * KActionBase class is abstract and represents QAction object
 * This class is used to remplace QAction object
 */

class AbstractActionBase: public QAction {
    Q_OBJECT

protected:
    QPixmap m_pixmap;
    QIcon m_icon;

public:
    // constructor
    AbstractActionBase(const std::string& toolTipText, const std::string& iconPath);

    // destructor
    virtual ~AbstractActionBase();

public slots:
    virtual void onActionClick() = 0;

signals:
    void setStackPage(const int page);
    void quit();
};

#endif // ACTIONBASE_H
