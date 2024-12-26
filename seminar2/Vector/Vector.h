#pragma once

#ifndef VECTOR
#define VECTOR

#include <iostream>

class Vector {
    public: 

        // Constructors
        Vector() = default;
        Vector(double x, double y);

        // Compound assigments
        Vector& operator+=(Vector const& other);
        Vector& operator-=(Vector const& other);
        Vector& operator*=(double value);
        Vector& operator/=(double value);

        // Comparison operators
        bool operator==(Vector const& other) const;
        bool operator!=(Vector const& other) const;

        // Negate operator
        Vector operator-() const;

        double length() const;

        // Utility functions (external interface)
        friend std::ostream& operator<<(std::ostream& os, Vector const& v);
        friend std::istream& operator>>(std::istream& is, Vector& v);

    private:
        double x;
        double y;
};

// Symnetric functions
Vector operator+(Vector const& lhs,Vector const& rhs);
Vector operator-(Vector const& lhs,Vector const& rhs);
Vector operator*(Vector const& v,double value);
Vector operator*(double value,Vector const& v);
Vector operator/(Vector const& v,double value);

#endif
