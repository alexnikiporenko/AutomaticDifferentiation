# Automatic Differentiation with Dual Numbers

This is my project exploring automatic differentiation using dual numbers. As I've been studying derivatives and C++, I wanted to build something that combines both interests. It's a hands-on way to see calculus in action!


## What This Project Does

This project has two parts:

### 1. C++ Implementation

I built a C++ class that represents dual numbers - a mathematical concept where each number tracks both its value and derivative simultaneously. It can:
- Perform basic arithmetic (+, -, *, /)
- Calculate derivatives of complex functions automatically
- Handle trigonometric functions like sin, cos, and tan

### 2. Visualization Tool

The Jupyter notebook creates an interactive animation showing:
- A function curve
- A point moving along the curve
- The tangent line showing the slope at each point
- The numerical value of the derivative

Here's a simple example of how it works:

```python
from automatic_differentiation import DualNumber

# Create a dual number for x=2.0 with derivative=1.0
x = DualNumber(2.0, 1.0)

# Calculate sin(x) and its derivative automatically
result = x.sin()

print(f"sin(2.0) = {result.get_x()}")
print(f"d/dx sin(x)|x=2.0 = {result.get_dx()}")
```

## See It In Action

The visualization notebook lets you watch derivatives in real-time. It's fascinating to see how the slope changes as you move along a function curve!

To use it:
1. Open the Jupyter notebook
2. Define your function
3. Run the cells to see the animation

## HTML Version for Easy Viewing

For convenience, the notebook has also been converted to an HTML file, allowing you to view the visualizations without needing Jupyter. Simply open automatic_differentiation.html in your browser.

## Mathematical Background

Dual numbers extend real numbers with an infinitesimal ε where ε² = 0. Each dual number has the form a + bε, where:
- a is the function value
- b is the derivative

This elegant approach gives us exact derivatives without approximations or complex symbolic math.
