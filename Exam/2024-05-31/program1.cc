#include <cassert>
#include <string>
#include <iostream>
#include <functional>

/** TESTCASES **/

int fun1(std::string const& str)
{
    return std::stoi(str);
}

char fun2(int x)
{
    return static_cast<char>(x);
}

struct NextCharacter
{
    char operator()(char c) const { return c + 1; }
};

template <typename T>
class Payload {
    public: 
        Payload(T data) : value { data } {}
        operator T() const {
            return value;
        }
    private:
        T value;
};

template <typename T>
Payload<T> payload(T&& value) 
{
    return { std::forward<T>(value) };
    
}

template <typename T, typename Callable>
auto operator|(Payload<T> const& p, Callable const& callable) 
    -> Payload<decltype(callable(static_cast<T>(p)))> {

    return { callable(static_cast<T>(p)) };
}

int main()
{
    assert((payload(1) | [](int    x) -> double { return 1.5f + x; }) == 2.5);

    char c { 'a' };
    assert((payload(c) | NextCharacter{}) == 'b');

    assert((payload(1) | [](int    x) -> double { return 1.5f + x; }
                       | [](double y) -> int    { return 2*y; }) == 5);

    assert((payload("67") | fun1 | fun2) == 'C');

}