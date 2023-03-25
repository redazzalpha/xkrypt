#ifndef KACTIONBASE_H
#define KACTIONBASE_H

#include <QAction>
#include <QMainWindow>

/**
 * KActionBase class is abstract and represent QAction object
 * and that contains QPixmap, QIcon objects
 * and set toolTip.
 * This class is used to remplace QAction object
 * with all needed.
 */

enum Page {encrypt , generate, decrypt};

class KActionBase: public QAction {

    Q_OBJECT

protected:
    QPixmap m_pixmap;
    QIcon m_icon;

public:
    // constructor
    KActionBase(std::string toolTipText, std::string iconPath);

    // destructor
    virtual ~KActionBase();

public slots:
    virtual void onActionClick() = 0;

signals:
    void setStackPage(int page);
    void quit();
};

#endif // KACTIONBASE_H
