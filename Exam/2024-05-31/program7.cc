#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <vector>

class JSON_Field;
using JSON_List = std::vector<JSON_Field>;

class JSON
{
public:

    JSON_Field& operator[](std::string const& key)
    {
        return fields[key];
    }

    JSON_Field const& operator[](std::string const& key) const
    {
        return fields.at(key);
    }

    void print(std::ostream& os, int indent = 0) const;

private:

    std::map<std::string, JSON_Field> fields { };

};

// Implement JSON_Field here

class JSON_Field 
{
    public:
        // Constructors
        JSON_Field() = default;

        template <typename T>
        JSON_Field(T&& field) : data { std::forward<T>(field) } { }

        JSON_Field(JSON_Field const&) = default; // Copy constructor
        JSON_Field(JSON_Field&&) = default; // Move constructor

        JSON_Field& operator=(JSON_Field const&) = default; // Copy assignment
        JSON_Field& operator=(JSON_Field&&) = default; // Move assignment

        void print(std::ostream& os, int indent) const
        {
            switch (data.index())
            {
            case 0: print_number(os, indent); break;
            case 1: print_list(os, indent); break;
            case 2: std::get<JSON>(data).print(os, indent); break;
            default: break;
            }
        }

    private:

        void print_number(std::ostream& os, int indent) const
        {
            os << std::get<double>(data);
        }

        void print_list(std::ostream& os, int indent) const
        {
            os << "[";
            bool first { true };
            for (auto& value : std::get<JSON_List>(data)) 
            {
                if (first)
                {
                    first = false;
                }
                else
                {
                    os << ", ";
                }
                value.print(os, indent);
            }
            os << "]";
        }

        std::variant<double, JSON_List, JSON> data;

};

void JSON::print(std::ostream& os, int indent) const
{
    os << "{" << std::endl;

    bool first { true };
    for (auto&& [key, value] : fields)
    {
        // print a 
        if (first)
        {
            first = false;
        }
        else
        {
            os << "," << std::endl;
        }

        os << std::setw(indent + 4) << "";
        os << '"' << key << "\" : ";
        value.print(os, indent + 4);
    }
    os << std::endl << std::setw(indent) << "" << "}";
}

int main()
{
    JSON json1;
    json1["d"] = 0.0;
    json1["e"] = 6.0;

    JSON json2;
    json2["a"] = 5.0;
    json2["b"] = JSON_List{ 1.0, JSON_List{ 2.0, 3.0 }, 4.0 };
    json2["c"] = std::move(json1);

    json2.print(std::cout);
    std::cout << std::endl;

    std::cout << "====" << std::endl;
    JSON json3;
    json3["list"] = JSON_List{ 0.5, std::move(json2), 1.5 };
    json3["number"] = -1.5;

    json3.print(std::cout);
    std::cout << std::endl;
}