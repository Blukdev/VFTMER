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
double speed=0.01;
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
	setx=atoi(argv[1]),sety=atoi(argv[2]),setz=atoi(argv[3]),speed=atof(argv[4]);
	init();
	ifstream fin("in.txt");
	int num,flag=1;
	fin>>num;
	int positive[num+1];
	long long lthetas[num+1],gcdt;
	TrigonometricFunction TFA[num+1];
	double data1,data2;
	for(int i=1;i<=num;++i){
		fin>>data1>>data2;
		TFA[i].alpha=sqrt(data1*data1+data2*data2);
		TFA[i].fai=atan2(data2,data1);
	}
	fin.close();
	for(int i=1;i<=num;++i){
		double theta=ctheta(speed,((i+1)/2)*((i%2==0)?-1:1),TFA[i].fai);
		positive[i]=theta>0?1:theta<0?-1:0;
		lthetas[i]=(long long)(fabs(theta-ctheta(2*speed,((i+1)/2)*((i%2==0)?-1:1),TFA[i].fai))*1e8);
		gcdt=(i==1?abs(lthetas[i]):gcd(gcdt,abs(lthetas[i])));
	}
	for(int i=1;i<=num;++i)TFA[i].omgea=(lthetas[i]*1.0)/(gcdt*1.0)*(positive[i]*1.0);
	while(flag){
		flag=0;
		for(int i=1;i<=num;++i)
			if(TFA[i].omgea>10){
				for(int i=1;i<=num;i++)TFA[i].omgea/=10.0;
				flag=1;
				break;
			}
	}
	TrigonometricFunction TF[num];
	for(int i=1;i<=num;++i)TF[i-1]=move(TFA[i]);
	auto Fix=InitialPhaseFix(TF,num);
	auto Series=FourierSeriesBuilder(TF,num);
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
