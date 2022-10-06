#pragma once

#include<cmath>
#include<cstdio>
#include<string>
#include<fstream>
#include<iomanip>
#include<iostream>
#include<vector>
#include<sstream>

#define pi 314.1592653589793238
using namespace std;
struct TrigonometricFunction {
    double alpha, omega, phi;
};

int setx, sety, setz;

inline long long gcd(long long x, long long y) {
    while (y ^= x ^= y ^= x %= y);
    return x;
}

string ArmorStandNameBuilder(int Num) {
    int LowLow = Num % 26, Low = (Num / 26) % 26, High = (Num / 676) % 26, HighHigh = Num / 17576;
    string Name;
    if (HighHigh != 0) {
        Name = "";
        Name += char(HighHigh + 65);
        Name += char(High + 65);
        Name += char(Low + 65);
        Name += char(LowLow + 65);
    } else if (High != 0) {
        Name = "";
        Name += char(High + 65);
        Name += char(Low + 65);
        Name += char(LowLow + 65);
    } else if (Low != 0) {
        Name = "";
        Name += char(Low + 65);
        Name += char(LowLow + 65);
    } else Name += char(LowLow + 65);
    return Name;
}

vector <string> FourierSeriesBuilder(TrigonometricFunction TriFunc[], int n, double zoom) {
    string name, name_p, SelectorA, SelectorB;
    vector <string> commands;
    for (int i = 0; i < n; ++i) {
        name = ArmorStandNameBuilder(i);
        name_p = ArmorStandNameBuilder(i + 1);
        ostringstream ofa(ostringstream::ate);
        ostringstream ofb(ostringstream::ate);
        SelectorA = "@e[type=armor_stand,name=\"" + name + "\"]";
        SelectorB = "@e[type=armor_stand,name=\"" + name_p + "\"]";
        ofa << "execute " << SelectorA << " ~~~ tp @s ~~~ ~" << round((-100) * TriFunc[i].omega) / 100.0 << "~";
        ofb << "execute " << SelectorA << " ~~~ tp " << SelectorB << " ^^^"
            << round(100 * TriFunc[i].alpha * zoom) / 100.0;
        commands.push_back(ofa.str());
        commands.push_back(ofb.str());
    }
    return commands;
}

vector <string> InitialPhaseFix(TrigonometricFunction TriFunc[], int n) {
    string name, Selector;
    vector <string> commands;
    for (int i = 0; i < n; ++i) {
        name = ArmorStandNameBuilder(i);
        ostringstream ofs(ostringstream::ate);
        Selector = "@e[type=armor_stand,name=\"" + name + "\"]";
        commands.push_back("execute " + Selector + " ~~~ tp @s ~~~ 0 0");
        ofs << "execute " << Selector << " ~~~ tp @s ~~~ ~"
            << round(TriFunc[i].phi * (-pi) / 180.0) / 100.0 << "~";
        commands.push_back(ofs.str());
    }
    return commands;
}

vector <string> SummonCommandBuilder(int cb) {
    vector <string> commands;
    for (int i = 1; i <= cb; i++)
        commands.push_back(
                "summon armor_stand " + ArmorStandNameBuilder(i - 1) + " " + to_string(setx) + " " + to_string(sety) +
                " " + to_string(setz));
    return commands;
}
