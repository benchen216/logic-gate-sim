cmake_minimum_required(VERSION 3.15)
project(logic-gate-sim)

set(CMAKE_CXX_STANDARD 14)
include_directories(
        /home/ben/opt/conda/include/python3.7m
        /home/ben/opt/conda/lib/python3.7/site-packages/pybind11/include
)
#add_library(mypython SHARED  )
#/usr/local/lib/python3.8/site-packages/pybind11/include
#        /usr/local/Cellar/python@3.8/3.8.5/Frameworks/Python.framework/Versions/3.8/include/python3.8
#        /Users/ben/opt/conda/envs/nsd/lib/python3.7/site-packages/pybind11/include
#        /Users/ben/opt/conda/envs/nsd/include/python3.7m
# pybind11_exp.cpp

add_executable(logic-gate-sim sim.cpp compute.cpp _build_gate.cpp compute.hpp)