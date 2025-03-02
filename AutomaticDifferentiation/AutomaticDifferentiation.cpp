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

    // Comparers
    bool operator==(const DualNumber& other) const {
        return _x == other._x && _dx == other._dx;
    }

    bool operator!=(const DualNumber& other) const {
        return !(*this == other);
    }

    // Below comparers compare non-derivatives only
    bool operator<(const DualNumber& other) const {
        return _x < other._x;
    }

    bool operator>(const DualNumber& other) const {
        return _x > other._x;
    }

    bool operator<=(const DualNumber& other) const {
        return _x <= other._x;
    }

    bool operator>=(const DualNumber& other) const {
        return _x >= other._x;
    }

    // Unary negation operator
    DualNumber neg() const {
        return DualNumber(-_x, -_dx);
    }

    // Algebraic operators
    DualNumber operator+(const DualNumber& other) const {
        return DualNumber(_x + other._x, _dx + other._dx);
    }

    DualNumber operator-(const DualNumber& other) const {
        return DualNumber(_x - other._x, _dx - other._dx);
    }

    DualNumber operator*(const DualNumber& other) const {
        double x = _x * other._x;
        double dx = _x * other._dx + _dx * other._x;
        return DualNumber(x, dx);
    }

    DualNumber operator/(const DualNumber& other) const {
        double x = _x / other._x;
        double dx = (_dx * other._x - _x * other._dx) / (other._x * other._x);
        return DualNumber(x, dx);
    }

    // Power function
    DualNumber pow(double exponent) const {
        double x = std::pow(_x, exponent);
        double dx = exponent * std::pow(_x, exponent - 1) * _dx;
        return DualNumber(x, dx);
    }

    // String representation
    std::string repr() const {
        return "<DualNumber x=" + std::to_string(_x) + ", dx=" + std::to_string(_dx) + ">";
    }

    // Friend function for right-hand side division
    friend DualNumber operator/(double lhs, const DualNumber& rhs);

    // Friend function for right-hand side power function
    friend DualNumber pow(double lhs, const DualNumber& rhs);
};

// Right-hand side division operator
DualNumber operator/(double lhs, const DualNumber& rhs) {
    double x = lhs / rhs._x;
    double dx = (-lhs * rhs._dx) / (rhs._x * rhs._x);
    return DualNumber(x, dx);
}

// Right-hand side power function
DualNumber pow(double lhs, const DualNumber& rhs) {
    double x = std::pow(lhs, rhs._x);
    double dx = x * std::log(lhs) * rhs._dx;
    return DualNumber(x, dx);
}

namespace py = pybind11;

PYBIND11_MODULE(automatic_differentiation, m) {
    py::class_<DualNumber>(m, "DualNumber")
        .def(py::init<double, double>(), py::arg("x"), py::arg("dx") = 0)
        .def(py::init<const DualNumber&>())
        .def("pow", &DualNumber::pow)
        .def("__neg__", &DualNumber::neg)
        .def("__add__", &DualNumber::operator+)
        .def("__sub__", &DualNumber::operator-)
        .def("__mul__", &DualNumber::operator*)
        .def("__truediv__", &DualNumber::operator/)
        .def("__eq__", &DualNumber::operator==)
        .def("__ne__", &DualNumber::operator!=)
        .def("__lt__", &DualNumber::operator<)
        .def("__le__", &DualNumber::operator<=)
        .def("__gt__", &DualNumber::operator>)
        .def("__ge__", &DualNumber::operator>=)
        .def("__repr__", &DualNumber::repr);
}
