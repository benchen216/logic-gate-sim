//
// Created by ben on 11/19/20.
//
#include <iostream>
#include <vector>
#include "compute.hpp"
using namespace std;
class node{
public:
    bitset<32> (*calcArray)(vector<bitset<32>>);
    node(){
        vector<node *>in_node;
    }
    bitset<32>run(){
        bitset<32>gate;
        return bitset<32>(0);
    }

};
out put -> input
        output
gate=
input
run {
gate()
};






#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

PYBIND11_MODULE(build_gate, m){

}
