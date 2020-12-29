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
    bitset<32> value = NULL;
    node(){
        from.push_back(nullptr);
    }

    node(function<bitset<32>(vector<bitset<32>>)>cal,vector<node *> inputnode){
        gate = std::move(cal);
        from = std::move(inputnode);
}
    bitset<32> run(){
        if (value != NULL) return value;
        vector<bitset<32>>from_value;
        for(auto i: from){
            if(i==nullptr){
                return value;
            } else {
                from_value.push_back(i->run());
            }
        }
        value = gate(from_value);
        return value;
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
    void reset(){
        value = NULL;
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
void build_logic2(map<string,node *> input,map<string,node *>output, map<string,node *> xlogic,string inputname="inputfile.txt",
                 string outputname="outputfile.txt"){
    ifstream inputfile(inputname);
    ofstream outputfile(outputname);
    map<string,node *>::iterator iter;
    string str1[32];
    int countlines =0;
    for(string line; getline(inputfile,line,'\n'); countlines++){
        if(countlines != 0)outputfile << endl;
        str1[0]=line;
        int a = 0;
        for(iter = input.begin();iter != input.end();iter++){
            //cout<<iter->first<<endl;
            input[iter->first]->set(bitset<32>(str1[0][a]));
            a++;
        }
        for(iter = output.begin();iter!=output.end();iter++){
            output[iter->first]->no_run();
            outputfile<<output[iter->first]->value[0];
            output[iter->first]->reset();
        }
        for(iter = xlogic.begin();iter!=xlogic.end();iter++){
            xlogic[iter->first]->reset();
        }

    }
    outputfile.close();
}
void build_logic(map<string,node *> input,map<string,node *>output, map<string,node *> xlogic,string inputname="inputfile.txt",
                 string outputname="outputfile.txt"){
    ifstream inputfile(inputname);
    ofstream outputfile(outputname);
    map<string,node *>::iterator iter;
    string str1[32];
    int countlines =0;
    string str3[input.size()];
    for(string line; getline(inputfile,line,'\n'); countlines++){
        if(countlines % 32 == 0 && countlines != 0)outputfile << endl;
        str1[countlines % 32]=line;
        if(countlines % 32 == 31){
            for(unsigned int j=0;j<input.size();j++){
                for(int z=0;z<32;z++) {
                    char tem = str1[z][j];
                    str3[j] += tem;
                }
            }
            int a = 0;
            for(iter = input.begin();iter != input.end();iter++){
                //cout<<iter->first<<endl;
                input[iter->first]->str_set(str3[a]);
                a++;
            }
            string str4[output.size()];
            int b =0;
            for(iter = output.begin();iter!=output.end();iter++){
                //cout<<iter->first<<endl;
                output[iter->first]->no_run();
                str4[b]=output[iter->first]->to_string();
                output[iter->first]->reset();
                b++;
            }
            for(iter = xlogic.begin();iter!=xlogic.end();iter++){
                xlogic[iter->first]->reset();
            }
            for(int w=0;w<32;w++){
                for(unsigned int x=0;x<output.size();x++){
                    outputfile<<str4[x][w];
                }
                if(w%32!=31)outputfile<<endl;
            }
        }
        //cout << countlines << endl;
    }
    if(countlines % 32){
        for(unsigned int j=0;j<input.size();j++){
            for(int z=0;z<32;z++) {
                if(z<=countlines%32){
                    char tem = str1[z][j];
                    str3[j] += tem;
                }else{
                    break;
                }
            }
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
            output[iter->first]->reset();
            b++;
        }
        for(iter = xlogic.begin();iter!=xlogic.end();iter++){
            xlogic[iter->first]->reset();
        }
        for(int w=0;w<32;w++){
            if(w<countlines%32-1){
                for(unsigned int x=0;x<output.size();x++){
                    outputfile<<str4[x][w];
                }
                outputfile<<endl;
            }else{
                for(unsigned int x=0;x<output.size();x++){
                    outputfile<<str4[x][w];
                }
                break;
            }
        }
        cout << "xxx:" << countlines;
    }
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
    m.def("build_logic2", & build_logic2, "naive method");
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