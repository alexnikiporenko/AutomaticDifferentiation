# Automatic Differentiation with Dual Numbers

This project implements automatic differentiation using dual numbers. It consists of two main components: a C++ implementation with Python bindings and a visualization tool for function derivatives.

## Overview

Automatic differentiation allows for exact computation of derivatives without the need for symbolic manipulation or numerical approximation. This implementation uses dual numbers - a mathematical concept where each number is represented as a pair (x, dx) that tracks both the value and its derivative.

## Components

### 1. C++ Implementation (`automatic_differentiation`)

The core of the project is a C++ class `DualNumber` exposed to Python via pybind11. The implementation:

- Represents dual numbers as pairs of real values (x, dx)
- Overloads common arithmetic operators (+, -, *, /)
- Implements comparison operators
- Provides trigonometric functions (sin, cos, tan)
- Implements power functions for both dual number and scalar exponents

### 2. Visualization Tool

A Jupyter notebook that creates interactive visualizations of functions and their derivatives. 

## Usage Examples

### Basic Dual Number Operations

```python
from automatic_differentiation import DualNumber

# Create a dual number representing x = 2.0 with derivative 1.0
x = DualNumber(2.0, 1.0)  # f(x) = x, f'(x) = 1

# Compute f(x) = sin(x) and its derivative
y = x.sin()  # y now contains (sin(2.0), cos(2.0))

print(f"Value: {y.get_x()}")       # sin(2.0)
print(f"Derivative: {y.get_dx()}")  # cos(2.0)
```

### Creating Complex Functions

```python
def f(x):
    # Compute f(x) = x^2 * sin(x) and its derivative
    x_dual = DualNumber(x, 1.0)  # Initialize with derivative = 1.0
    result = (x_dual * x_dual) * x_dual.sin()
    return result.get_x(), result.get_dx()

# Evaluate at x = 1.0
value, derivative = f(1.0)
print(f"f(1.0) = {value}, f'(1.0) = {derivative}")
```

## Mathematical Background

Dual numbers extend real numbers with an additional component ε such that ε² = 0. Each dual number has the form a + bε, where:
- a is the real part (the function value)
- b is the dual part (the derivative)

This allows all derivatives to be computed exactly through algebraic operations without requiring limits or symbolic differentiation.
