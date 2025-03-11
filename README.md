# Automatic Differentiation with Dual Numbers

Hi there! This project explores automatic differentiation using dual numbers - a fascinating mathematical concept that lets us calculate exact derivatives. I created it while studying C++ and calculus, wanting to build something that brings these two interests together in a practical way.

## What This Project Does

The project combines several technologies:

### 1. C++ Implementation

I built a C++ class that represents dual numbers - a pair of values where one tracks the function value and the other tracks its derivative. The implementation handles:
- Basic arithmetic operations
- Trigonometric functions
- Power functions
- Comparison operations

### 2. Python Bindings with pybind11

I used pybind11 to create Python bindings for my C++ code. This was a valuable learning experience because it allows me to leverage C++'s speed with Python's ease of use.

### 3. Visualization Tool

The Jupyter notebook creates an interactive animation showing:
- A function curve
- A point moving along the curve
- The tangent line showing the slope at each point
- The numerical value of the derivative


## Real-World Applications

While this is a learning project, automatic differentiation has important real-world applications:

- **Machine Learning**: Deep learning frameworks like TensorFlow and PyTorch use automatic differentiation for backpropagation
- **Financial Modelling**: Computing sensitivities (like "Greeks" in options pricing) accurately
- **Optimization Problems**: Finding minima or maxima efficiently in complex systems

## HTML Version for Easy Viewing

For convenience, the notebook has also been converted to an HTML file, allowing you to view the visualizations without needing Jupyter. Simply open automatic_differentiation.html in your browser.
