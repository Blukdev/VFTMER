/*
 ____  _       _          _
| __ )| |_   _| | __   __| | _____   __
|  _ \| | | | | |/ /  / _` |/ _ \ \ / /
| |_) | | |_| |   <  | (_| |  __/\ V /
|____/|_|\__,_|_|\_\  \__,_|\___| \_(_)
*/
#include<iostream>
#include<fstream>
#include<sstream>
#include<cmath>
#include "becbct.h"
#include "jsonxx/json.hpp"
#define roundt(x) round(x*100)/100.0
using namespace std;
jsonxx::json sets={
    {"Chains",3},
    {"Define",{
		{"1",{
            {"Length",0},
            {"Name","Fix"},
            {"FirstCommandType","ncb"},
            {"Define",{}}
		}},
        {"2",{
            {"Length",0},
            {"Name","Summon"},
            {"FirstCommandType","ncb"},
            {"Define",{}}
		}},
        {"3",{
            {"Length",0},
            {"Name","Series"},
            {"FirstCommandType","rcb"},
            {"Define",{}}
		}}
    }}
};
double omega_zoom=1,zoom;
inline void init(){
	ifstream filein("datas.txt");
	int lines=0;
	stringstream buffer;
	buffer<<filein.rdbuf();
	filein.close();
	string process(buffer.str());
	for(int i=0;i<process.size();++i)
		if(process[i]=='['||process[i]==']')process.erase(i,1);
		else if(process[i]==','){
			++lines;
			process[i]=' ';
		}
	ofstream fout("in.txt");
	fout<<lines<<endl;
	fout<<process;
	fout.close();
}
int main(int argc,char *argv[]){
	setx=atoi(argv[1]),sety=atoi(argv[2]),setz=atoi(argv[3]),zoom=atof(argv[4]);
	init();
	ifstream fin("in.txt");
	int num,flag=1;
	fin>>num;
	if(num>=10)omega_zoom=0.1;
	else if(num>=100)omega_zoom=0.01;
	TrigonometricFunction TFA[num+1];
	double data1,data2;
	for(int i=1;i<=num;++i){
		fin>>data1>>data2;
		TFA[i].alpha=sqrt(data1*data1+data2*data2);
		TFA[i].phi=atan2(data2,data1);
	}
	fin.close();
	for(int i=1;i<=num;++i)TFA[i].omega=(((i+1)/2)*((i%2==0)?-1:1))*omega_zoom;
	TrigonometricFunction TF[num];
	for(int i=1;i<=num;++i)TF[i-1]=move(TFA[i]);
	auto Fix=InitialPhaseFix(TF,num);
	auto Series=FourierSeriesBuilder(TF,num,zoom);
	auto Summon=SummonCommandBuilder(num+1);
	for(int i=0;i<Fix.size();++i)
		sets["Define"]["1"]["Define"].push_back(Fix[i]);
	sets["Define"]["1"]["Length"]=Fix.size();
	for(int i=0;i<Summon.size();++i)
		sets["Define"]["2"]["Define"].push_back(Summon[i]);
	sets["Define"]["2"]["Length"]=Summon.size();
	for(int i=0;i<Series.size();++i)
		sets["Define"]["3"]["Define"].push_back(Series[i]);
	sets["Define"]["3"]["Length"]=Series.size();
	ofstream fout("set.json");
	fout<<sets.dump();
	fout.close();
}
