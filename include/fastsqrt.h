#pragma once
// en -O3, duplica en performance a sqrt. En -O0, es 30 veces mejor :D
float fastsqrt(float x) {
    float z = x;
    int val_int = *(int*)&z;
    val_int = (1 << 29) + (val_int >> 1) - (1 << 22);
    z = *(float*)&val_int;
    z -= z / 2 - x / (2*z);
    // z -= z / 2 - x / (2*z);
    return z;
}