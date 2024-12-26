#include "Vector.h"
#include "cmath"

// Constructor 
Vector::Vector(double x, double y) : x{x}, y{y} {}

// Compound assignment
Vector& Vector::operator+=(Vector const& other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
}
Vector& Vector::operator-=(Vector const& other) {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}
Vector& Vector::operator*=(double value) {
    this->x *= value;
    this->y *= value;
    return *this;
}
Vector& Vector::operator/=(double value) {
    this->x /= value;
    this->y /= value;
    return *this;
}

// Comparision operators
bool Vector::operator==(Vector const& other) const {
    return (this->x == other.x) && (this->y == other.y);
}

bool Vector::operator!=(Vector const& other) const {
    return !(*this == other);
}

// Get length 
double Vector::length() const {
    return sqrt(pow(x,2)+ pow(y,2));
}

// Negate operator
Vector Vector::operator-() const {
    Vector tmp{*this};
    tmp.x = -tmp.x;
    tmp.y = -tmp.y;
    return tmp;
}

// Utility functions
std::ostream& operator<<(std::ostream& os, Vector const& v) {
    os << "(" << v.x << ", " << v.y << ")";
    

    return os;
}
std::istream& operator>>(std::istream& is, Vector& v) {
    Vector tmp;
    is >> std::ws;
    if (is.peek() == '(') {
        if (is.ignore(1) >> std::ws >> tmp.x >> std::ws) {
            if (is.peek() == ',') {
                if (is.ignore(1) >> std::ws >> tmp.y >> std::ws) {
                    if (is.peek() == ')') {
                        is.ignore(1);
                        v = tmp;
                        return is;
                    }
                }
            }           
        }
    }
    is.setstate(std::ios::failbit);
    return is;
}

// Symmetric operations
Vector operator+(Vector const& lhs,Vector const& rhs) {
    return Vector{lhs} += rhs;
}
Vector operator-(Vector const& lhs,Vector const& rhs) {
    return Vector{lhs} -= rhs;
}

Vector operator*(Vector const& v,double value) {
    return Vector{v} *= value;
}
Vector operator*(double value,Vector const& v) {
    return v * value;
}

Vector operator/(Vector const& v,double value) {
    return Vector{v} /= value;
}
