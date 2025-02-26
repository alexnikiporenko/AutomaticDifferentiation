#include <iostream>
#include <cmath>

class DualNumber {
    double _x;
    double _dx;   
public:
    // Default constructor
    DualNumber(double x, double dx=0) : _x(x), _dx(dx) {}

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
	DualNumber operator-() const {
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
		double dx = exponent * std::pow(_x, exponent-1) * _dx;
		return DualNumber(x, dx);
		
	}

	// Friend function for right-hand side division
	friend DualNumber operator/(double lhs, const DualNumber& rhs);

	// Friend function for right-hand side power function
	friend DualNumber pow(double lhs, const DualNumber& rhs);

	// Friend function for << operator
	friend std::ostream& operator<<(std::ostream& os, const DualNumber& dn);
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

std::ostream& operator<<(std::ostream& os, const DualNumber& dn) {
	os << "x = " << dn._x << ", dx = " << dn._dx << std::endl;
	return os;
}

int main()
{
	DualNumber dn1(2.0, 1.0);
	DualNumber dn2 = dn1.pow(3);
	std::cout << "dn1.pow(3): " << dn2 << std::endl;
	return 0;
}
