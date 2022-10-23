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

void test_reshaping(void)
{
    NumCpp<float>::zero(3, 3).disp("original");
    NumCpp<float> f1 = NumCpp<float>::zero(3, 3).flatten(false);
    NumCpp<float> f2 = NumCpp<float>::zero(3, 3).flatten(true);
    NumCpp<float> r1 = NumCpp<float>::zero(3, 3).reshape(9, 1);
    NumCpp<float> r2 = NumCpp<float>::zero(3, 3).reshape(1, 9);
    f1.disp("flatten 1");
    f2.disp("flatten 2");
    r1.disp("reshape 1");
    r2.disp("reshape 2");

    NumCpp<float>::zero(4, 4).disp("original");
    NumCpp<float> r3 = NumCpp<float>::zero(4, 4).reshape(1, 16);
    NumCpp<float> r4 = NumCpp<float>::zero(4, 4).reshape(2, 8);
    NumCpp<float> r5 = NumCpp<float>::zero(4, 4).reshape(4, 4);
    NumCpp<float> r6 = NumCpp<float>::zero(4, 4).reshape(8, 2);
    NumCpp<float> r7 = NumCpp<float>::zero(4, 4).reshape(16, 1);
    r3.disp("reshape 3");
    r4.disp("reshape 4");
    r5.disp("reshape 5");
    r6.disp("reshape 6");
    r7.disp("reshape 7");

    NumCpp<float> r8 = NumCpp<float>::linspace(0.f, 3.6f, 36).reshape(6, 6);
    r8.disp("reshape 8");

    uint32_t n_shape1[] = {1, 16};
    uint32_t n_shape2[] = {2, 8};
    uint32_t n_shape3[] = {4, 4};
    uint32_t n_shape4[] = {8, 2};
    uint32_t n_shape5[] = {16, 1};
    NumCpp<float> rs1 = NumCpp<float>::zero(4, 4).reshape(n_shape1, NDIMS(n_shape1));
    NumCpp<float> rs2 = NumCpp<float>::zero(4, 4).reshape(n_shape2, NDIMS(n_shape2));
    NumCpp<float> rs3 = NumCpp<float>::zero(4, 4).reshape(n_shape3, NDIMS(n_shape3));
    NumCpp<float> rs4 = NumCpp<float>::zero(4, 4).reshape(n_shape4, NDIMS(n_shape4));
    NumCpp<float> rs5 = NumCpp<float>::zero(4, 4).reshape(n_shape5, NDIMS(n_shape5));
    rs1.disp("reshape by n_shape1");
    rs2.disp("reshape by n_shape2");
    rs3.disp("reshape by n_shape3");
    rs4.disp("reshape by n_shape4");
    rs5.disp("reshape by n_shape5");

    NumCpp<float> t1 = NumCpp<float>::arange(0.f, 16.f, 1.f, false).reshape(4, 4).reshape(1, 16).trans();
    NumCpp<float> t2 = NumCpp<float>::arange(0.f, 16.f, 1.f, false).reshape(2, 8).trans();
    NumCpp<float> t3 = NumCpp<float>::arange(0.f, 16.f, 1.f, false).reshape(4, 4).trans();
    NumCpp<float> t4 = NumCpp<float>::arange(0.f, 16.f, 1.f, false).reshape(8, 2).trans();
    NumCpp<float> t5 = NumCpp<float>::arange(0.f, 16.f, 1.f, false).reshape(4, 4).reshape(16, 1).trans();
    t1.disp("transpose 1");
    t2.disp("transpose 2");
    t3.disp("transpose 3");
    t4.disp("transpose 4");
    t5.disp("transpose 5");
}

void test_predefs_mxnx(void)
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
void test_predefs_mxnx1(void)
{
    uint32_t s_shape[] = {3, 3};  // square
    uint32_t w_shape[] = {10, 3}; // wide
    uint32_t l_shape[] = {3, 10}; // long
    uint32_t m_shape[] = {3, 1};  // 1d col
    uint32_t n_shape[] = {1, 3};  // 1d row

    NumCpp<float> z1 = NumCpp<float>::zero(s_shape[0], s_shape[1]);
    NumCpp<float> z2 = NumCpp<float>::zero(w_shape[0], w_shape[1]);
    NumCpp<float> z3 = NumCpp<float>::zero(l_shape[0], l_shape[1]);
    NumCpp<float> z4 = NumCpp<float>::zero(m_shape[0], m_shape[1]);
    NumCpp<float> z5 = NumCpp<float>::zero(n_shape[0], n_shape[1]);
    NumCpp<float> d1 = NumCpp<float>::diag(s_shape[0], s_shape[1]);
    NumCpp<float> d2 = NumCpp<float>::diag(w_shape[0], w_shape[1]);
    NumCpp<float> d3 = NumCpp<float>::diag(l_shape[0], l_shape[1]);
    NumCpp<float> d4 = NumCpp<float>::diag(m_shape[0], m_shape[1]);
    NumCpp<float> d5 = NumCpp<float>::diag(n_shape[0], n_shape[1]);
    NumCpp<float> o1 = NumCpp<float>::ones(s_shape[0], s_shape[1]);
    NumCpp<float> o2 = NumCpp<float>::ones(w_shape[0], w_shape[1]);
    NumCpp<float> o3 = NumCpp<float>::ones(l_shape[0], l_shape[1]);
    NumCpp<float> o4 = NumCpp<float>::ones(m_shape[0], m_shape[1]);
    NumCpp<float> o5 = NumCpp<float>::ones(n_shape[0], n_shape[1]);
    NumCpp<float> f1 = NumCpp<float>::fill(s_shape[0], s_shape[1], 69.0f);
    NumCpp<float> f2 = NumCpp<float>::fill(w_shape[0], w_shape[1], 69.0f);
    NumCpp<float> f3 = NumCpp<float>::fill(l_shape[0], l_shape[1], 69.0f);
    NumCpp<float> f4 = NumCpp<float>::fill(m_shape[0], m_shape[1], 69.0f);
    NumCpp<float> f5 = NumCpp<float>::fill(n_shape[0], n_shape[1], 69.0f);

    z1.disp("zero 1");
    z2.disp("zero 2");
    z3.disp("zero 3");
    z4.disp("zero 4");
    z5.disp("zero 5");
    d1.disp("diag 1");
    d2.disp("diag 2");
    d3.disp("diag 3");
    d4.disp("diag 4");
    d5.disp("diag 5");
    o1.disp("ones 1");
    o2.disp("ones 2");
    o3.disp("ones 3");
    o4.disp("ones 4");
    o5.disp("ones 5");
    f1.disp("fill 1");
    f2.disp("fill 2");
    f3.disp("fill 3");
    f4.disp("fill 4");
    f5.disp("fill 5");
}
void test_predefs_nxn(void)
{

    NumCpp<float> z4 = NumCpp<float>::zero(10);
    NumCpp<float> o4 = NumCpp<float>::ones(10);
    NumCpp<float> d4 = NumCpp<float>::diag(10);
    NumCpp<float> f4 = NumCpp<float>::fill(10, 69.0);
    z4.disp("zero 4");
    o4.disp("ones 4");
    d4.disp("diag 4");
    f4.disp("fill 4");
}
void test_predefs_1xn(void)
{

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

    NumCpp<float> a = NumCpp<float>::arange(0.f, 9.f, 1.f, false).reshape(3, 3);
    NumCpp<float> b = NumCpp<float>::arange(9.f, 0.f, -1.f, false).reshape(3, 3);
    NumCpp<float> c1 = a == 5.f;
    NumCpp<float> c2 = a != 5.f;
    NumCpp<float> c3 = a <= 5.f;
    NumCpp<float> c4 = a >= 5.f;
    NumCpp<float> c5 = a > 5.f;
    NumCpp<float> c6 = a < 5.f;
    NumCpp<float> ab1 = a == b;
    NumCpp<float> ab2 = a != b;
    NumCpp<float> ab3 = a <= b;
    NumCpp<float> ab4 = a >= b;
    NumCpp<float> ab5 = a > b;
    NumCpp<float> ab6 = a < b;
    a.disp("a");
    b.disp("b");
    c1.disp("c1 = a == 5.f");
    c2.disp("c2 = a != 5.f");
    c3.disp("c3 = a <= 5.f");
    c4.disp("c4 = a >= 5.f");
    c5.disp("c5 = a > 5.f");
    c6.disp("c6 = a < 5.f");
    ab1.disp("ab1 = a == b");
    ab2.disp("ab2 = a != b");
    ab3.disp("ab3 = a <= b");
    ab4.disp("ab4 = a >= b");
    ab5.disp("ab5 = a > b");
    ab6.disp("ab6 = a < b");
}

int main()
{
    test_ops();
    // test_reshaping();
    // test_predefs_mxnx1();
    // test_predefs_mxnx();
    // test_predefs_nxn();
    // test_predefs_1xn();
    return 0;
}