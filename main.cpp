#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdint>
#include <cfloat>

#include "NumCpp.h"
#include "logger.cpp"

using namespace std;

#define NDIMS(x) (uint32_t)(sizeof(x) / sizeof(x[0]))

void test_predefs(void)
{
    uint32_t s_shape[] = {3, 3};    // square
    uint32_t w_shape[] = {10, 3};   // wide
    uint32_t l_shape[] = {3, 10};   // long
    uint32_t m_shape[] = {3, 3, 3}; // 3d

    NumCpp<float> z1 = NumCpp<float>::zero(s_shape, NDIMS(s_shape));
    NumCpp<float> z2 = NumCpp<float>::zero(w_shape, NDIMS(w_shape));
    NumCpp<float> z3 = NumCpp<float>::zero(l_shape, NDIMS(l_shape));

    NumCpp<float> o1 = NumCpp<float>::ones(s_shape, NDIMS(s_shape));
    NumCpp<float> o2 = NumCpp<float>::ones(w_shape, NDIMS(w_shape));
    NumCpp<float> o3 = NumCpp<float>::ones(l_shape, NDIMS(l_shape));

    NumCpp<float> d1 = NumCpp<float>::diag(s_shape, NDIMS(s_shape));
    NumCpp<float> d2 = NumCpp<float>::diag(w_shape, NDIMS(w_shape));
    NumCpp<float> d3 = NumCpp<float>::diag(l_shape, NDIMS(l_shape));

    NumCpp<float> f1 = NumCpp<float>::fill(s_shape, NDIMS(s_shape), 69.0);
    NumCpp<float> f2 = NumCpp<float>::fill(w_shape, NDIMS(w_shape), 69.0);
    NumCpp<float> f3 = NumCpp<float>::fill(l_shape, NDIMS(l_shape), 69.0);

    z1.disp("zero 1");
    o1.disp("ones 1");
    d1.disp("diag 1");
    f1.disp("fill 1");
    z2.disp("zero 2");
    o2.disp("ones 2");
    d2.disp("diag 2");
    f2.disp("fill 2");
    z3.disp("zero 3");
    o3.disp("ones 3");
    d3.disp("diag 3");
    f3.disp("fill 3");
}

void test_ops(void)
{

    uint32_t s_shape[] = {2, 2}; // square
    uint32_t s_dims = NDIMS(s_shape);
    float src[] = {1., 2., 3., 4.};

    NumCpp<float> ret1(src, s_shape, s_dims);
    NumCpp<float> ret2(s_shape, s_dims);
    ret1.disp("ret1");
    ret2.disp("ret2");
    NumCpp<float> ret3;
    ret3 = ret1 + ret1;
    ret3.disp("ret3 = ret1 + ret1;");
    ret1.disp("ret1");
    ret2.disp("ret2");

    ret3 = ret3 + 10.f;
    ret3.disp("ret3 = ret3 + 10.f;");
    ret3 = ret3 + ret1;
    ret3.disp("ret3 = ret3 + ret1;");
    ret3 = ret3 - ret1;
    ret3.disp("ret3 = ret3 - ret1;");
    ret3 = ret3 * ret1;
    ret3.disp("ret3 = ret3 * ret1;");
    ret3 = ret3 / ret1;
    ret3.disp("ret3 = ret3 / ret1;");
    ret3 = ret3 + 10.f;
    ret3.disp("ret3 = ret3 + 10.f;");
    ret3 = ret3 - 10.f;
    ret3.disp("ret3 = ret3 - 10.f;");
    ret3 = ret3 * 10.f;
    ret3.disp("ret3 = ret3 * 10.f;");
    ret3 = ret3 / 10.f;
    ret3.disp("ret3 = ret3 / 10.f;");
}

int main()
{
    // test_ops();
    test_predefs();
    return 0;
}