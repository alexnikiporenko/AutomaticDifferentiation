cmake_minimum_required(VERSION 3.14)
project(example LANGUAGES CXX)

# Find Python from the active virtual environment
find_package(Python REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)

# Create the Python module
pybind11_add_module(automatic_differentiation AutomaticDifferentiation.cpp)
