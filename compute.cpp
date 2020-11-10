//
// Created by ben on 11/8/20.
//
#include <iostream>
#include <bitset>
#include <array>
#include <vector>

using namespace std;
bitset<32> myand(vector<bitset<32>> z){
    bitset<32>ans_and(4294967295);
    for(bitset<32>a :z){
        ans_and=ans_and.operator&=(a);
    }
    return ans_and;
}
bitset<32> myor(vector<bitset<32>> z){
    bitset<32>ans_or(0);
    for(bitset<32>a :z){
        ans_or=ans_or.operator|=(a);
    }
    return ans_or;
}
bitset<32> myxor(bitset<32> a,bitset<32> b){
    return a.operator^=(b);
}

int main(){
    bitset<32> *a;
    vector<bitset<32>>b;
    b.push_back(bitset<32>(0));
    b.push_back(bitset<32>(0));
    b.at(0).operator|=(4);
    b.at(1).operator|=(2);

    cout<< myor(b);//.operator|=(bitset<32>("1010"))
    return 0;
}
