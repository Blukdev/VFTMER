#pragma once
#include<cmath>
#include<cstdio>
#include<string>
#include<fstream>
#include<iomanip>
#include<iostream>
#include<vector>
#define roundt(x) round(x*100)/100.0
using namespace std;
struct TrigonometricFunction {
	double alpha,omgea,fai;
};
int setx,sety,setz;
inline double ctheta(double t,int m,double fai) {
	return t*m+fai;
}
inline long long gcd(long long x,long long y) {
	while(y^=x^=y^=x%=y);
	return x;
}
string ArmorStandNameBuilder(int Num) {
	int LowLow=Num%26, Low=(Num/26)%26, High=(Num/676)%26, HighHigh=Num/17576;
	string Name;
	if(HighHigh!=0) {
		Name="";
		Name+=char(HighHigh+65); 
		Name+=char(High+65);
		Name+=char(Low+65);
		Name+=char(LowLow+65);
	} else if(High!=0) {
		Name="";
		Name+=char(High+65);
		Name+=char(Low+65);
		Name+=char(LowLow+65);
	} else if(Low!=0) {
		Name="";
		Name+=char(Low+65);
		Name+=char(LowLow+65);
	} else Name+=char(LowLow+65);
	return Name;
}
vector<string> FourierSeriesBuilder(TrigonometricFunction (&TriFunc)[],int n,double zoom) {
	string name,namep,SelectorA,SelectorB;
	vector<string>commands;
	for(register int i=0; i<n; ++i) {
		name=ArmorStandNameBuilder(i);
		namep=ArmorStandNameBuilder(i+1);
		ostringstream ofa(ostringstream::ate);
		ostringstream ofb(ostringstream::ate);
		SelectorA="@e[type=armor_stand,name=\""+name+"\"]";
		SelectorB="@e[type=armor_stand,name=\""+namep+"\"]";
		ofa<<"execute "<<SelectorA<<" ~~~ tp @s ~~~ ~"<<roundt((-1)*TriFunc[i].omgea)<<"~";
		ofb<<"execute "<<SelectorA<<" ~~~ tp "<<SelectorB<<" ^^^"<<roundt(TriFunc[i].alpha*zoom);
		commands.push_back(ofa.str());
		commands.push_back(ofb.str());
	}
	return commands;
}
vector<string> InitialPhaseFix(TrigonometricFunction (&TriFunc)[],int n) {
	string name,Selector;
	vector<string>commands;
	for(register int i=0; i<n; ++i) {
		name=ArmorStandNameBuilder(i);
		ostringstream ofs(ostringstream::ate);
		Selector="@e[type=armor_stand,name=\""+name+"\"]";
		commands.push_back("execute "+Selector+" ~~~ tp @s ~~~ 0 0");
		TriFunc[i].fai-=round(TriFunc[i].fai/2/3.14159265358979)*2*3.14159265358979;
		ofs<<"execute "<<Selector<<" ~~~ tp @s ~~~ ~"<<roundt(((-1)*TriFunc[i].fai*180/3.14159265358979))<<"~";
		commands.push_back(ofs.str());
	}
	return commands;
}
vector<string> SummonCommandBuilder(int cb) {
	vector<string>commands;
	for(int i=1; i<=cb; i++)
		commands.push_back("summon armor_stand "+ArmorStandNameBuilder(i-1)+" "+to_string(setx)+" "+to_string(sety)+" "+to_string(setz));
	return commands;
}
