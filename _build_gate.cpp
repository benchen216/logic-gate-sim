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
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>
#include <pybind11/operators.h>
#include <pybind11/stl_bind.h>
namespace py = pybind11;

//template<typename T>
class node{
public:
    bitset<32> (*gate)(vector<bitset<32>>);
    function<bitset<32>(vector<bitset<32>>)>gate2;
    vector<node *>from;
    bitset<32> value;
    node(){
        from.push_back(nullptr);
    }
    node(bitset<32> (*cal)(vector<bitset<32>>),vector<node *> inputnode){
        gate = cal;
        from = inputnode;
    }
    node(function<bitset<32>(vector<bitset<32>>)>cal,vector<node *> inputnode){
        gate2 = cal;
        from = inputnode;
}
    bitset<32> run(){
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
class test{
public:
    int a=0;
    bitset<32> d=bitset<32>(2);
    test(int b){
        a=b;
    }
    test(bitset<32> k ){
        d=k;
    }
    bitset<32> run(){
        return d;
    }
    test * run2(){
        return this;
    }
    vector<test *>g;
    function<int(vector<int>)> gate;

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
    node n3=node(myand,z);
    n1.set(bitset<32>(1));
    n2.set(bitset<32>(2));
    vector<node*>f;
    f.push_back(&n3);
    node n4=node(mybuf,f);
    cout<<n4.run()<<endl;
    n1.set(bitset<32>(2));
    n2.set(bitset<32>(2));
    cout<<n4.run()<<endl;
    function<unsigned int(vector<unsigned int>)> gate=&mybuf2;
    vector<unsigned int>d;
    d.push_back(1);
    cout<<gate(d);
    return 0;
}*/

PYBIND11_MODULE(_build_gate, m){
    m.doc() = "pybind11 matrix multiplication test";
    m.def("build_logic", & build_logic, "naive method");

    py::class_<test>(m,"test")
            .def(py::init<int>())
            .def(py::init<bitset<32>>())
            .def("run",&test::run)
            .def("run2",&test::run2)
            .def_readwrite("d",&test::d);
    //.def("a",&test::a);

    py::class_<node>(m, "node")
        .def(py::init<>())
        .def(py::init<bitset<32>(*)(vector<bitset<32>>),vector<node *>>())
        .def(py::init<function<bitset<32>(vector<bitset<32>>)>,vector<node *>>())
        .def("set",&node::set)
        .def("run",&node::run);
    m.def("myand",&myand);
    m.def("mynand",&mynand);
    m.def("myor",&myor);
    m.def("myxor",&myxor);
    m.def("mynor",&mynor);
    m.def("mynot",&mynot);
    m.def("mybuf",&mybuf);
    //  .def_property()
    //.def_property("value", &node::value, nullptr);
}




