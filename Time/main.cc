#include "Time.h"
#include <cassert>
#include <sstream>

int main() {
    // Check validation
    {
        Time t1{24,0,0};
        Time t2{0,61,0};
        Time t3{0,0,61};
        Time t4{-1,-1,-1};
        Time t5{0,0,0};
        assert(!is_valid(t1));
        assert(!is_valid(t2));
        assert(!is_valid(t3));
        assert(!is_valid(t4));
        assert(is_valid(t5));
    }

    // Check is am
    {
        Time t1 {12,0,0};
        Time t2 {11,59,59};
        Time t3 {0,0,0};
        Time t4 {23,59,59};
        assert(!is_am(t1));
        assert(is_am(t2));
        assert(is_am(t3));
        assert(!is_am(t4));
    }

    // Check string formatting
    {
        Time t1 {};
        Time t2 {21,11,01};
        Time t3 {0,23,59};
        Time t4 {1,0,0};
        assert(to_string(t1) == "00:00:00");
        assert(to_string(t2) == "21:11:01");
        assert(to_string(t3) == "00:23:59");
        assert(to_string(t4) == "01:00:00");
    }

    // Check addition operator
    {
        Time t {0,0,0};
        assert(to_string(t + 3600) == "01:00:00");
        assert(to_string(t + (3600*5 + 1)) == "05:00:01");
        assert(to_string(t + (3600*72 + 60*100 + 41)) == "01:40:41");
        assert(to_string(3600 + t) == "01:00:00");
        assert(to_string((3600*5 + 1) + t) == "05:00:01");
        assert(to_string((3600*72 + 60*100 + 41) + t) == "01:40:41");
    }

    // Check increment & decrement operator
    {
        Time t{12, 40, 50};
        assert (to_string(t++) == "12:40:50");
        assert (to_string(--t) == "12:40:50");
        assert (to_string(++t) == "12:40:51");
    }

    // Check comparison operators
    {
        Time t1 {00, 00, 01};
        Time t2 {12, 30, 40};
        Time t3 {12, 30, 41};
        assert(!(t1 > t2));
        assert(t1 != t2);
        assert(t2 < t3);
        assert(t2 >= t2);
        assert(t2 <= t2);
    }

    // check output stream operator
    {
        Time t {0, 12, 12};
        std::ostringstream oss { };
        oss << t;
        assert(oss.str() == "00:12:12");
    }
    {
        Time t {0, 12, 12};
        std::ostringstream oss { };
        oss << (t + 3600);
        assert(oss.str() == "01:12:12");
    }
    
    // check input stream operator
    {
        Time t {};
        std::istringstream iss {"01:00:12"};
        iss >> t;
        assert(to_string(t) == "01:00:12");
    }
    {
        Time t {};
        std::istringstream iss {"01%00&12"};
        assert(!(iss >> t));
    }
}