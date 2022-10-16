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
    // NumCpp<float> *n2 = new NumCpp<float>();
    n1->disp();

    float src[] = {1., 2., 3., 4.};
    uint32_t *s_shape = (uint32_t *)calloc(2, sizeof(uint32_t));
    s_shape[0] = 2;
    s_shape[1] = 2;
    uint32_t s_dims = 2;
    n1->set(src, s_shape, s_dims);
    n1->disp();
    // n1->set(src, s_shape, s_dims);
    // n1->disp();

    const uint32_t *a = n1->shape();
    for (uint32_t i = 0; i < n1->dims(); ++i)
        printf("%d x ", a[i]);
    printf("(1) = %d\n", n1->size());

    // // NumCpp<float> *ret = n1->operator+(n2);

    NumCpp<float> *ret2 = n1->operator+(1.);
    ret2->disp();

    for (size_t i = 0; i < 10; i++)
    {
        ret2 = n1->operator+((float)i);
        ret2->disp();
    }

    return 0;
}