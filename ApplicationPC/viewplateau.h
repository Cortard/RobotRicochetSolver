#ifndef VIEWPLATEAU_H
#define VIEWPLATEAU_H

#include <QWidget>

class viewPlateau : public QObject
{
    Q_OBJECT
private:
    QWidget *widg2;
public:
    viewPlateau(QWidget *parent);
};

#endif // VIEWPLATEAU_H
