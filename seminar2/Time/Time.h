#pragma once

#ifndef TIME_H
#define TIME_H

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

struct Time {
    int hours;
    int minutes;
    int seconds;
};

bool is_valid(Time const&);
std::string to_string(Time const&); 

bool is_am(Time const&);

Time operator+(Time&, int);
Time operator+(int, Time&);

Time operator-(Time&, int);
Time operator-(int, Time&);


Time& operator++(Time&);
Time operator++(Time&, int);

Time& operator--(Time&);
Time operator--(Time&, int);

bool operator<(Time const& t1, Time const& t2);
bool operator>(Time const& t1, Time const& t2);
bool operator==(Time const& t1, Time const& t2);
bool operator!=(Time const& t1, Time const& t2);
bool operator>=(Time const& t1, Time const& t2);
bool operator<=(Time const& t1, Time const& t2);

std::ostream& operator<<(std::ostream&, Time const&);
std::istream& operator>>( std::istream&, Time&);

#endif