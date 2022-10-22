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

    NumCpp<float> z4 = NumCpp<float>::zero(10);
    NumCpp<float> o4 = NumCpp<float>::ones(10);
    NumCpp<float> d4 = NumCpp<float>::diag(10);
    NumCpp<float> f4 = NumCpp<float>::fill(10, 69.0);
    z4.disp("zero 4");
    o4.disp("ones 4");
    d4.disp("diag 4");
    f4.disp("fill 4");

    NumCpp<float> a1 = NumCpp<float>::arange(0.f, 1.f, .1f, false);
    NumCpp<float> a2 = NumCpp<float>::arange(0.f, 1.f, .1f, true);
    NumCpp<float> a3 = NumCpp<float>::arange(-1.f, 0.f, .1f);
    NumCpp<float> a4 = NumCpp<float>::arange(1.f, 0.f, -.1f);
    NumCpp<float> a5 = NumCpp<float>::arange(0.f, 1.f, 2.f);
    a1.disp("arange 1");
    a2.disp("arange 2");
    a3.disp("arange 3");
    a4.disp("arange 4");
    a5.disp("arange 5");

    NumCpp<float> l1 = NumCpp<float>::linspace(0.f, 1.f, 10);
    NumCpp<float> l2 = NumCpp<float>::linspace(0.f, 1.1f, 11);
    NumCpp<float> l3 = NumCpp<float>::linspace(-1.f, 0.f, 10);
    NumCpp<float> l4 = NumCpp<float>::linspace(1.f, 0.f, 10);
    NumCpp<float> l5 = NumCpp<float>::linspace(0.f, 1.f, 1);
    l1.disp("linspace 1");
    l2.disp("linspace 2");
    l3.disp("linspace 3");
    l4.disp("linspace 4");
    l5.disp("linspace 5");
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