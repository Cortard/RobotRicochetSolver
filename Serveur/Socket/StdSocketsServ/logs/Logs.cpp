//
// Created by cfaur on 19/11/2023.
//

#include "Logs.h"

std::ofstream Logs::file;

bool Logs::openLogs()
{
    Logs::file = std::ofstream(LOG_PATH);
    return file.is_open();
}

bool Logs::write(const std::string &msg, int level)
{
    if(!Logs::file.is_open()) return openLogs();

    time_t now = time(nullptr);
    std::string dt = ctime(&now);
    dt = dt.substr(0, dt.length() - 1);
    Logs::file<<dt<<": ";
    Logs::file<<msg;
    Logs::file<<" |"<<level;
    Logs::file<<std::endl;

    return true;
}

void Logs::close()
{
    Logs::file.close();
}

