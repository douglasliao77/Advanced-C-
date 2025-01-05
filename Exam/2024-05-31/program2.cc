#include <iostream>
#include <list>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <iterator>

void print(int key, std::string const& value)
{
    std::cout << "(" << key << ", " << value << ") ";
}

struct IntPrinter
{
    void operator()(int key) const
    {
        std::cout << key << " ";
    };
};

template <typename T, typename U, typename Callable>
auto apply(std::pair<T,U> p, Callable const& callable,int, int, int) 
    -> decltype(callable(p.first), std::declval<void>())
{
    callable(p.first);
}

template <typename T, typename U, typename Callable>
auto apply(std::pair<T,U> p, Callable const& callable, int, int, float) 
    -> decltype(callable(p.second), std::declval<void>()) 
{
    callable(p.second);
}

template <typename T, typename U, typename Callable>
auto apply(std::pair<T,U> p, Callable const& callable, int, float, float) 
    -> decltype(callable(p.first, p.second), std::declval<void>()) 
{
    callable(p.first, p.second);
}

template <typename T, typename Callable>
auto apply(T const& data, Callable const& callable, float, float, float) 
    -> decltype(callable(data)) 
{
    callable(data);
}

template <typename It, typename Callable>
void iterate(It begin, It end, Callable const& callable) 
{
    for (auto it = begin; it != end; ++it) {
        apply(*it, callable,0,0,0);
    }
}

int main()
{
    /** TESTCASES **/

    /* Expected output:

    1 2 3 
    1 2 
    one two 
    (1, one) (2, two) 
    one three two 

    */
    std::vector<int> v { 1, 2, 3 };
    iterate(v.begin(), v.end(), [](int v) { std::cout << v << " "; });
    std::cout << std::endl;

    std::list<std::pair<int, std::string>> l { { 1, "one" }, { 2, "two" } };
    iterate(l.begin(), l.end(), IntPrinter{});
    std::cout << std::endl;

    iterate(l.begin(), l.end(), [](std::string const& v) { std::cout << v << " "; });
    std::cout << std::endl;

    iterate(l.begin(), l.end(), print);
    std::cout << std::endl;

    std::map<std::string, std::string> m { { "one", "1" }, { "two", "2" }, { "three", "3" } };
    iterate(m.begin(), m.end(), [](std::string const& k) { std::cout << k << " "; });
    std::cout << std::endl;
}