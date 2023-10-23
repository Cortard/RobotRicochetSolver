#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

class RicochetRobotSolver {
private:
    static QString address = "127.0.0.1";

public:
    static void setAddress(Qstring &add) {
        address = add;
    }

    static QString const getAddress() {
        return address;
    }
};

#endif // SETTINGS_H
