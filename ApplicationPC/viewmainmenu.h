#ifndef VIEWMAINMENU_H
#define VIEWMAINMENU_H

#include <QWidget>

class viewMainMenu : public QObject
{
    Q_OBJECT
private:
    QWidget *widg;

public:
    viewMainMenu(QWidget *parent);

public slots:
};

#endif // VIEWMAINMENU_H
