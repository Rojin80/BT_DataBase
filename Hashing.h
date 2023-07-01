#ifndef PROJECT_HASHING_H
#define PROJECT_HASHING_H
#include "math.h"
#include "string"
#include <iostream>
using namespace std;
int hashTimestamp(string year, string month, string day) {
    int y = stoi(year), m = stoi(month), d = stoi(day);
    if (y < 1 || m < 1 || m > 12 || d < 1 || d > 31) {
        cout << y << " " << m << " " << d << " is an invalid timestamp!" << endl;
        return -1;  
    }
    int hs = y; 
    hs *= 100; 
    hs += m * 5;
    hs += d;  
    
    return hs % 100007;
}
long long int hashh(string s){
    long long int tmp = 0;
    for (int i = 0; i < s.length(); ++i) {
        tmp += (int(s[i])*pow(3.12,i));
        tmp %= 100007;
    }
    return tmp;
}

#endif //PROJECT_HASHING_H