/*
 ____  _       _          _
| __ )| |_   _| | __   __| | _____   __
|  _ \| | | | | |/ /  / _` |/ _ \ \ / /
| |_) | | |_| |   <  | (_| |  __/\ V /
|____/|_|\__,_|_|\_\  \__,_|\___| \_(_)
*/
#include<iostream>
#include<fstream>
#include<cmath>
#define roundt(x) round(x*100)/100.0
using namespace std;
double speed=1;
inline double ctheta(double t,int m,double fai){
	return t*m+fai;
}
inline long long gcd(long long x,long long y){
    	while(y^=x^=y^=x%=y);
	return x;
}
int main(){
	ifstream fin("in.txt");
	int num,flag=1;
	fin>>num;
	int positive[num+1];
	long long lthetas[num+1],gcdt;
	double data1,data2,fai[num+1],alpha[num+1],omega[num+1],thetas[num+1];
	for(int i=1;i<=num;i++){
		fin>>data1>>data2;
		alpha[i]=sqrt(data1*data1+data2*data2);
		fai[i]=atan2(data2,data1);
	}
	fin.close();
	for(int i=1;i<=num;i++){
		double theta=ctheta(speed,((i+1)/2)*((i%2==0)?-1:1),fai[i]);
		positive[i]=theta>0?1:theta<0?-1:0;
		lthetas[i]=(long long)(fabs(theta-ctheta(2*speed,((i+1)/2)*((i%2==0)?-1:1),fai[i]))*1e8);
		gcdt=(i==1?abs(lthetas[i]):gcd(gcdt,abs(lthetas[i])));
	}
	for(int i=1;i<=num;i++)omega[i]=(lthetas[i]*1.0)/(gcdt*1.0)*(positive[i]*1.0);
	while(flag){
		flag=0;
		for(int i=1;i<=num;i++)
			if(omega[i]>10){
				for(int i=1;i<=num;i++)omega[i]/=10.0;
				flag=1;
				break;
			}
	}
	ofstream fout("set.txt");
	fout<<num<<endl;
	for(int i=1;i<=num;i++)fout<<roundt(omega[i])<<" "<<roundt(alpha[i])<<" "<<roundt(fai[i])<<endl;
	fout.close();
}
