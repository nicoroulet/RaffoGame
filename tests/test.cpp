#include <iostream>
#include "fastsqrt.h"
#include "math.h"
#include "rdtsc.h"

// float fastsqrt(float x);
using namespace std;
int main() {
    //test de performance de fastsqrt
    float i;
    cout << "ingresar numero\n";
    cin >> i;
    uint64_t t;
    float a1;
    float a2;
    float a3;
    float a4;
    float a5;
    float a6;
    uint64_t ta;
    float b1;
    float b2;
    float b3;
    float b4;
    float b5;
    float b6;
    uint64_t tb;
    
    t = rdtsc();
    a1 = sqrt(i);
    a2 = sqrt(i+1);
    a3 = sqrt(i+2);
    a4 = sqrt(i+3);
    a5 = sqrt(i+4);
    a6 = sqrt(i+5);
    ta = rdtsc() - t;
    
    t = rdtsc();
    b1 = fastsqrt(i);
    b2 = fastsqrt(i+1);
    b3 = fastsqrt(i+2);
    b4 = fastsqrt(i+3);
    b5 = fastsqrt(i+4);
    b6 = fastsqrt(i+5);
    tb = rdtsc() - t;
    
    cout << "sqrt: " << a1+a2+a3+a4+a5+a6 << " time: " << ta << endl;
    cout << "fastsqrt: " << b1+b2+b3+b4+b5+b6 << " time: " << tb << endl;
    
    
    return 0;
}