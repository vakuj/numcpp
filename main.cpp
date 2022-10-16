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

    /**
     * NumCpp<float> ret;
     * ret = *n1 + (float)1.;
     * --->
     * In file included from main.cpp:8:
     * NumCpp.h:9:7: note: candidate: ‘NumCpp<float>& NumCpp<float>::operator=(const NumCpp<float>&)’
     *      9 | class NumCpp
     *        |       ^~~~~~
     * NumCpp.h:9:7: note:   no known conversion for argument 1 from ‘NumCpp<float>*’ to ‘const NumCpp<float>&’
     *
     */
    NumCpp<float> *ret2 = n1->operator+(1.);

    ret2->disp();

    for (size_t i = 0; i < 10; i++)
    {
        ret2 = n1->operator+((float)i);
        // ret2 = n1 + (float)1.; // why not this work?
        // ret2 = *n1 + (float)1.; // or this?
        ret2->disp();
    }

    return 0;
}