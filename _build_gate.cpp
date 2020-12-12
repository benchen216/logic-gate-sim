//
// Created by ben on 11/19/20.
//
#include <iostream>
#include <utility>
#include <vector>
#include <bitset>
#include <map>

#include <fstream>
#include <sstream>
#include "compute.hpp"
using namespace std;

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/operators.h>
#include <pybind11/stl_bind.h>
namespace py = pybind11;

//template<typename T>
class node{
public:
    function<bitset<32>(vector<bitset<32>>)>gate;
    vector<node *>from;
    bitset<32> value;
    node(){
        from.push_back(nullptr);
    }

    node(function<bitset<32>(vector<bitset<32>>)>cal,vector<node *> inputnode){
        gate = std::move(cal);
        from = std::move(inputnode);
}
    bitset<32> run(){
        vector<bitset<32>>from_value;
        for(auto i: from){
            if(i==nullptr){
                return value;
            } else {
                from_value.push_back(i->run());
            }
        }
        return gate(from_value);
    }
    void no_run(){
        set(run());
    }
    void set(bitset<32> input){
        value = input;
    }
    void str_set(const string& input){
        value=bitset<32>(input);
    }
    void output() const{
        cout<<value<<endl;
    }
    string to_string(){
        return value.to_string();
    }
};
void test(map<string,node *> input,map<string,node *>output){
    map<string,node *>::iterator iter;
    for(iter = input.begin();iter != input.end();iter++){
        cout<<iter->first<<endl;
        input[iter->first]->str_set("1111");
    }
    for(iter = output.begin();iter!=output.end();iter++){
        cout<<iter->first;
        output[iter->first]->no_run();
        cout<<output[iter->first]->to_string()<<endl;
    }
}
void build_logic(map<string,node *> input,map<string,node *>output){
    ifstream inputfile("inputfile.txt");
    ofstream outputfile("outputfile.txt");
    map<string,node *>::iterator iter;
    string str1[32];
    int i =0;
    string str3[input.size()];
    for(string line;getline(inputfile,line,'\n');i++){
        if(i%32==0&&i!=0)outputfile<<endl;
        str1[i%32]=line;
        if(i%32==31){
            for(unsigned int j=0;j<input.size();j++){
                for(int z=0;z<32;z++) {
                    char tem = str1[z][j];
                    str3[j] += tem;
                }
                //outputfile<<str3[j]<<endl;
            }
            int a = 0;
            for(iter = input.begin();iter != input.end();iter++){
                cout<<iter->first<<endl;
                input[iter->first]->str_set(str3[a]);
                a++;
            }
            string str4[output.size()];
            int b =0;
            for(iter = output.begin();iter!=output.end();iter++){
                cout<<iter->first<<endl;
                output[iter->first]->no_run();
                str4[b]=output[iter->first]->to_string();
                b++;
            }
            for(int w=0;w<32;w++){
                for(unsigned int x=0;x<output.size();x++){
                    outputfile<<str4[x][w];
                }
                if(w%32!=31)outputfile<<endl;
            }
        }
        cout<<i<<endl;
    }
    if(i%32){

        cout<<"xxx:"<<i;
    }
    //if(i%32)

    outputfile.close();
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
}
*/

PYBIND11_MODULE(_build_gate, m){
    m.doc() = "pybind11 logic gate";
    m.def("build_logic", & build_logic, "naive method");
    m.def("test", &test);

    py::class_<node>(m, "node")
        .def(py::init<>())
        //.def(py::init<bitset<32>(*)(vector<bitset<32>>),vector<node *>>())
        .def(py::init<function<bitset<32>(vector<bitset<32>>)>,vector<node *>>())
        .def("set",&node::set)
        .def("str_set",&node::str_set)
        .def("run",&node::run)
        .def("no_run",&node::no_run)
        .def("output",&node::output)
        .def("__str__",&node::to_string);
    m.def("myand",&myand);
    m.def("mynand",&mynand);
    m.def("myor",&myor);
    m.def("myxor",&myxor);
    m.def("mynor",&mynor);
    m.def("mynot",&mynot);
    m.def("mybuf",&mybuf);
}




