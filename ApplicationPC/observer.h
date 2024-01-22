#pragma once
#include <QVector>

class Observer {
public:
    virtual ~Observer() {}
    virtual void updateModel() = 0;
};

class Observable {
private:
    QVector<Observer*> observers;
public:
    virtual ~Observable() {}
    virtual void addObserver(Observer* observer) { observers.append(observer); }
    virtual void removeObserver(Observer* observer) { observers.removeAll(observer); }
    virtual void notifyObserver() const { for (Observer* obs : observers) obs->updateModel(); }
};
