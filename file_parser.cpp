//
// Created by ben on 2020-12-11.
//
#include <iostream>
#include <fstream>
using namespace std;
int main(){
    ifstream inputfile("inputfile.txt");
    ofstream outputfile("outputfile.txt",ios::app);
    //outputfile<<"test"<<endl;
    //outputfile<<"test"<<endl;
    //outputfile.close();
    string str1[32];
    int i =0;
    int b =0;
    for(string line;getline(inputfile,line,'\n');i++){
        str1[i]=line;
        if(i%32==31){
            b=str1[31].length();
            //run
            string str3[b];
            for(int j=0;j<b;j++){
                for(int z=0;z<32;z++) {
                    char tem=str1[z][j];
                    str3[j]+=tem;
                }
                outputfile<<str3[j]<<endl;
            }
        }
    }
    //int b = str1[0].length();
    //for(string j:str1)cout<<j<<endl;
    //cout<<b<<endl;
/*
    const int LINE_LENGTH = 100;
    char str[32][LINE_LENGTH];
    int n=0;
    while( inputfile.getline(str[n],LINE_LENGTH) )
    {
        cout << "Read from file: " << str[n] << endl;
        n++;
    }
    //string a = "";
    //a.append("123");
    //a.append("321");
    //cout<<a<<endl;*/
    string str2[b];
    for(int j=0;j<b;j++){
        for(int i=0;i<32;i++) {
            char tem=str1[i][j];
            str2[j]+=tem;
        }
        cout<<str2[j]<<endl;
    }

    return 0;
}