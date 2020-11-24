cmake_minimum_required(VERSION 3.15)
project(logic-gate-sim)

set(CMAKE_CXX_STANDARD 14)
include_directories(
        /usr/local/lib/python3.8/site-packages/pybind11/include
        /usr/local/Cellar/python@3.8/3.8.5/Frameworks/Python.framework/Versions/3.8/include/python3.8
)
#add_library(mypython SHARED  )
add_executable(logic-gate-sim sim.cpp compute.cpp build_gate.cpp compute.hpp)