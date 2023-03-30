#ifndef KACTIONBASE_H
#define KACTIONBASE_H

#include <QAction>
#include <QMainWindow>

/**
 * KActionBase class is abstract and represents QAction object
 * This class is used to remplace QAction object
 */

class KActionBase: public QAction {
    Q_OBJECT

protected:
    QPixmap m_pixmap;
    QIcon m_icon;

public:
    // constructor
    KActionBase(const std::string& toolTipText, const std::string& iconPath);

    // destructor
    virtual ~KActionBase();

public slots:
    virtual void onActionClick() = 0;

signals:
    void setStackPage(const int page);
    void quit();
};

#endif // KACTIONBASE_H
