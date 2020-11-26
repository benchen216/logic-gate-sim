//
// Created by ben on 11/19/20.
//
#include <iostream>
#include <vector>
#include <bitset>
#include "compute.hpp"
using namespace std;
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
namespace py = pybind11;

//template<typename T>
class node{
public:
    bitset<32> (*gate)(vector<bitset<32>>)=mybuf;
    vector<node *>from;
    bitset<32> value;
    node(){
        from.push_back(nullptr);
    }
    node(bitset<32> (*cal)(vector<bitset<32>>),vector<node *>* inputnode){
        gate = cal;
        from = *inputnode;
    }
    bitset<32>run(){
        vector<bitset<32>>from_value;
        for(auto i: from){
            if(i==nullptr){
                from_value.push_back(this->value);
            } else {
                from_value.push_back(i->run());
            }
        }
        return gate(from_value);
    }
    void set(bitset<32> input){
        value = input;
    }
};
int build_logic(){
    vector<node *> input;
    vector<node *> output;
    vector<node *> temp;
    return 1;
}
/*
int main(){
    node n1=node();
    node n2=node();
    vector<node *> z;
    z.push_back(&n1);
    z.push_back(&n2);
    node n3=node(myand,&z);
    n1.set(bitset<32>(1));
    n2.set(bitset<32>(2));
    vector<node*>f;
    f.push_back(&n3);
    node n4=node(mybuf,&f);
    cout<<n4.run()<<endl;
    n1.set(bitset<32>(2));
    n2.set(bitset<32>(2));
    cout<<n4.run()<<endl;
    return 0;
}*/



/*

PYBIND11_MODULE(_build_gate, m){
    m.doc() = "pybind11 matrix multiplication test";
    m.def("build_logic", & build_logic, "naive method");
}
*/