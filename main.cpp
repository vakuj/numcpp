#include <iostream>
#include <cstring>

#include "include/NumCpp.h"
#include "include/NumCpp_helpers.h"

#include "extra/logger.cpp"

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
    NF z4 = NF::zero(m_shape, NDIMS(m_shape));
    NF o1 = NF::ones(s_shape, NDIMS(s_shape));
    NF o2 = NF::ones(w_shape, NDIMS(w_shape));
    NF o3 = NF::ones(l_shape, NDIMS(l_shape));
    NF o4 = NF::ones(m_shape, NDIMS(m_shape));
    NF f1 = NF::fill(s_shape, NDIMS(s_shape), 69.0f);
    NF f2 = NF::fill(w_shape, NDIMS(w_shape), 69.0f);
    NF f3 = NF::fill(l_shape, NDIMS(l_shape), 69.0f);
    NF f4 = NF::fill(m_shape, NDIMS(m_shape), 69.0f);

    z1.disp("zero 1");
    o1.disp("ones 1");
    f1.disp("fill 1");
    z2.disp("zero 2");
    o2.disp("ones 2");
    f2.disp("fill 2");
    z3.disp("zero 3");
    o3.disp("ones 3");
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
    NF &row = a[1];
    row.disp("row?");
    delete &row;
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
void test_math(void)
{
    NF a = NF_LINSPACE(0, 9, 9);
    a.disp("linear array a");

    float asum = a.sum();
    float amax = a.max();
    float amin = a.min();
    printf("sum of a: %.3f\nmax of a: %.3f\nmin of a: %.3f\n", asum, amax, amin);

    NF b = NF(a).cumsum();
    b.disp("summed a");

    NF c = NF_DIAG(4);
    // NF c = NF_LINSPACE(0, 9, 9).reshape(3, 3);
    c.disp("c");

#define COUNT 4

    uint32_t max1 = c.arg_max();
    uint32_t min1 = c.arg_min();
    uint32_t *max2 = c.arg_max(COUNT);
    uint32_t *min2 = c.arg_min(COUNT);
    printf("First ind: %3d, %3d\n", max1, min1);
    printf("ind max min\n");
    for (uint32_t i = 0; i < COUNT; ++i)
    {
        printf("%3d %3d %3d\n", i, max2[i], min2[i]);
    }
    loc_t l1 = c.coord(max1);
    loc_t l2 = c.coord(min1);
    printf("max (row,col): (%3d, %3d)\n", l1.row, l1.col);
    printf("min (row,col): (%3d, %3d)\n", l2.row, l2.col);
    loc_t *ll1 = c.coord(max2, COUNT);
    loc_t *ll2 = c.coord(min2, COUNT);
    for (uint32_t i = 0; i < COUNT; ++i)
    {
        printf("%3d th max (row,col): (%3d, %3d)\n", i, ll1[i].row, ll1[i].col);
        printf("%3d th min (row,col): (%3d, %3d)\n", i, ll2[i].row, ll2[i].col);
    }
    free(max2);
    free(min2);
    free(ll1);
    free(ll2);

    NF ma1 = NF_DIAG(2);
    NF mb1 = NF::arange(2.f, 8.f, 2.f).reshape(2, 2);
    NF mm1 = ma1.matmul(&mb1);
    NF ma2 = NF::arange(0.f, 5.f, 1.f).reshape(3, 2);
    NF mb2 = NF::arange(0.f, 5.f, 1.f).reshape(2, 3);
    NF mm2 = ma2.matmul(&mb2);
    NF mm3 = mb2.matmul(&ma2);
    ma1.disp("ma1");
    mb1.disp("mb1");
    mm1.disp("mm1");
    ma2.disp("ma2");
    mb2.disp("mb2");
    mm2.disp("mm2");
    mm3.disp("mm3");
}
void test_assert(void)
{
    NF a = NF_LINSPACE(0, 9, 9);
    NF b = NF_LINSPACE(0, 9, 9).reshape(3, 3);
    NF c = NF_LINSPACE(1, 10, 9);
    NF d = a + 1.0;

    /** Soft checking: Does not abort if failed */
    ASSERT_SIZE(a, b);   // Pass
    ASSERT_SHAPE(a, b);  // Fail
    ASSERT_SHAPE(c, d);  // Pass
    ASSERT_DIMS(a, b);   // Fail
    ASSERT_DIMS(c, d);   // Pass
    ASSERT_MEMORY(a, b); // Pass
    ASSERT_MEMORY(a, c); // Fail
    ASSERT_MEMORY(c, d); // Pass
    ASSERT_EMPTY(a);     // Fail

    /** Hard checking: Must pass to continue */
    XPASS_SIZE(a, b);   // Pass
    XFAIL_SHAPE(a, b);  // Pass
    XPASS_SHAPE(c, d);  // Pass
    XFAIL_DIMS(a, b);   // Pass
    XPASS_DIMS(c, d);   // Pass
    XPASS_MEMORY(a, b); // Pass
    XFAIL_MEMORY(a, c); // Pass
    XPASS_MEMORY(c, d); // Pass
    XFAIL_EMPTY(a);     // Pass
}
void test_pre_ops(void)
{
    NF a = NF_LINSPACE(1, 10, 9).reshape(3, 3).trans();
    NF b = NF_LINSPACE(1, 10, 9).reshape(3, 3);
    NF c = NF_ZERO(3, 3);
    a.disp("a");
    b.disp("b");
    c.disp("c");

    // NF *dst = &c;
    NF *dst = NF::padd(&c, &a, &b);
    dst->disp("after padd");
    dst = NF::psub(dst, &a, &b);
    dst->disp("after psub");
    dst = NF::pdiv(dst, &a, &b);
    dst->disp("after pdiv");
    dst = NF::pmul(dst, &a, &b);
    dst->disp("after pmul");

    dst = NF::padd(dst, &a, 3.f);
    dst->disp("after padd");
    dst = NF::psub(dst, &a, 3.f);
    dst->disp("after psub");
    dst = NF::pdiv(dst, &a, 3.f);
    dst->disp("after pdiv");
    dst = NF::pmul(dst, &a, 3.f);
    dst->disp("after pmul");
}
void example(void)
{
    NumCpp<float> a = NumCpp<float>::ones(3);                             // 3x3 array with ones
    NumCpp<float> b = NumCpp<float>::linspace(0.f, 9.f, 9).reshape(3, 3); // reshape 9 elements to 3x3 array
    a.disp("a");                                                          // display the arrays
    b.disp("b");                                                          // display the arrays
    NumCpp<float> c, d;
    c = a + b; // Ok
    c.disp("c = a + b");
    c = a - b; // Ok
    c.disp("c = a - b");
    c = a * b; // Ok
    c.disp("c = a * b");
    c = a / b; // Ok
    c.disp("c = a / b");

    d = a + 3.f; // Ok
    d = a - 3.f; // Ok
    d = a * 3.f; // Ok
    d = a / 3.f; // Ok
    // d = 3.f + a; // not supported

    NumCpp<float> e = NF(b).trans();   // Copy b and transpose
    NumCpp<float> f = NF(e).flatten(); // Copy e and flatten to 1d
    e.disp("e");
    f.disp("f");

    NumCpp<float> g = a / b < .3f; // create a mask where elements of a/b are smaller than 0.3
    g.disp("g");
    NumCpp<float> h = b * g; // apply mask g to a
    h.disp("h");
}
int main()
{
    // test_pre_ops();
    // test_assert();
    test_math();
    // example();
    // test_access();
    // test_ops();
    // test_reshaping();
    // test_predefs_mxnx1();
    // test_predefs_mxnx();
    // test_predefs_nxn();
    // test_predefs_1xn();

    return 0;
}