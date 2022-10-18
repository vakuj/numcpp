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

    NumCpp<float> *n1 = new NumCpp<float>();

    n1->disp();

    float src[] = {1., 2., 3., 4.};
    uint32_t *s_shape = (uint32_t *)calloc(2, sizeof(uint32_t));
    s_shape[0] = 2;
    s_shape[1] = 2;
    uint32_t s_dims = 2;
    n1->set(src, s_shape, s_dims);
    n1->disp();

    const uint32_t *a = n1->shape();
    for (uint32_t i = 0; i < n1->dims(); ++i)
        printf("%d x ", a[i]);
    printf("(1) = %d\n", n1->size());

    NumCpp<float> ret1(src, s_shape, s_dims);
    NumCpp<float> ret2(s_shape, s_dims);
    ret1.disp();
    ret2.disp();
    NumCpp<float> ret3;
    ret3 = ret1 + ret1;
    ret3.disp();

    ret3 = ret3 + 10.f;
    ret3.disp();

    return 0;
}