//
// Created by ben on 11/19/20.
//
#include <iostream>
#include <vector>
#include "compute.hpp"
using namespace std;

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
void buid_logic(){
    vector<node *> input;
    vector<node *> output;
    vector<node *> temp;
}

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
    //cout<<n3.run()<<endl;
    node n4=node(mybuf,&f);
    cout<<n4.run()<<endl;
    n1.set(bitset<32>(2));
    n2.set(bitset<32>(2));
    cout<<n4.run()<<endl;
    /*
    bitset<32> *a;
    vector<bitset<32>>b;
    b.push_back(bitset<32>(0));
    b.push_back(bitset<32>(0));
    b.at(0).operator|=(4);
    b.at(1).operator|=(2);

    cout<< b.at(1);
    cout<< b.at(1).operator~();//.operator|=(bitset<32>("1010"))*/
    return 0;
}



/*
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

PYBIND11_MODULE(build_gate, m){

}
*/