#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdint>
#include <cfloat>

#include "NumCpp.h"
#include "NumCpp_defs.h"

#include "logger.cpp"

using namespace std;

#define NDIMS(x) (uint32_t)(sizeof(x) / sizeof(x[0]))
void test_reshaping(void)
{
    NF::zero(3, 3).disp("original");
    NF f1 = NF::zero(3, 3).flatten(false);
    NF f2 = NF::zero(3, 3).flatten(true);
    NF r1 = NF::zero(3, 3).reshape(9, 1);
    NF r2 = NF::zero(3, 3).reshape(1, 9);
    f1.disp("flatten 1");
    f2.disp("flatten 2");
    r1.disp("reshape 1");
    r2.disp("reshape 2");

    NF::zero(4, 4).disp("original");
    NF r3 = NF::zero(4, 4).reshape(1, 16);
    NF r4 = NF::zero(4, 4).reshape(2, 8);
    NF r5 = NF::zero(4, 4).reshape(4, 4);
    NF r6 = NF::zero(4, 4).reshape(8, 2);
    NF r7 = NF::zero(4, 4).reshape(16, 1);
    r3.disp("reshape 3");
    r4.disp("reshape 4");
    r5.disp("reshape 5");
    r6.disp("reshape 6");
    r7.disp("reshape 7");

    NF r8 = NF::linspace(0.f, 3.6f, 36).reshape(6, 6);
    r8.disp("reshape 8");

    uint32_t n_shape1[] = {1, 16};
    uint32_t n_shape2[] = {2, 8};
    uint32_t n_shape3[] = {4, 4};
    uint32_t n_shape4[] = {8, 2};
    uint32_t n_shape5[] = {16, 1};
    NF rs1 = NF::zero(4, 4).reshape(n_shape1, NDIMS(n_shape1));
    NF rs2 = NF::zero(4, 4).reshape(n_shape2, NDIMS(n_shape2));
    NF rs3 = NF::zero(4, 4).reshape(n_shape3, NDIMS(n_shape3));
    NF rs4 = NF::zero(4, 4).reshape(n_shape4, NDIMS(n_shape4));
    NF rs5 = NF::zero(4, 4).reshape(n_shape5, NDIMS(n_shape5));
    rs1.disp("reshape by n_shape1");
    rs2.disp("reshape by n_shape2");
    rs3.disp("reshape by n_shape3");
    rs4.disp("reshape by n_shape4");
    rs5.disp("reshape by n_shape5");

    NF t1 = NF::arange(0.f, 16.f, 1.f, false).reshape(4, 4).reshape(1, 16).trans();
    NF t2 = NF::arange(0.f, 16.f, 1.f, false).reshape(2, 8).trans();
    NF t3 = NF::arange(0.f, 16.f, 1.f, false).reshape(4, 4).trans();
    NF t4 = NF::arange(0.f, 16.f, 1.f, false).reshape(8, 2).trans();
    NF t5 = NF::arange(0.f, 16.f, 1.f, false).reshape(4, 4).reshape(16, 1).trans();
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

    NF z1 = NF::zero(s_shape, NDIMS(s_shape));
    NF z2 = NF::zero(w_shape, NDIMS(w_shape));
    NF z3 = NF::zero(l_shape, NDIMS(l_shape));
    NF o1 = NF::ones(s_shape, NDIMS(s_shape));
    NF o2 = NF::ones(w_shape, NDIMS(w_shape));
    NF o3 = NF::ones(l_shape, NDIMS(l_shape));
    NF d1 = NF::diag(s_shape, NDIMS(s_shape));
    NF d2 = NF::diag(w_shape, NDIMS(w_shape));
    NF d3 = NF::diag(l_shape, NDIMS(l_shape));
    NF f1 = NF::fill(s_shape, NDIMS(s_shape), 69.0);
    NF f2 = NF::fill(w_shape, NDIMS(w_shape), 69.0);
    NF f3 = NF::fill(l_shape, NDIMS(l_shape), 69.0);

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

    NF z1 = NF::zero(s_shape[0], s_shape[1]);
    NF z2 = NF::zero(w_shape[0], w_shape[1]);
    NF z3 = NF::zero(l_shape[0], l_shape[1]);
    NF z4 = NF::zero(m_shape[0], m_shape[1]);
    NF z5 = NF::zero(n_shape[0], n_shape[1]);
    NF d1 = NF::diag(s_shape[0], s_shape[1]);
    NF d2 = NF::diag(w_shape[0], w_shape[1]);
    NF d3 = NF::diag(l_shape[0], l_shape[1]);
    NF d4 = NF::diag(m_shape[0], m_shape[1]);
    NF d5 = NF::diag(n_shape[0], n_shape[1]);
    NF o1 = NF::ones(s_shape[0], s_shape[1]);
    NF o2 = NF::ones(w_shape[0], w_shape[1]);
    NF o3 = NF::ones(l_shape[0], l_shape[1]);
    NF o4 = NF::ones(m_shape[0], m_shape[1]);
    NF o5 = NF::ones(n_shape[0], n_shape[1]);
    NF f1 = NF::fill(s_shape[0], s_shape[1], 69.0f);
    NF f2 = NF::fill(w_shape[0], w_shape[1], 69.0f);
    NF f3 = NF::fill(l_shape[0], l_shape[1], 69.0f);
    NF f4 = NF::fill(m_shape[0], m_shape[1], 69.0f);
    NF f5 = NF::fill(n_shape[0], n_shape[1], 69.0f);

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

    NF z4 = NF::zero(10);
    NF o4 = NF::ones(10);
    NF d4 = NF::diag(10);
    NF f4 = NF::fill(10, 69.0);
    z4.disp("zero 4");
    o4.disp("ones 4");
    d4.disp("diag 4");
    f4.disp("fill 4");
}
void test_predefs_1xn(void)
{

    NF a1 = NF::arange(0.f, 1.f, .1f, false);
    NF a2 = NF::arange(0.f, 1.f, .1f, true);
    NF a3 = NF::arange(-1.f, 0.f, .1f);
    NF a4 = NF::arange(1.f, 0.f, -.1f);
    NF a5 = NF::arange(0.f, 1.f, 2.f);
    a1.disp("arange 1");
    a2.disp("arange 2");
    a3.disp("arange 3");
    a4.disp("arange 4");
    a5.disp("arange 5");

    NF l1 = NF::linspace(0.f, 1.f, 10);
    NF l2 = NF::linspace(0.f, 1.1f, 11);
    NF l3 = NF::linspace(-1.f, 0.f, 10);
    NF l4 = NF::linspace(1.f, 0.f, 10);
    NF l5 = NF::linspace(0.f, 1.f, 1);
    l1.disp("linspace 1");
    l2.disp("linspace 2");
    l3.disp("linspace 3");
    l4.disp("linspace 4");
    l5.disp("linspace 5");
}
void test_access(void)
{
    NF a = NF::linspace(-9.f, 0.f, 9).reshape(3, 3);
    a.disp();
    loc_t loc = {loc.row = 1, loc.col = 0};
    float a1 = a[{1, 0}];
    float a2 = a[loc];
    printf("\na1: %.3f\na2: %.3f\n", a1, a2);
    NF row = a[1];
    row.disp("row?");
}
void test_ops(void)
{

    uint32_t s_shape[] = {2, 2}; // square
    uint32_t s_dims = NDIMS(s_shape);
    float src[] = {1., 2., 3., 4.};

    NF ret1(src, s_shape, s_dims);
    NF ret2(s_shape, s_dims);
    ret1.disp("ret1");
    ret2.disp("ret2");
    NF ret3;
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

    NF a = NF::arange(0.f, 9.f, 1.f, false).reshape(3, 3);
    NF b = NF::arange(9.f, 0.f, -1.f, false).reshape(3, 3);
    NF c1 = a == 5.f;
    NF c2 = a != 5.f;
    NF c3 = a <= 5.f;
    NF c4 = a >= 5.f;
    NF c5 = a > 5.f;
    NF c6 = a < 5.f;
    NF ab1 = a == b;
    NF ab2 = a != b;
    NF ab3 = a <= b;
    NF ab4 = a >= b;
    NF ab5 = a > b;
    NF ab6 = a < b;
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
    test_access();
    test_ops();
    test_reshaping();
    test_predefs_mxnx1();
    test_predefs_mxnx();
    test_predefs_nxn();
    test_predefs_1xn();
    return 0;
}