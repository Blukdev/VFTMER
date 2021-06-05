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
using namespace std;
int main(){
	ifstream fin("datas.txt");
	int lines=0;
	stringstream buffer;
	buffer<<fin.rdbuf();
	fin.close();
	string process(buffer.str());
	for(int i=0;i<process.size();i++)
		if(process[i]=='['||process[i]==']')
			process.erase(i,1);
		else if(process[i]==','){
			++lines;
			process[i]=' ';
		}
	ofstream fout("in.txt");
	fout<<lines<<endl;
	fout<<process;
	fout.close(); 
}
