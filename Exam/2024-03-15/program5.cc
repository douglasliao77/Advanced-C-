#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <set>
#include <fstream>

struct Process
{
    std::string name { };
    std::vector<std::string> resources { };
};

std::istream& operator>>(std::istream& is, Process& p)
{
    Process result { };
    std::string line;
    std::getline(is, line);

    std::istringstream iss { line };

    std::getline(iss, result.name, ':');
    std::copy(std::istream_iterator<std::string> { iss }, 
        std::istream_iterator<std::string> { },
        std::back_inserter(result.resources)
    );

    std::sort(result.resources.begin(), result.resources.end());
    p = std::move(result);
    return is;
}

std::ostream& operator<<(std::ostream& os, Process p)
{
    os << p.name << ": ";
    std::vector<std::string> v;
    std::copy(p.resources.begin(), p.resources.end(),
        std::ostream_iterator<std::string> { os, " " } 
    );
    return os;
}

int main()
{
    

    std::cout << "Enter resources that are busy: "; 
    std::vector<std::string> busy;

    auto begin { std::istream_iterator<std::string> { std::cin } };
    auto end { std::istream_iterator<std::string> { } };
    std::copy(begin, end, std::back_inserter(busy));
    std::sort(busy.begin(), busy.end());
    std::cout << std::endl;
    
    std::vector<Process> ps { };

    std::ifstream file { "processes.txt" };
    std::copy(std::istream_iterator<Process> { file },
        std::istream_iterator<Process> { },
        std::back_inserter(ps)
    );

    ps.erase(std::remove_if(ps.begin(), ps.end(), 
        [&busy] (Process p) 
        {
            std::vector<std::string> intersection;
            std::set_intersection(p.resources.begin(), p.resources.end(),
                busy.begin(), busy.end(),
                std::back_inserter(intersection)
            );
            return !intersection.empty();
        }), ps.end());

    std::copy(ps.begin(), ps.end(), std::ostream_iterator<Process> {std::cout, "\n"});
}

/* Example 1:

$ ./a.out
Enter resources that are busy: disk <ctrl+D>
Processs that can run unhindered:
Web Browser: network
Print Manager: network printer
Input Handler: keyboard
Image Processing: GPU display
Video Streaming: display network speakers
Print Driver Service: printer
Photo Viewer: display
Scientific Computation Module: GPU
Text Editor: display keyboard
Network Scanning Tool: USB network
Audio Playback: speakers
System Update Service: GPU USB network
Document Conversion Tool: display printer
Graphic Design Software: GPU display
Simulation Engine: GPU
E-Mail Client: network

Example 2:

$ ./a.out 
Enter resources that are busy: network display printer GPU <ctrl+D>
Processs that can run unhindered:
Input Handler: keyboard
File Management Tool: USB disk
Audio Playback: speakers
Disk Cleaning Utility: disk

Example 3:

$ ./a.out 
Enter resources that are busy: USB speakers keyboard <ctrl+D>
Processs that can run unhindered:
Data Analysis Tool: disk network
Web Browser: network
Print Manager: network printer
Image Processing: GPU display
Print Driver Service: printer
Photo Viewer: display
Database Management System: disk network
Scientific Computation Module: GPU
Document Conversion Tool: display printer
Disk Cleaning Utility: disk
Graphic Design Software: GPU display
Simulation Engine: GPU
E-Mail Client: network

*/