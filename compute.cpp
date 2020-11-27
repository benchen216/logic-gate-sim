//
// Created by ben on 11/8/20.
//
#include <bitset>
#include <vector>

using namespace std;

//template<typename T>
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
bitset<32> myxor(vector<bitset<32>> z){
    return z.at(0).operator^=(z.at(1));
}
bitset<32> mynand(vector<bitset<32>> z){
    bitset<32>ans_and(4294967295);
    for(bitset<32>a :z){
        ans_and=ans_and.operator&=(a).operator~();
    }
    return ans_and;
}
bitset<32> mynor(vector<bitset<32>> z){
    bitset<32>ans_or(0);
    for(bitset<32>a :z){
        ans_or=ans_or.operator|=(a).operator~();
    }
    return ans_or;
}
bitset<32> mynot(vector<bitset<32>> z){
    return z.at(0).operator~();
}
bitset<32> mybuf(vector<bitset<32>> z){
    return z.at(0);
}

int mybuf2(vector<int> z){
    return z.at(0);
}
