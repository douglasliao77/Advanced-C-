#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>
#include <numeric>
#include <sstream>

struct Line
{
    Line(std:: string str) : str{str} {}
    Line() : str{""} {};
    std::string str;
};


std::istream& operator>>(std::istream& is, Line& line) 
{
    std::getline(is, line.str, '\n');
    return is;
}

int main() 
{
    std::cout << "Enter your text:" << std::endl;
// 1. Read each word on each line into a container that helps you keep track
//    of each unique word that appeared on each line (See hint in PDF).

    std::vector <std::set<std::string> > lines = { };

    std::transform(std::istream_iterator<Line> { std::cin }, 
        std::istream_iterator<Line> {}, std::back_inserter(lines),
        [] (Line const& line) 
        {
            std::istringstream iss { line.str };
            std::set<std::string> words {
                std::istream_iterator<std::string> { iss },
                std::istream_iterator<std::string> { }
            };
            return words;
        }
    );

    std::cout << lines.size() << std::endl;

    // for (set<string> ss : lines ) {
    //     for (string s : ss) {
    //         std::cout << s << " ";
    //     }
    //     std::cout << std::endl;
    // }

// 2. Remove all blank lines
    lines.erase(std::remove_if(begin(lines), end(lines), 
        [] (std::set<std::string> const& s) 
        {
            return s.empty();
        }
    ), end(lines));

// 3. Find which words appear on each line (see hint in PDF).
    std::set<std::string> result = std::accumulate(begin(lines)+1, end(lines), lines[0], 
        [] (std::set<std::string> const& s1,std::set<std::string> const& s2) 
        {
            std::set<std::string> dest {};
            std::set_intersection(s1.cbegin(), s1.cend(),
                   s2.cbegin(), s2.cend(),
                   std::inserter(dest, dest.end()));
            return dest;
        } 
    );

// 4. Print the found common words, OR print a message stating that no common
//    words appeared if none could be found.
    std::cout << std::endl;
    std::copy(begin(result), end(result), 
        std::ostream_iterator<std::string> {std::cout, "\n"});
    
}