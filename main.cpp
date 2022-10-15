#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdint>
#include <cfloat>

#include "NumCpp.h"
#include "logger.cpp"
using namespace std;

int main()
{

    NumCpp<float> *f32 = new NumCpp<float>();
    f32->disp();

    float src[] = {1., 2., 3., 4.};
    uint32_t *s_shape = (uint32_t *)calloc(4, 4);
    s_shape[0] = 2;
    s_shape[1] = 2;
    uint32_t s_dims = 2;
    f32->set(src, s_shape, s_dims);
    f32->disp();
    f32->set(src, s_shape, s_dims);
    f32->disp();

    return 0;
}