#include "Time.h"

bool is_valid(Time const& t) {
    return (t.hours < 24 && t.hours >=0) &&
        (t.minutes < 60 && t.minutes >=0) && 
        (t.seconds < 60 && t.seconds >=0);
}
std::string to_string(Time const& t) {
    std::stringstream ss {};
    ss << std::setfill('0')
        << std::setw(2) << t.hours   << ':'
        << std::setw(2) << t.minutes << ':'
        << std::setw(2) << t.seconds;

    return ss.str();
} 

bool is_am(Time const& t) {
    return t.hours>=0 && t.hours<12;
}

Time operator+(Time& t, int n) {
    Time tmp{t};
    tmp.seconds += n;

    tmp.minutes += tmp.seconds / 60;
    tmp.seconds %= 60;

    tmp.hours += tmp.minutes / 60;
    tmp.minutes %= 60;
    tmp.hours %= 24;

    return tmp;

}
Time operator+(int n, Time& t) {
    Time tmp {t};
    return tmp + n;
}

Time operator-(Time& t, int n) {
    Time tmp {t};
    tmp.seconds -= n;
    while (tmp.seconds < 0) {
        tmp.seconds += 60;
        --tmp.minutes;
    }

    while (tmp.minutes < 0) {
        tmp.minutes += 60;
        --tmp.hours;
    }

    while (tmp.hours < 0) {
        tmp.hours += 24;
    }
    return tmp;
}
Time operator-(int n, Time& t) {
    Time tmp {t};
    return t - n;
}


Time& operator++(Time& t) {
    t = t + 1;
    return t;

}
Time operator++(Time& t, int) {
    Time tmp {t};
    ++t;
    return tmp;
}

Time& operator--(Time& t) {
    t = t - 1;
    return t;
}
Time operator--(Time& t, int) {
    Time tmp {t};
    ++t;
    return tmp;
}
bool operator<(Time const& t1, Time const& t2) {
    return (t1.hours < t2.hours) || 
        (t1.hours == t2.hours && (t1.minutes < t2.minutes || 
        (t1.minutes == t2.minutes && t1.seconds < t2.seconds)));
}
bool operator>(Time const& t1, Time const& t2) {
    return !(t1 == t2 || t1 < t2);
}
bool operator==(Time const& t1, Time const& t2) {
    return t1.hours == t2.hours && 
        t1.minutes == t2.minutes && 
        t1.seconds == t2.seconds;
}
bool operator!=(Time const& t1, Time const& t2) {
    return !(t1 == t2);
}
bool operator>=(Time const& t1, Time const& t2) {
    return !(t1 < t2);
}
bool operator<=(Time const& t1, Time const& t2) {
    return !(t1 > t2);
}

std::ostream& operator<<(std::ostream& os, Time const& t) {
    os << std::setfill('0')
        << std::setw(2) << t.hours << ':'
        << std::setw(2) << t.minutes << ':'
        << std::setw(2) << t.seconds;
    return os;
}
std::istream& operator>>( std::istream& is, Time& t) {
    Time tmp {};
    is >> tmp.hours;
    if (tmp.hours >= 0 && tmp.hours < 24) {
        if (is.peek() == ':') {
            if (is.ignore(1) >> tmp.minutes) {
                if (tmp.minutes < 60 && tmp.minutes >= 0) {
                    if (is.peek() == ':') {
                        if (is.ignore(1) >> tmp.seconds) {
                            if (tmp.seconds < 60 && tmp.seconds >= 0 ) {
                                t = tmp;
                                return is;
                            }
                        }
                    }
                }
            }

        }
    }
    is.setstate(std::ios::failbit);
    return is;
}

