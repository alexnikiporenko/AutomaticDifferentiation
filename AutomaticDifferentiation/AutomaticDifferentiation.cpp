#include <pybind11/pybind11.h>
#include <cmath>
#include <string>

class DualNumber {
    double _x;
    double _dx;
public:
    // Default constructor
    DualNumber(double x, double dx = 0) : _x(x), _dx(dx) {}

    // Copy constructor
    DualNumber(const DualNumber& other) : _x(other._x), _dx(other._dx) {}
    
    double get_x() const {
        return _x;
    }

    double get_dx() const {
        return _dx;
    }

    // Comparers
    template <typename T>
    bool operator==(const T& other) const {
        DualNumber dn_other = static_cast<DualNumber>(other);
        return _x == dn_other._x && _dx == dn_other._dx;
    }

    template <typename T>
    bool operator!=(const T& other) const {
        DualNumber dn_other = static_cast<DualNumber>(other);
        return !(*this == dn_other);
    }

    // Below comparers compare non-derivatives only
    template <typename T>
    bool operator<(const T& other) const {
        DualNumber dn_other = static_cast<DualNumber>(other);
        return _x < dn_other._x;
    }

    template <typename T>
    bool operator>(const T& other) const {
        DualNumber dn_other = static_cast<DualNumber>(other);
        return _x > dn_other._x;
    }

    template <typename T>
    bool operator<=(const T& other) const {
        DualNumber dn_other = static_cast<DualNumber>(other);
        return _x <= dn_other._x;
    }

    template <typename T>
    bool operator>=(const T& other) const {
        DualNumber dn_other = static_cast<DualNumber>(other);
        return _x >= dn_other._x;
    }

    // Unary negation operator
    DualNumber neg() const {
        return DualNumber(-_x, -_dx);
    }

    // Algebraic operators
    template <typename T>
    DualNumber operator+(const T& other) const {
        DualNumber dn_other = static_cast<DualNumber>(other);
        return DualNumber(_x + dn_other._x, _dx + dn_other._dx);
    }

    template <typename T>
    DualNumber operator-(const T& other) const {
        DualNumber dn_other = static_cast<DualNumber>(other);
        return DualNumber(_x - dn_other._x, _dx - dn_other._dx);
    }

    template <typename T>
    DualNumber operator*(const T& other) const {
        DualNumber dn_other = static_cast<DualNumber>(other);
        double x = _x * dn_other._x;
        double dx = _x * dn_other._dx + _dx * dn_other._x;
        return DualNumber(x, dx);
    }

    template <typename T>
    DualNumber operator/(const T& other) const {
        DualNumber dn_other = static_cast<DualNumber>(other);
        double x = _x / dn_other._x;
        double dx = (_dx * dn_other._x - _x * dn_other._dx) / (dn_other._x * dn_other._x);
        return DualNumber(x, dx);
    }

    // Power functions
    DualNumber power(const DualNumber& other) const {
        double x = std::pow(_x, other._x);
        double dx = x * std::log(_x) * other._dx + other._x * std::pow(_x, other._x - 1) * _dx;
        return DualNumber(x, dx);
    }

    DualNumber power(double other) const {
        double x = std::pow(_x, other);
        double dx = other * std::pow(_x, other-1) * _dx;
        return DualNumber(x, dx);
    }

    // String representation
    std::string repr() const {
        return "<DualNumber x=" + std::to_string(_x) + ", dx=" + std::to_string(_dx) + ">";
    }

    // Friend functions for right-hand side algebraic operators
    friend DualNumber operator+(double lhs, const DualNumber& rhs);

    friend DualNumber operator-(double lhs, const DualNumber& rhs);

    friend DualNumber operator*(double lhs, const DualNumber& rhs);

    friend DualNumber operator/(double lhs, const DualNumber& rhs);

    // Friend function for right-hand side power function
    friend DualNumber power(double lhs, const DualNumber& rhs);

    // Friend functions for non-algebraic operators
    friend DualNumber sin(const DualNumber& dn);

    friend DualNumber cos(const DualNumber& dn);
};

// Right-hand side algebraic operators
DualNumber operator+(double lhs, const DualNumber& rhs) {
    return rhs + lhs;
}

DualNumber operator-(double lhs, const DualNumber& rhs) {
    return rhs.neg() + lhs;
}

DualNumber operator*(double lhs, const DualNumber& rhs) {
    return rhs * lhs;
}

DualNumber operator/(double lhs, const DualNumber& rhs) {
    double x = lhs / rhs._x;
    double dx = (-lhs * rhs._dx) / (rhs._x * rhs._x);
    return DualNumber(x, dx);
}

// Right-hand side power function
DualNumber power(double lhs, const DualNumber& rhs) {
    double x = std::pow(lhs, rhs._x);
    double dx = x * std::log(lhs) * rhs._dx;
    return DualNumber(x, dx);
}

DualNumber sin(const DualNumber& dn) {
    double x = std::sin(dn._x);
    double dx = std::cos(dn._x) * dn._dx;
    return DualNumber(x, dx);
}

DualNumber cos(const DualNumber& dn) {
    double x = std::cos(dn._x);
    double dx = -std::sin(dn._x) * dn._dx;
    return DualNumber(x, dx);
}

DualNumber tan(const DualNumber& dn) {
    return sin(dn) / cos(dn);
}

namespace py = pybind11;

PYBIND11_MODULE(automatic_differentiation, m) {
    py::class_<DualNumber>(m, "DualNumber")
        .def(py::init<double, double>(), py::arg("x"), py::arg("dx") = 0)
        .def("get_x", &DualNumber::get_x)
        .def("get_dx", &DualNumber::get_dx)
        .def("__eq__", &DualNumber::operator== <DualNumber>)
        .def("__eq__", &DualNumber::operator== <double>)
        .def("__ne__", &DualNumber::operator!= <DualNumber>)
        .def("__ne__", &DualNumber::operator!= <double>)
        .def("__lt__", &DualNumber::operator< <DualNumber>)
        .def("__lt__", &DualNumber::operator< <double>)
        .def("__le__", &DualNumber::operator<= <DualNumber>)
        .def("__le__", &DualNumber::operator<= <double>)
        .def("__gt__", &DualNumber::operator> <DualNumber>)
        .def("__gt__", &DualNumber::operator> <double>)
        .def("__ge__", &DualNumber::operator>= <DualNumber>)
        .def("__ge__", &DualNumber::operator>= <double>)
        .def("__neg__", &DualNumber::neg)
        .def("__add__", &DualNumber::operator+ <DualNumber>)
        .def("__add__", &DualNumber::operator+ <double>)
        .def("__radd__", [](const DualNumber& rhs, double lhs) { return operator+(lhs, rhs); })
        .def("__sub__", &DualNumber::operator- <DualNumber>)
        .def("__sub__", &DualNumber::operator- <double>)
        .def("__rsub__", [](const DualNumber& rhs, double lhs) { return operator-(lhs, rhs); })
        .def("__mul__", &DualNumber::operator* <DualNumber>)
        .def("__mul__", &DualNumber::operator* <double>)
        .def("__rmul__", [](const DualNumber& rhs, double lhs) { return operator*(lhs, rhs); })
        .def("__truediv__", &DualNumber::operator/ <DualNumber>)
        .def("__truediv__", &DualNumber::operator/ <double>)
        .def("__rtruediv__", [](const DualNumber& rhs, double lhs) { return operator/(lhs, rhs); })
        .def("__pow__", (DualNumber(DualNumber::*)(const DualNumber&) const) & DualNumber::power)
        .def("__pow__", (DualNumber(DualNumber::*)(double) const) & DualNumber::power)
        .def("__rpow__", [](const DualNumber& rhs, double lhs) { return power(lhs, rhs); })
        .def("__repr__", &DualNumber::repr)
        .def("sin", [](const DualNumber& dn) { return sin(dn); })
        .def("cos", [](const DualNumber& dn) { return cos(dn); })
        .def("tan", [](const DualNumber& dn) { return tan(dn); });
}
